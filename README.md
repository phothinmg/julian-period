# Julian Period

## Overview

This is a part of the project [Thetkarit][thetkarit] , a dual-language library for Burmese calendar calculations and astronomical computations.

A small and zero-dependency library for working with [Julian Day][jd] , [Julian Day Number][jdn] , [Solar cycle][solar_cycle] , [Lunar cycle (Metonic cycle)][lunar_cycle] , [Indiction cycle][indiction_cycle] , [Julian Period][julian_period] and design to handles historical date calculations.

## Use

### Node Js

#### Install and import

Install :

```bash
npm i @phothinmaung/julian-period
```

Import :

```ts
import jp from "@phothinmaung/julian-period";
```

### C++

![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/phothinmg/julian-period/cmake-multi-platform.yml?style=for-the-badge&logo=cmake&label=CMake%20on%20multiple%20platforms)

#### Example C++ program

Clone the repository :

```text
git clone https://github.com/phothinmg/julian-period.git
cd julian-period
```

- **Build & Run With CMake (recommended)**

```text
mkdir build
cd build
cmake ..
make
./jpapp # Running example
```

- **Quick compile with g++**

```text
g++ -std=c++17 cpp/example/main.cpp -Ijp -o jpapp
./jpapp
```

## API

[thetkarit]: https://github.com/phothinmg/thetkarit
[julian_period]: https://en.wikipedia.org/wiki/Julian_day#External_links:~:text=%5Bedit%5D-,Julian%20Period,-%5Bedit%5D
[solar_cycle]: https://en.wikipedia.org/wiki/Solar_cycle_/(calendar/)
[lunar_cycle]: https://en.wikipedia.org/wiki/Metonic_cycle
[indiction_cycle]: https://en.wikipedia.org/wiki/Indiction
[jd]: https://en.wikipedia.org/wiki/Julian_day
[jdn]: https://en.wikipedia.org/wiki/Julian_day#:~:text=The-,Julian%20day%20number,-(JDN)%20has%20the
