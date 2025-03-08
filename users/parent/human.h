#pragma once

#include <iostream>
#include <string>

using namespace std;

struct DATEBIRTH{
private:
    unsigned short year;
    unsigned short day;
    unsigned short month;
    bool isValidDate(int y, int m, int d) const {
        if (y < 1 || m < 1 || m > 12 || d < 1) {
            return 0;
        }
        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
            daysInMonth[2] = 29;
        }
        return d <= daysInMonth[m];
    }

public:
    DATEBIRTH(int y = 1970, int m = 1, int d = 1) : year(y), month(m), day(d) {
        if (!isValidDate(year, month, day)) {
            std::cerr << "Ошибка: Некорректная дата. Установлена дата по умолчанию (1970-01-01)." << std::endl;
            year = 1970;
            month = 1;
            day = 1;
        }
    }
    unsigned short get_day(){return day;}
    unsigned short get_month(){return month;}
    unsigned short get_year(){return year;}
};

class Human{
    private:

        enum GENDER{
            main, femail
        };


        string name{};
        DATEBIRTH birth{};
        GENDER gender;
        string login{};
        string password{};

    public:
        Human(string name, DATEBIRTH birth, GENDER gender, string login, string password);
        ~Human();
        void set_name(string name);
        void set_password(string password);

        string get_name();
        string get_login();
        DATEBIRTH get_datebirth();
        unsigned short get_age();
};

