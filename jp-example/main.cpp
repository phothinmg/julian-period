#include "../jp/jp.hpp"
#include "./pcolor/pcolor.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

using namespace jp;

using namespace pcolor;

int main()
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

    Dt2Jd j = gregorian_to_jd(year, month, day);

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

    return 0;
}
