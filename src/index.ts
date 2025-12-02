type EnumerateInternal<
  N extends number,
  Acc extends number[] = []
> = Acc["length"] extends N
  ? Acc[number]
  : EnumerateInternal<N, [...Acc, Acc["length"]]>;
type Enumerate<N extends number> = EnumerateInternal<N> | N;

type NumberInRange<Min extends number, Max extends number> = Min extends Max
  ? Min
  : Exclude<Enumerate<Max>, Enumerate<Min>> | Min;

export interface GregorianDateTime {
  year: number;
  month: NumberInRange<1, 12>;
  day: NumberInRange<1, 31>;
  hour?: NumberInRange<0, 23>;
  minute?: NumberInRange<0, 59>;
  second?: NumberInRange<0, 59>;
}

class JulianPeriod {
  private isGregorian({
    year,
    month,
    day,
  }: Omit<GregorianDateTime, "hour" | "minute" | "second">): boolean {
    return (
      year > 1582 ||
      (year === 1582 && (month > 10 || (month === 10 && day > 14)))
    );
  }
  //Special "Math.floor()"
  private INT(d: number) {
    if (d > 0) {
      return Math.floor(d);
    }
    if (d === Math.floor(d)) {
      return d;
    }
    return Math.floor(d) - 1;
  }

  private mod(n: number, m: number) {
    // Mathematical modulo that returns a value in [0, m-1] for any integer n (including negatives)
    return ((n % m) + m) % m;
  }

  solarNumber(year: number): number {
    // Position of a year within the 28-year Solar Cycle (1..28), handles BCE (negative/zero years)
    return this.mod(year + 8, 28) + 1;
  }

  lunarNumber(year: number): number {
    // Position of a year within the 19-year Metonic (Lunar) cycle (1..19), handles BCE
    return this.mod(year, 19) + 1;
  }

  indictionNumber(year: number): number {
    // Position of a year within the 15-year Indiction cycle (1..15), handles BCE
    return this.mod(year + 2, 15) + 1;
  }

