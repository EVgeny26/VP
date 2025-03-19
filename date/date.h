#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct DATEBIRTH {
    private:
        unsigned short year;
        unsigned short day;
        unsigned short month;
    
        bool isValidDate(int d, int m, int y) const;
    
    public:
        DATEBIRTH(int d = 1, int m = 1, int y = 1970);
        DATEBIRTH(string date);
        DATEBIRTH(tm* localTime);

        unsigned short get_day() const;
        unsigned short get_month() const;
        unsigned short get_year() const;
        string to_str() const;

        bool operator>(const DATEBIRTH& other) const;
        bool operator<(const DATEBIRTH& other) const;
        bool operator>=(const DATEBIRTH& other) const;
        bool operator<=(const DATEBIRTH& other) const;
        bool operator==(const DATEBIRTH& other) const;
        bool operator!=(const DATEBIRTH& other) const;
    
        friend ostream& operator<<(ostream& os, const DATEBIRTH& date);
        friend istream& operator>>(istream& is, DATEBIRTH& date);
};

bool operator>(const DATEBIRTH& date, const tm* localTime);
bool operator>=(const DATEBIRTH& date, const tm* localTime);
bool operator<(const DATEBIRTH& date, const tm* localTime);
bool operator<=(const DATEBIRTH& date, const tm* localTime);
bool operator==(const DATEBIRTH& date, const tm* localTime);
bool operator!=(const DATEBIRTH& date, const tm* localTime);

bool operator>(const tm* localTime, const DATEBIRTH& date);
bool operator>=(const tm* localTime, const DATEBIRTH& date);
bool operator<(const tm* localTime, const DATEBIRTH& date);
bool operator<=(const tm* localTime, const DATEBIRTH& date);
bool operator==(const tm* localTime, const DATEBIRTH& date);
bool operator!=(const tm* localTime, const DATEBIRTH& date);


#endif // DATE_H