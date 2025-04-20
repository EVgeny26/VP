#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct MYDATE {
    private:
        unsigned short year;
        unsigned short day;
        unsigned short month;
    
        bool isValidDate(int d, int m, int y) const;
    
    public:
        MYDATE(int d = 1, int m = 1, int y = 1970);
        MYDATE(string date);
        MYDATE(tm* localTime);

        unsigned short get_day() const;
        unsigned short get_month() const;
        unsigned short get_year() const;
        string to_str() const;

        bool operator>(const MYDATE& other) const;
        bool operator<(const MYDATE& other) const;
        bool operator>=(const MYDATE& other) const;
        bool operator<=(const MYDATE& other) const;
        bool operator==(const MYDATE& other) const;
        bool operator!=(const MYDATE& other) const;
    
        friend ostream& operator<<(ostream& os, const MYDATE& date);
        friend istream& operator>>(istream& is, MYDATE& date);
};

bool operator>(const MYDATE& date, const tm* localTime);
bool operator>=(const MYDATE& date, const tm* localTime);
bool operator<(const MYDATE& date, const tm* localTime);
bool operator<=(const MYDATE& date, const tm* localTime);
bool operator==(const MYDATE& date, const tm* localTime);
bool operator!=(const MYDATE& date, const tm* localTime);

bool operator>(const tm* localTime, const MYDATE& date);
bool operator>=(const tm* localTime, const MYDATE& date);
bool operator<(const tm* localTime, const MYDATE& date);
bool operator<=(const tm* localTime, const MYDATE& date);
bool operator==(const tm* localTime, const MYDATE& date);
bool operator!=(const tm* localTime, const MYDATE& date);


#endif // DATE_H