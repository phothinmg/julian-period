#ifndef JULIAN_PERIOD_HPP_
#define JULIAN_PERIOD_HPP_

#include <optional>
#include <cmath>

using namespace std;
namespace jp
{
    struct GregorianDateTime
    {
        int year;
        int month;
        int day;
        optional<int> hour = nullopt;
        optional<int> minute = nullopt;
        optional<int> seconds = nullopt;
    };
    struct Dt2Jd
    {
        double julianDay;
        int julianDayNumber;
    };
    struct Jd2Dt
    {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int seconds;
    };

    /// @brief Determine if a given date is in the Gregorian calendar
    /// @param year Year of date
    /// @param month Month of date
    /// @param day Day of date
    /// @return True if date is in Gregorian calendar, false otherwise
    bool is_gregorian(const int &year, const int &month, const int &day)
    {
        return year > 1582 || (year == 1582 && (month > 10 || (month == 10 && day > 14)));
    }

    double INT(double d)
    {
        if (d > 0)
        {
            return floor(d);
        }
        if (d == floor(d))
        {
            return d;
        }
        return floor(d) - 1;
    }
    /// @brief Mathematical modulo that returns a value in [0, m-1] for any integer n (including negatives)
    double mod(int n, int m) { return ((n % m) + m) % m; }

    /// @brief Position of a year within the 28-year Solar Cycle (1..28), handles BCE (negative/zero years)
    /// @param year Year of date
    /// @return Position of year in Solar Cycle (1..28)
    /// @details This function computes the position of a year within the 28-year Solar Cycle.
    /// The Solar Cycle is a sequence of years that repeat every 28 years, where the same days of the week
    /// fall on the same dates. The position of a year in the Solar Cycle is used in algorithms to compute
    /// the day of the week for a given date.
    /// @example solar_number(2025) returns 11
    int solar_number(const int &year)
    // Position of a year within the 28-year Solar Cycle (1..28), handles BCE (negative/zero years)
    {
        return mod(year + 8, 28) + 1;
    }

    /// @brief Position of a year within the 19-year Metonic (Lunar) cycle (1..19), handles BCE
    /// @param year Year of date
    /// @return Position of year in current Lunar cycle (1..19)
    /// @details This function computes the position of a year within the 19-year Metonic (Lunar) cycle.
    /// The Lunar cycle is a sequence of years that repeat every 19 years, where the same days of the month
    /// fall on the same dates. The position of a year in the Lunar cycle is used in algorithms to compute
    /// the day of the month for a given date.
    int lunar_number(const int &year)
    {
        return mod(year, 19) + 1;
    }

    /// @brief Position of a year within the 15-year Indiction cycle (1..15), handles BCE
    /// @param year Year of date
    /// @return Position of year in current Indiction cycle (1..15)
    /// @details This function computes the position of a year within the 15-year Indiction cycle.
    /// The Indiction cycle is a sequence of years that repeat every 15 years, where the same days of the year
    /// fall on the same dates. The position of a year in the Indiction cycle is used in algorithms to compute
    /// the day of the year for a given date.
    int indiction_number(const int &year)
    {
        return mod(year + 2, 15) + 1;
    }
    /// @brief Compute position within the Julian Period (length 15*19*28 = 7980 years)
    /// @param year Year of date
    /// @return Position of year in Julian Period (1..7980)
    /// @details This function computes the position of a year within the Julian Period.
    /// The Julian Period is a sequence of years that repeat every 7980 years, where the same days of the week
    /// fall on the same dates. The position of a year in the Julian Period is used in algorithms to compute
    /// the day of the week for a given date.
    int julian_period_year(const int &year)
    // Compute position within the Julian Period (length 15*19*28 = 7980 years)
    {
        int C15 = 15;
        int C19 = 19;
        int C28 = 28;
        int N = C15 * C19 * C28; // 7980

        int ind0 = indiction_number(year) - 1; // 0..14 zero-based cycle positions
        int lun0 = lunar_number(year) - 1;     // 0..18 zero-based cycle positions
        int sol0 = solar_number(year) - 1;     // 0..24 zero-based cycle positions

        int combined = 6916 * ind0 + 4200 * lun0 + 4845 * sol0; // Coefficients as in original formula, combine and reduce modulo N

        return mod(combined, N) + 1;
    }

