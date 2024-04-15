#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Date {
    int day;
    int month;
    int year;

    static const int DAYS_IN_MONTH[];
    static const int DAYS_IN_YEAR;

    bool isValidDate() const {
        if (year < 0 || month < 1 || month > 12 || day < 1)
            return false;
        if (month == 2 && isLeapYear(year)) {
            return day <= 29;
        } else {
            return day <= DAYS_IN_MONTH[month - 1];
        }
    }

    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    void newDate(int d, int m, int y) {
        if (m >= 1 && m <= 12 && d >= 1 && d <= DAYS_IN_MONTH[m - 1] && (m != 2 || (m == 2 && isLeapYear(y)))) {
            day = d;
            month = m;
            year = y;
        } else {
            // Invalid date, do not set
            cout << "Некорректная дата: " << d << "-" << m << "-" << y << endl;
        }
    }

    int getDayOfWeek() const {
        int y = year;
        int m = month;
        if (m < 3) {
            m += 12;
            y--;
        }
        int h = (day + (13 * (m + 1)) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
        return h;
    }

    int calculateDifference(const Date& date) const {
        int days1 = day + month * DAYS_IN_MONTH[month - 1] + year * DAYS_IN_YEAR;
        int days2 = date.day + date.month * DAYS_IN_MONTH[date.month - 1] + date.year * DAYS_IN_YEAR;
        return abs(days2 - days1);
    }

    void printDate() const {
        const char* months[] = {"Январь", "Февраль", "Март", "Апрель", "Май", "Июнь", "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};
        cout << months[month - 1] << " " << day << ", " << year;
    }

    bool operator<(const Date& other) const {
        if (year != other.year)
            return year < other.year;
        if (month != other.month)
            return month < other.month;
        return day < other.day;
    }
};

const int Date::DAYS_IN_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int Date::DAYS_IN_YEAR = 365;

int main() {
    vector<Date> dates = {{1, 1, 2023}, {15, 3, 2022}, {10, 6, 2024}};

    sort(dates.begin(), dates.end());

    for (const auto& date : dates) {
        if (date.isValidDate()) {
            date.printDate();
            cout << endl;
        } else {
            cout << "Некорректная дата: ";
            date.printDate();
            cout << endl;
        }
    }

    return 0;
}
