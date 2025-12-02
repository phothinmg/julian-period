#ifndef JULIAN_PERIOD_HPP_
#define JULIAN_PERIOD_HPP_

#include <optional>
#include <cmath>

using namespace std;
namespace jp
{
    struct GregorianDateTime
    {
        int year;
        int month;
        int day;
        optional<int> hour = nullopt;
        optional<int> minute = nullopt;
        optional<int> seconds = nullopt;
    };
    struct Dt2Jd
    {
        double julianDay;
        int julianDayNumber;
    };
    struct Jd2Dt
    {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int seconds;
    };

    bool is_gregorian(const int &year, const int &month, const int &day)
    {
        return year > 1582 || (year == 1582 && (month > 10 || (month == 10 && day > 14)));
    }

    double INT(double d)
    {
        if (d > 0)
        {
            return floor(d);
        }
        if (d == floor(d))
        {
            return d;
        }
        return floor(d) - 1;
    }
    /// @brief Mathematical modulo that returns a value in [0, m-1] for any integer n (including negatives)
    double mod(int n, int m) { return ((n % m) + m) % m; }
    /// @brief Position of a year within the 28-year Solar Cycle (1..28), handles BCE (negative/zero years)
    int solar_number(const int &year)
    {
        return mod(year + 8, 28) + 1;
    }
    /// @brief Position of a year within the 19-year Metonic (Lunar) cycle (1..19), handles BCE
    int lunar_number(const int &year) { return mod(year, 19) + 1; }
    /// @brief Position of a year within the 15-year Indiction cycle (1..15), handles BCE
    int indiction_number(const int &year) { return mod(year + 2, 15) + 1; }
    /// @brief Compute position within the Julian Period (length 15*19*28 = 7980 years)
    /// @param year Year
    /// @return Position of year in current Julian Preoid
    int julian_period_year(const int &year)
    {
        int C15 = 15;
        int C19 = 19;
        int C28 = 28;
        int N = C15 * C19 * C28; // 7980

        int ind0 = indiction_number(year) - 1; // 0..14 zero-based cycle positions
        int lun0 = lunar_number(year) - 1;     // 0..18 zero-based cycle positions
        int sol0 = solar_number(year) - 1;     // 0..24 zero-based cycle positions

        int combined = 6916 * ind0 + 4200 * lun0 + 4845 * sol0; // Coefficients as in original formula, combine and reduce modulo N

        return mod(combined, N) + 1;
    }

    Dt2Jd gregorian_to_jd(int year, int month, int day, optional<int> hour = nullopt, optional<int> minute = nullopt, optional<int> seconds = nullopt, optional<float> tz_offset = nullopt)
    {
        int _hour = hour.value_or(12);
        int _minute = minute.value_or(0);
        int _seconds = seconds.value_or(0);

        double def = (_hour * 3600 + _minute * 60 + _seconds) / 86400;

        if (month < 3) // Adjust Jan/Feb to months 13/14 of previous year (Meeus / Zeller style)
        {
            year -= 1;
            month += 12;
        }

        int B = 0; // Gregorian correction (B). Use adjusted year/month when computing correction.
        if (is_gregorian(year, month, day))
        {
            int A = INT(year / 100);
            B = 2 - A + INT(A / 4);
        }

        int julianDayNumber = INT(365.25 * (year + 4716)) +
                              INT(30.6001 * (month + 1)) +
                              day +
                              B -
                              1524.5;
        double julianDay = julianDayNumber + def;
        return {
            julianDay, julianDayNumber};
    }
} // namespace jp
#endif // JULIAN_PERIOD_HPP_