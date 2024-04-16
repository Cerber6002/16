#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

struct Date {
    int day;
    int month;
    int year;

    Date() : day(0), month(0), year(0) {}

    bool isValidDate() const {
        if (month < 1 || month > 12)
            return false;
        if (day < 1 || day > 31)
            return false;
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
            return false;
        if (month == 2) {
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                if (day > 29)
                    return false;
            }
            else {
                if (day > 28)
                    return false;
            }
        }
        return true;
    }

    void newDate(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
        if (!isValidDate()) {
            throw invalid_argument("Invalid date!");
        }
    }

    int getDayOfWeek() const {
        return (day + month + year) % 7;
    }

    int calculateDifference(const Date& date) const {
        int days1 = year * 360 + month * 30 + day;
        int days2 = date.year * 360 + date.month * 30 + date.day;
        return abs(days2 - days1);
    }

    void printDate() const {
        const char* months[] = { "January", "February", "March", "April", "May", "June", "July",
                                "August", "September", "October", "November", "December" };
        cout << months[month - 1] << " " << day << ", " << year << endl;
    }

    bool operator<(const Date& other) const {
        if (year != other.year)
            return year < other.year;
        if (month != other.month)
            return month < other.month;
        return day < other.day;
    }
};

void sortDates(vector<Date>& dates) {
    sort(dates.begin(), dates.end());
}

int main() {
    vector<Date> dates;

    try {
        Date d1, d2, d3;
        d1.newDate(12, 3, 2023);
        d2.newDate(5, 10, 2022);
        d3.newDate(28, 12, 2024);

        dates.push_back(d1);
        dates.push_back(d2);
        dates.push_back(d3);
    }
    catch (const invalid_argument& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    sortDates(dates);

    cout << "Sorted Dates:" << endl;
    for (const auto& date : dates) {
        date.printDate();
    }

    return 0;
}
