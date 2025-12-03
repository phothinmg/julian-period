#include "../jp.hpp"
#include "./pcolor/pcolor.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

using namespace jp;

using namespace pcolor;

namespace jpapp
{

    void dt_to_jd()
    {
        int year, month, day; // gregorian to jd and jdn
        print("Gregorian DateTime ==> JD & JDN", color_yellow);
        println();
        cout << "Enter Year [";
        print("required", color_pink);
        cout << "] :  ";
        cin >> year; // input year

        cout << "Enter Month [";
        print("required", color_pink);
        cout << "] [1-12] : ";
        cin >> month;

        cout << "Enter Day [";
        print("required", color_pink);
        cout << "] [1-31] :  ";
        cin >> day;

        cin.ignore(); // Add this line to ignore the newline character

        cout << "Enter hour [";
        print("optional ", color_pink);
        print("default = 12", color_yellow);
        cout << "] [0-23] :  ";
        int hour = 12;
        string _h;
        getline(cin, _h);
        if (!_h.empty())
        {
            istringstream stream(_h);
            stream >> hour;
        }

        cout << "Enter minute [";
        print("optional ", color_pink);
        print("default = 0", color_yellow);
        cout << "] [0-59] :  ";
        int minute = 0;
        string _m;
        getline(cin, _m);
        if (!_m.empty())
        {
            istringstream stream(_m);
            stream >> minute;
        }

        cout << "Enter seconds [";
        print("optional ", color_pink);
        print("default = 0", color_yellow);
        cout << "] [0-59] :  ";
        int second = 0;
        string _s;
        getline(cin, _s);
        if (!_s.empty())
        {
            istringstream stream(_s);
            stream >> second;
        }

        cout << "Enter timezone offset [";
        print("optional ", color_pink);
        print("default = 0.0", color_yellow);
        cout << "] :  ";
        double tz = 0.0;
        string _t;
        getline(cin, _t);
        if (!_t.empty())
        {
            istringstream stream(_t);
            stream >> tz;
        }

        Dt2Jd j = gregorian_to_jd(year, month, day, hour, second, minute, tz);

        int jdn = j.julianDayNumber;
        double jd = j.julianDay;

        print("JDN : ", color_magenta);
        print_color(color_yellow);
        cout << fixed << setprecision(0) << jdn;
        print_color_reset();
        println();

        print("JD : ", color_magenta);
        print_color(color_yellow);
        cout << setprecision(15) << jd;
        print_color_reset();
        println(); // new line
    }

    void jd_to_dt()
    {
        double jd;
        print("Convert from Julian Date or Julian Day Number to date time.", color_dark_green);
        println();

        cout << "Enter JD or JDN [";
        print("required", color_pink);
        cout << "] :  ";
        cin >> jd; // jd or jdn

        Jd2Dt dt = jd_to_gregorian(jd);

        print("Year : ", color_magenta);
        print_color(color_yellow);
        cout << fixed << setprecision(0) << dt.year;
        print_color_reset();
        println();

        print("Month : ", color_magenta);
        print_color(color_yellow);
        cout << fixed << setprecision(0) << dt.month;
        print_color_reset();
        println();

        print("Day : ", color_magenta);
        print_color(color_yellow);
        cout << fixed << setprecision(0) << dt.day;
        print_color_reset();
        println();

        print("Hour : ", color_magenta);
        print_color(color_yellow);
        cout << fixed << setprecision(0) << dt.hour;
        print_color_reset();
        println();

        print("Minute : ", color_magenta);
        print_color(color_yellow);
        cout << fixed << setprecision(0) << dt.minute;
        print_color_reset();
        println();

        print("Seconds : ", color_magenta);
        print_color(color_yellow);
        cout << fixed << setprecision(0) << dt.seconds;
        print_color_reset();
        println();
    }
    void j_p()
    {
        int year;
        print("Position of a year withing astronomical cycles", color_dark_green);
        println();

        cout << "Enter Year [";
        print("required", color_pink);
        cout << "] :  ";
        cin >> year; // input year

        int sn = solar_number(year);
        int ln = lunar_number(year);
        int in = indiction_number(year);
        int jpn = julian_period_year(year);

        print_color(color_green);
        cout << fixed << setprecision(0) << year;
        print_color_reset();
        print(" is Year - ");
        print_color(color_green);
        cout << fixed << setprecision(0) << sn;
        print_color_reset();
        print(" in solar cycle.");
        print_color_reset();
        println();

        print_color(color_green);
        cout << fixed << setprecision(0) << year;
        print_color_reset();
        print(" is Year - ");
        print_color(color_green);
        cout << fixed << setprecision(0) << ln;
        print_color_reset();
        print(" in lunar cycle.");
        print_color_reset();
        println();

        print_color(color_green);
        cout << fixed << setprecision(0) << year;
        print_color_reset();
        print(" is Year - ");
        print_color(color_green);
        cout << fixed << setprecision(0) << in;
        print_color_reset();
        print(" in indiction cycle.");
        print_color_reset();
        println();

        print_color(color_green);
        cout << fixed << setprecision(0) << year;
        print_color_reset();
        print(" is Year - ");
        print_color(color_green);
        cout << fixed << setprecision(0) << jpn;
        print_color_reset();
        print(" in current Julian Peroid.");
        print_color_reset();
        println();
    }

}