#include "../jp/jp.hpp"

#include <iostream>
#include <iomanip>

using namespace std;

using namespace jp;

int main()
{
    int year, month, day;
    cout << "Enter Year :  ";
    cin >> year;
    cout << "Enter Month :  ";
    cin >> month;
    cout << "Enter Day :  ";
    cin >> day;

    jp::Dt2Jd j = jp::gregorian_to_jd(year, month, day);

    int jdn = j.julianDayNumber;
    double jd = j.julianDay;

    cout << "jdn : " << std::setw(6) << std::setfill('0') << jdn << endl;
    cout << " jd : " << std::setprecision(10) << std::fixed << jd << endl;

    return 0;
}