    /// @brief Converts a Gregorian date to a Julian Day Number (JDN)
    /// @param year Year of date
    /// @param month Month of date
    /// @param day Day of date
    /// @param hour Optional hour of date (defaults to 12)
    /// @param minute Optional minute of date (defaults to 0)
    /// @param seconds Optional seconds of date (defaults to 0)
    /// @param tz_offset Optional timezone offset in hours (defaults to 0.0)
    /// @return A Dt2Jd object containing the Julian Day (JD) and Julian Day Number (JDN) of the input date
    Dt2Jd gregorian_to_jd(int year, int month, int day,
                          optional<int> hour = nullopt,
                          optional<int> minute = nullopt,
                          optional<int> seconds = nullopt,
                          optional<float> tz_offset = nullopt)
    {
        // keep original date for Gregorian calendar determination
        int orig_year = year, orig_month = month, orig_day = day;

        // defaults: noon if time not provided (traditional for JD)
        int h = hour.value_or(12);
        int m = minute.value_or(0);
        int s = seconds.value_or(0);

        // timezone offset in hours: convert local time to UT by subtracting offset
        double tz_hours = tz_offset.value_or(0.0f);
        double seconds_of_day = static_cast<double>(h) * 3600.0 + static_cast<double>(m) * 60.0 + static_cast<double>(s) - tz_hours * 3600.0;
        double day_fraction = seconds_of_day / 86400.0;

        // adjust month/year for algorithm (Jan/Feb are treated as months 13/14 of previous year)
        int Y = year;
        int M = month;
        if (M <= 2)
        {
            Y -= 1;
            M += 12;
        }

        // Gregorian correction term
        int B = 0;
        if (is_gregorian(orig_year, orig_month, orig_day))
        {
            int A = static_cast<int>(std::floor(static_cast<double>(Y) / 100.0));
            B = 2 - A + static_cast<int>(std::floor(static_cast<double>(A) / 4.0));
        }

        // Meeus algorithm for Julian Day (JD)
        double julianDay = std::floor(365.25 * (static_cast<double>(Y) + 4716.0)) + std::floor(30.6001 * (static_cast<double>(M) + 1.0)) + static_cast<double>(day) + static_cast<double>(B) - 1524.5 + day_fraction;

        // Julian Day Number (JDN) is the integer day number: floor(JD + 0.5)
        int julianDayNumber = static_cast<int>(std::floor(julianDay + 0.5));

        return {julianDay, julianDayNumber};
    }
    /// @brief Converts a Julian Day Number (JDN) to a Gregorian date with optional time components
    /// @param jd Julian Day Number (JDN)
    /// @return A Jd2Dt object containing the Gregorian date and optional time components of the input JDN
    /// @details The algorithm used is Meeus', which is a fast and efficient method for converting between Julian Day Numbers and Gregorian dates.
    /// The method first adjusts the input JDN to account for the Gregorian calendar's starting date of October 15, 1582.
    /// It then uses the Meeus algorithm to compute the year, month, and day of the input JDN.
    /// Finally, the method extracts any time components from the fractional day and normalizes them to ensure they are within valid ranges.
    Jd2Dt jd_to_gregorian(double jd)
    {
        // Convert Julian Day to calendar date (Meeus algorithm)
        double jd_plus = jd + 0.5;
        long Z = static_cast<long>(std::floor(jd_plus));
        double F = jd_plus - static_cast<double>(Z);

        long A = Z;
        if (Z >= 2299161L) // use Gregorian calendar starting 1582-10-15
        {
            long alpha = static_cast<long>(std::floor((static_cast<double>(Z) - 1867216.25) / 36524.25));
            A = Z + 1 + alpha - alpha / 4;
        }

        long B = A + 1524;
        long C = static_cast<long>(std::floor((static_cast<double>(B) - 122.1) / 365.25));
        long D = static_cast<long>(std::floor(365.25 * static_cast<double>(C)));
        long E = static_cast<long>(std::floor((static_cast<double>(B - D)) / 30.6001));

        double day_decimal = static_cast<double>(B - D) - std::floor(30.6001 * static_cast<double>(E)) + F;
        int day = static_cast<int>(std::floor(day_decimal));
        int month = (E < 14) ? static_cast<int>(E - 1) : static_cast<int>(E - 13);
        int year = (month > 2) ? static_cast<int>(C - 4716) : static_cast<int>(C - 4715);

        // Extract time from fractional day
        double day_frac = day_decimal - static_cast<double>(day);
        double seconds_of_day = day_frac * 86400.0;
        int hour = static_cast<int>(seconds_of_day / 3600.0);
        int minute = static_cast<int>((seconds_of_day - hour * 3600.0) / 60.0);
        int second = static_cast<int>(std::round(seconds_of_day - hour * 3600.0 - minute * 60.0));

        // normalize seconds/minutes/hours (handle rounding)
        if (second >= 60)
        {
            second -= 60;
            ++minute;
        }
        if (minute >= 60)
        {
            minute -= 60;
            ++hour;
        }

        // helper for leap-year and days in month (choose Gregorian/Julian rules)
        auto is_leap = [](int y, bool gregorian)
        {
            if (gregorian)
                return (y % 4 == 0) && ((y % 100 != 0) || (y % 400 == 0));
            return (y % 4 == 0);
        };
        auto days_in_month = [&](int y, int m, bool gregorian)
        {
            if (m == 4 || m == 6 || m == 9 || m == 11)
                return 30;
            if (m == 2)
                return is_leap(y, gregorian) ? 29 : 28;
            return 31;
        };

        // If hour overflowed past 23, advance the day (and adjust month/year as needed)
        if (hour >= 24)
        {
            hour -= 24;
            ++day;
        }

        // Adjust day/month/year if day exceeds month length
        // Determine calendar type for the (year, month, day) using is_gregorian; loop handles cascades
        while (true)
        {
            bool gregorian_calendar = is_gregorian(year, month, day);
            int dim = days_in_month(year, month, gregorian_calendar);
            if (day <= dim)
                break;
            day -= dim;
            ++month;
            if (month > 12)
            {
                month = 1;
                ++year;
            }
        }

        // In rare cases rounding might have produced negative values (shouldn't normally happen),
        // but guard by normalizing downward as well.
        while (day <= 0)
        {
            --month;
            if (month < 1)
            {
                month = 12;
                --year;
            }
            bool gregorian_calendar = is_gregorian(year, month, 1);
            int dim = days_in_month(year, month, gregorian_calendar);
            day += dim;
        }

        return Jd2Dt{year, month, day, hour, minute, second};
    }
} // namespace jp
#endif // JULIAN_PERIOD_HPP_