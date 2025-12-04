# Julian Period

## Overview

A small and zero-dependency library for working with [Julian Day][jd] , [Julian Day Number][jdn] , [Solar cycle][solar_cycle] , [Lunar cycle (Metonic cycle)][lunar_cycle] , [Indiction cycle][indiction_cycle] , [Julian Period][julian_period] and design to handles historical date calculations.

## Use

### Node Js

**Install :**

```bash
npm i @phothinmaung/julian-period
```

**Import :**

```ts
import jp from "@phothinmaung/julian-period";
console.log(jp.solarNumber(2025));
```

OR

```js
const jp = require("@phothinmaung/julian-period");
console.log(jp.solarNumber(2025));
```

### ESM Import

```js
import julianPeriod from "https://esm.run/@phothinmaung/julian-period";
const jp = julianPeriod.default;
console.log(jp.solarNumber(2025));
```

### Browser

```html
<script src="https://cdn.jsdelivr.net/npm/@phothinmaung/julian-period@0.1.1/cdn/julianPeriod.min.js"></script>
```

```html
<script>
  const ln = jp.solarNumber(2025);
  console.log(ln);
</script>
```

OR

```html
<script type="module">
  import julianPeriod from "https://cdn.jsdelivr.net/npm/@phothinmaung/julian-period@0.1.1/+esm";
  const jp = julianPeriod.default;
  console.log(jp.solarNumber(2025));
</script>
```

## API

### Functions

1. `jp.solarNumber(year:number):number`
   Position of a year within the 28-year Solar Cycle (1..28)

2. `jp.lunarNumber(year:number):number`
   Position of a year within the 19-year Metonic (Lunar) cycle (1..19)

3. `jp.indictionNumber(year:number):number`
   Position of a year within the the 15-year Indiction cycle (1..15)

4. `jp.julianPeriodYearNumber(year:number):number`
   Compute position within the Julian Period (length 15*19*28 = 7980 years)

5. `jp.gregorianToJD(date:GregorianDateTime):{julianDay: number, julianDayNumber: number}`
   Computes the Julian Day Number (JDN) and Julian Day (JD) from a Gregorian date.

6. `jp.jdToGregorian(jd: number): GregorianDateTime`
   Converts a Julian Day Number (JDN) to a Gregorian date.

### Types

```ts
interface GregorianDateTime {
  year: number;
  month: NumberInRange<1, 12>;
  day: NumberInRange<1, 31>;
  hour?: NumberInRange<0, 23>;
  minute?: NumberInRange<0, 59>;
  second?: NumberInRange<0, 59>;
}
```

## License

[Apache-2.0][file-license] © [Pho Thin Maung][ptm]

<!--  -->

[file-license]: LICENSE
[ptm]: https://github.com/phothinmg
[thetkarit]: https://github.com/phothinmg/thetkarit
[julian_period]: https://en.wikipedia.org/wiki/Julian_day#External_links:~:text=%5Bedit%5D-,Julian%20Period,-%5Bedit%5D
[solar_cycle]: https://en.wikipedia.org/wiki/Solar_cycle_/(calendar/)
[lunar_cycle]: https://en.wikipedia.org/wiki/Metonic_cycle
[indiction_cycle]: https://en.wikipedia.org/wiki/Indiction
[jd]: https://en.wikipedia.org/wiki/Julian_day
[jdn]: https://en.wikipedia.org/wiki/Julian_day#:~:text=The-,Julian%20day%20number,-(JDN)%20has%20the
