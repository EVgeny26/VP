#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct DATE {
    private:
        unsigned short year;
        unsigned short day;
        unsigned short month;
    
        bool isValidDate(int d, int m, int y) const;
    
    public:
        DATE(int d = 1, int m = 1, int y = 1970);
        DATE(string date);
        DATE(tm* localTime);

        unsigned short get_day() const;
        unsigned short get_month() const;
        unsigned short get_year() const;
        string to_str() const;

        bool operator>(const DATE& other) const;
        bool operator<(const DATE& other) const;
        bool operator>=(const DATE& other) const;
        bool operator<=(const DATE& other) const;
        bool operator==(const DATE& other) const;
        bool operator!=(const DATE& other) const;
    
        friend ostream& operator<<(ostream& os, const DATE& date);
        friend istream& operator>>(istream& is, DATE& date);
};

bool operator>(const DATE& date, const tm* localTime);
bool operator>=(const DATE& date, const tm* localTime);
bool operator<(const DATE& date, const tm* localTime);
bool operator<=(const DATE& date, const tm* localTime);
bool operator==(const DATE& date, const tm* localTime);
bool operator!=(const DATE& date, const tm* localTime);

bool operator>(const tm* localTime, const DATE& date);
bool operator>=(const tm* localTime, const DATE& date);
bool operator<(const tm* localTime, const DATE& date);
bool operator<=(const tm* localTime, const DATE& date);
bool operator==(const tm* localTime, const DATE& date);
bool operator!=(const tm* localTime, const DATE& date);


#endif // DATE_H