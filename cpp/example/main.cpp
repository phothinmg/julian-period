#include "./pcolor/pcolor.hpp"
#include "./gtjd.hpp"

using namespace pcolor;
using namespace jpapp;

int main()
{
    int options = 0;

    print("1. ", color_dark_green);
    print("Convert from Gregorian Date Time to JD and JDN.", color_yellow);
    println();

    print("2. ", color_dark_green);
    print("Convert from Julian Date or Julian Day Number to date time.", color_yellow);
    println();

    print("3. ", color_dark_green);
    print("Position of a year in Astronomical Cycles: [Solar, Metonic (Lunar),Indiction] and Julian Period", color_yellow);
    println();

    print("");
    println();

    print("Please choose a number from above [1,2,3]  : ", color_dark_green);
    cin >> options;

    switch (options)
    {
    case 1:
        println();
        dt_to_jd();
        break;
    case 2:
        println();
        jd_to_dt();
        break;
    case 3:
        println();
        j_p();
        break;
    }

    return 0;
}
