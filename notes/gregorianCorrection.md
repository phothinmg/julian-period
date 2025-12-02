## Purpose of A and B: The Gregorian Correction

The intermediate values A and B are used exclusively in the Gregorian calendar calculation to implement the specific Gregorian leap year rules, which differ from the simpler Julian calendar rules.

Here is the breakdown of why those calculations are necessary:

The basic Julian calendar rule adds a leap day every 4 years. The Gregorian calendar refined this to make the average year length closer to the actual solar year. The Gregorian rules are:

- A year is a leap year if it is evenly divisible by 4.
- EXCEPT if it is also evenly divisible by 100, then it is a common year.
- BUT if it is also evenly divisible by 400, it is a leap year again.

The A and B calculations incorporate these exceptions into the main formula using clever integer arithmetic, avoiding complex conditional logic.

`A = INT(Y / 100)`

A calculates the century number (the first two digits of the year for years >= 100). This value is used to identify years that are evenly divisible by 100, which are the exception years in the Gregorian system (e.g., 1700, 1800, 1900, 2100).

`B = 2 - A + INT(A / 4)`

The value B is a correction factor that adjusts the total day count in the main formula.
INT(A / 4) adds back the leap day for years divisible by 400 (e.g., in century 20 (2000), `A/4 = 5`, adding 5 days for the 5 leap centuries that occurred).

- A subtracts the leap day for the centurial years that are not divisible by 400 (e.g., 1900).
  The 2 is a constant offset required to make the whole formula align correctly with the historical Julian Date epoch (JD 0 on Jan 1, 4713 BC) when accounting for the 10 days that were skipped during the Gregorian reform.
  In the final Julian Day Number formula, the B term effectively adds or subtracts the correct number of days skipped by the Gregorian reform and rules to ensure the resulting JD number is a continuous count that matches the proleptic Gregorian calendar date.
  If you were calculating the Julian Day Number for a date before the adoption of the Gregorian calendar (e.g., in the pure Julian calendar system), you would simply set `B = 0`.
