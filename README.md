**Julian Period**

- **Description**: A small library and example tools for working with Julian Day (JD), Julian Day Number (JDN), and the Julian Period. Includes C++ utilities in `jp/` for conversions between Gregorian dates and Julian days, and a TypeScript package in the repository root.
- **License**: ISC
- **Author**: Pho Thin Mg (`phothinmg@disroot.org`)

**Repository Layout**
- **`jp/`**: C++ header implementing Julian period utilities (`jp.hpp`).
- **`jp-example/`**: C++ example that demonstrates converting Gregorian dates to JD/JDN.
- **TypeScript package**: Top-level `package.json`, `src/` and `index.ts` (TypeScript build and tooling configured).

**Quick Build & Run (C++ example)**
- **With CMake (recommended)**:

```
mkdir -p build
cd build
cmake ..
cmake --build .
# If CMake configured an executable, run it from build or as instructed by CMake output
```

- **Quick compile with g++** (if you just want to run the example directly):

```
g++ -std=c++17 jp-example/main.cpp -Ijp -o jp-example/jp-example
./jp-example/jp-example
```

**TypeScript package**
- Install dependencies and build:

```
npm install
npm run build
```

- Formatting and checks (this repo uses Biome):

```
npm run fmt
npm run lint
```

**Usage (example)**
- The C++ example (`jp-example/main.cpp`) prompts for year/month/day and optional time and prints the JDN and JD. Typical session:

```
Enter Year [required] : 2025
Enter Month [required] [1-12] : 3
Enter Day [required] [1-31] : 14
Enter hour [optional default = 12] [0-23] :
JDN : 2460024
JD  : 2460024.000000000000000
```

**API summary (C++ `jp/jp.hpp`)**
- `jp::gregorian_to_jd(year, month, day, hour?, minute?, seconds?, tz_offset?)` : converts a Gregorian date/time to a `Dt2Jd` containing `julianDay` (double) and `julianDayNumber` (int).
- `jp::jd_to_gregorian(jd)` : converts a Julian Day (JD) back to a Gregorian date/time (`Jd2Dt`).
- `jp::julian_period_year(year)` : returns the position of the year inside the 7980-year Julian Period.

**Notes & Contributing**
- Ignore `.notes` and `.vscode` when browsing or packaging — they are not part of the public API.
- Contributions welcome: open an issue or PR with tests and a short description of the change.

**Contact**
- `phothinmg@disroot.org` — author metadata is also in `package.json`.
