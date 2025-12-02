# Astronomical Cycles: Solar, Metonic (Lunar), and Indiction

This note summarizes three historical astronomical/time cycles used in calendrical calculations and in the codebase (`src/index.mts`). It explains each cycle, its period, typical formulaic computation, examples, and usage.

## Solar Cycle (28 years)

- **Definition:** The Solar Cycle is a 28-year cycle used historically to track the weekday of dates in the Julian/Gregorian calendar and for certain calendrical datings (e.g., the Dominical Letter system). Over 28 years, the combination of leap years and weekdays repeats.
- **Period:** 28 years.
- **Computation (common implementation):**

```ts
// In `src/index.mts`:
// Position within 1..28, handles BCE via mathematical modulo
function solarNumber(year: number): number {
  return ( (year + 8) % 28 + 28 ) % 28 + 1;
}
```

- **Notes/Examples:**
  - For year 2000: `solarNumber(2000)` → ((2000 + 8) mod 28) + 1 = position in 1..28.
  - The `+8` shift is a conventional offset that makes the cycle align with historical reference points; different implementations sometimes use other offsets.

- **Usage:** Useful for computing weekday repeats and in composite cycles such as the Julian Period (which multiplies 28 with 19 and 15).

## Metonic (Lunar) Cycle (19 years)

- **Definition:** The Metonic cycle ~19 solar years ≈ 235 synodic months. After 19 years, lunar phases recur on (or near) the same calendar dates. It is widely used for lunisolar calendars (e.g., determining the dates of Easter, Hebrew calendar intercalation).
- **Period:** 19 years.
- **Computation (common implementation):**

```ts
// In `src/index.mts`:
// Position within 1..19, handles BCE via mathematical modulo
function lunarNumber(year: number): number {
  return ( (year % 19) + 19 ) % 19 + 1;
}
```

- **Notes/Examples:**
  - The Metonic cycle is the basis for adding leap months in lunisolar calendars: typically 7 leap months are added every 19 years.
  - `lunarNumber(2025)` will give the year position inside the 19-year Metonic cycle.

- **Usage:** Determining the lunar age for a given year, calculating epact, or deciding intercalary months in historical calendar systems.

## Indiction Cycle (15 years)

- **Definition:** The Indiction was a 15-year fiscal/administrative cycle used in the Roman/Byzantine world for tax and record-keeping purposes. In later medieval chronology it appears as a dating element.
- **Period:** 15 years.
- **Computation (common implementation):**

```ts
// In `src/index.mts`:
// Position within 1..15, handles BCE via mathematical modulo
function indictionNumber(year: number): number {
  return ( (year + 2) % 15 + 15 ) % 15 + 1;
}
```

- **Notes/Examples:**
  - The `+2` shift is conventional and makes the numbering align with historical reckoning; other sources may use a different offset depending on epoch.
  - Example: an indiction value of 1 corresponds to the first year of a 15-year indiction cycle.

- **Usage:** Primarily historical — used in dated documents and for computing the Julian Period element (often combined with solar and lunar positions).

## Julian Period (combined cycle)

- **Definition:** The Julian Period is a long cycle formed as the least common multiple of 15, 19, and 28, giving 7980 years. It was devised by Joseph Scaliger to produce a continuous year count (the Julian Day system is related historically but not identical).
- **Computation in code (example from `src/index.mts`):**

```ts
// Combine zero-based positions and reduce modulo 7980
const combined = 6916 * ind0 + 4200 * lun0 + 4845 * sol0;
const julianPeriodPos = ((combined % 7980) + 7980) % 7980 + 1; // 1..7980
```

- **Notes:** Coefficients (6916, 4200, 4845) are used to combine the 3 cycle offsets into a single Julian Period year index; they arise from solving congruences for a unique representation within 1..7980.

## Implementation notes & gotchas

- The codebase uses a mathematical modulo helper that normalizes negative years (BCE) correctly:

```ts
function mod(n: number, m: number) {
  return ((n % m) + m) % m;
}
```

- Offsets like `+8`, `+2`, or using raw `%` with adjustments are conventional choices to align the numeric position with historical references; if you change offsets, documented examples should be updated.

- These cycle computations return positions in 1..N (not zero-based) for easier human interpretation.

- TypeScript and runtime caveats:
  - The cycle functions accept integer year values; non-integer years should be validated or rejected.
  - BCE handling is implemented via the `mod` normalization above.

## References / Further reading

- Historical descriptions of the Metonic cycle and its use in calendars (e.g., Meeus — Astronomical Algorithms).
- Notes on the Indiction in medieval chronology literature.
- Internal: See `src/index.mts` for the exact implementations used in this project.

---

If you want this note named differently, expanded with diagrams, or to include worked numeric examples for specific years, tell me which years and I will add them.