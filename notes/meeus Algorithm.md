The Meeus algorithm for calculating the Julian day (JD) from a calendar date involves adjusting the month and year (treating January and February as months 13 and 14 of the previous year) and then applying a formula that accounts for leap years and a constant offset. 

The formula is: 

JDN = \((int)(365.25*(Y+4716))+(int)(30.6001*(M+1))+D+B-1524.5\)

Steps for the Meeus algorithm Adjust month and year: 

If the month (\(M\)) is January or February, subtract 1 from the year (\(Y\)) and add 12 to the month.

Apply Gregorian calendar correction:If the date is on or after October 15, 1582 (Gregorian calendar), calculate a variable B using the formula: 

\(B=2-\text{int}(Y/100)+\text{int}(Y/400)\).

If the date is before October 15, 1582 (Julian calendar), set B = 0.Calculate Julian Day: Use the following formula, where D is the day of the month, and Y and M are the potentially adjusted year and month:

JDN = \((int)(365.25*(Y+4716))+(int)(30.6001*(M+1))+D+B-1524.5\)

Note that int() represents the integer (or floor) part of a number.This algorithm counts days starting from noon on January 1, 4713 BC. A JD ending in .5 corresponds to midnight, while a JD ending in .0 corresponds to noon. 

## Cycles: Solar, Metonic (Lunar), and Indiction

This project also uses several historical cycles when computing calendrical indexes and combined periods (see `src/index.mts`). Below is a compact reference, simple diagrams, and a quick lookup table mapping example years to their cycle positions.

### Short definitions

- **Solar Cycle (28 years):** weekday/leap-year pattern repeats every 28 years. Positions are 1..28.
- **Metonic (Lunar) Cycle (19 years):** lunar phases recur on the same calendar dates roughly every 19 years. Positions are 1..19.
- **Indiction Cycle (15 years):** a 15-year fiscal/dating cycle used historically in Roman/Byzantine records. Positions are 1..15.

### Mini diagrams

Solar (28):

[1]→[2]→...→[28]↺

Metonic (19):

[1]→[2]→...→[19]↺

Indiction (15):

[1]→[2]→...→[15]↺

### Code reference

Representative implementations in `src/index.mts`:

```ts
function solarNumber(year: number): number {
	return ((year + 8) % 28 + 28) % 28 + 1;
}

function lunarNumber(year: number): number {
	return ((year % 19) + 19) % 19 + 1;
}

function indictionNumber(year: number): number {
	return ((year + 2) % 15 + 15) % 15 + 1;
}
```

### Quick lookup table (examples)

| Year | Solar (1..28) | Metonic (1..19) | Indiction (1..15) | Julian Period (1..7980) |
|------:|:-------------:|:---------------:|:-----------------:|:------------------------:|
| 2000 | 21 | 6  | 8  | 6713 |
| 2025 | 18 | 12 | 3  | 6738 |
| 1582 | 23 | 6  | 10 | 6295 |
| 0    | 9  | 1  | 3  | 4713 |
| -44  | 21 | 14 | 4  | 4669 |

Values computed using the code's conventions and mathematical modulo normalization for negative years (BCE/astronomical year numbering). The Julian Period column is the combined position within the 7980-year Julian Period, computed from zero-based cycle offsets and coefficients in `src/index.mts`.

### Notes & tips

- Offsets (for example `+8` in the solar formula or `+2` in the indiction formula) are conventional; they align numeric results with historical reference epochs used in the code. If you change offsets, update examples accordingly.
- The modulo helper in the code normalizes negative years so that BCE values behave consistently:

```ts
function mod(n: number, m: number) {
	return ((n % m) + m) % m;
}
```

If you'd like, I can also add more worked examples for specific years, visual SVG diagrams, or a small script that prints a table for any range of years.