  julianPeriodYearNumber(year: number): number {
    // Compute position within the Julian Period (length 15*19*28 = 7980 years),
    // returning a value in 1..7980 and correctly handling BCE years.
    const C15 = 15;
    const C19 = 19;
    const C28 = 28;
    const N = C15 * C19 * C28; // 7980

    // Use zero-based cycle positions for linear combination, then map to 1..N
    const ind0 = this.indictionNumber(year) - 1; // 0..14
    const lun0 = this.lunarNumber(year) - 1; // 0..18
    const sol0 = this.solarNumber(year) - 1; // 0..27

    // Coefficients as in original formula, combine and reduce modulo N
    const combined = 6916 * ind0 + 4200 * lun0 + 4845 * sol0;
    return this.mod(combined, N) + 1;
  }
  gregorianToJD({
    year: inputYear,
    month: inputMonth,
    day: inputDay,
    hour = 12,
    minute = 0,
    second = 0,
  }: GregorianDateTime): { julianDay: number; julianDayNumber: number } {
    // Runtime validation (stronger guarantees)
    if (!Number.isFinite(inputYear) || !Number.isInteger(inputYear)) {
      throw new TypeError("year must be a finite integer");
    }
    if (
      !Number.isFinite(inputMonth) ||
      !Number.isInteger(inputMonth) ||
      inputMonth < 1 ||
      inputMonth > 12
    ) {
      throw new RangeError("month must be an integer in 1..12");
    }
    if (
      !Number.isFinite(inputDay) ||
      !Number.isInteger(inputDay) ||
      inputDay < 1 ||
      inputDay > 31
    ) {
      throw new RangeError("day must be an integer in 1..31");
    }
    if (!Number.isFinite(hour) || hour < 0 || hour >= 24) {
      throw new RangeError("hour must be in 0..23");
    }
    if (!Number.isFinite(minute) || minute < 0 || minute >= 60) {
      throw new RangeError("minute must be in 0..59");
    }
    if (!Number.isFinite(second) || second < 0 || second >= 60) {
      throw new RangeError("second must be in 0..59");
    }

    // Use local copies to avoid mutating the caller-provided values
    let year = inputYear;
    let month = inputMonth;
    const day = inputDay;

    // Adjust Jan/Feb to months 13/14 of previous year (Meeus / Zeller style)
    if (month < 3) {
      year -= 1;
      month += 12;
    }

    // Gregorian correction (B). Use adjusted year/month when computing correction.
    let B = 0;
    if (this.isGregorian({ year, month: month as NumberInRange<1, 12>, day })) {
      const A = this.INT(year / 100);
      B = 2 - A + this.INT(A / 4);
    }

    // Meeus algorithm (JDN has fractional .5 offset included)
    const julianDayNumber =
      this.INT(365.25 * (year + 4716)) +
      this.INT(30.6001 * (month + 1)) +
      day +
      B -
      1524.5;

    // Compute fractional day from h/m/s with integer arithmetic for precision
    const dayFraction = (hour * 3600 + minute * 60 + second) / 86400;

    const julianDay = julianDayNumber + dayFraction;

    return { julianDay, julianDayNumber };
  }
  jdToGregorian(jd: number): GregorianDateTime {
    if (!isFinite(jd)) {
      throw new TypeError("jd must be a finite number");
    }

    // Core conversion (Meeus)
    const temp = jd + 0.5;
    const Z = this.INT(temp);
    let F = temp - Z;
    let A = Z;
    if (Z >= 2299161) {
      const alpha = this.INT((Z - 1867216.25) / 36524.25);
      A = Z + 1 + alpha - this.INT(alpha / 4);
    }
    const B = A + 1524;
    const C = this.INT((B - 122.1) / 365.25);
    const D = this.INT(365.25 * C);
    const E = this.INT((B - D) / 30.6001);

    // Day (integer) and fractional day
    const dayWithFrac = B - D - this.INT(30.6001 * E) + F;
    let day = this.INT(dayWithFrac);
    let month = E < 14 ? E - 1 : E - 13;
    let year = month > 2 ? C - 4716 : C - 4715;
    let dayFraction = dayWithFrac - day; // fraction of the day [0,1)

    // Compute time components from fractional day with millisecond precision
    let totalSeconds = dayFraction * 86400; // seconds in the fractional day
    // Round to milliseconds to avoid floating noise
    totalSeconds = Math.round(totalSeconds * 1000) / 1000;

    let hour = Math.trunc(totalSeconds / 3600);
    totalSeconds -= hour * 3600;
    let minute = Math.trunc(totalSeconds / 60);
    let second = +(totalSeconds - minute * 60).toFixed(3);

    // Normalize carries (second -> minute -> hour -> day)
    if (second >= 60) {
      second -= 60;
      minute += 1;
    }
    if (minute >= 60) {
      minute -= 60;
      hour += 1;
    }

    if (hour >= 24) {
      hour -= 24;
      day += 1;
    }

    // Helpers for month/day overflow using appropriate leap rules
    const isGregorian = this.isGregorian({
      year,
      month: month as NumberInRange<1, 12>,
      day: day as NumberInRange<1, 31>,
    });
    const isLeap = (y: number, greg: boolean) =>
      greg ? y % 4 === 0 && (y % 100 !== 0 || y % 400 === 0) : y % 4 === 0;

    const daysInMonth = (y: number, m: number, greg: boolean) => {
      if (m === 2) return isLeap(y, greg) ? 29 : 28;
      if (m === 4 || m === 6 || m === 9 || m === 11) return 30;
      return 31;
    };

    // Normalize day/month/year if day overflowed after carry
    let dim = daysInMonth(year, month, isGregorian);
    if (day > dim) {
      day = 1;
      month += 1;
      if (month > 12) {
        month = 1;
        year += 1;
      }
    }

    // Final shape matches GregorianDateTime interface
    return {
      year,
      month: month as NumberInRange<1, 12>,
      day: day as NumberInRange<1, 31>,
      hour: hour as NumberInRange<0, 23>,
      minute: minute as NumberInRange<0, 59>,
      second: second as NumberInRange<0, 59>,
    };
  }
}

const jp = new JulianPeriod();

export default jp;
