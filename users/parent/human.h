// #ifndef HUMAN_H
// #define HUMAN_H

// #pragma once

// #include <iostream>
// #include <string>

// #endif

// using namespace std;

// struct DATEBIRTH{
// private:
//     unsigned short year;
//     unsigned short day;
//     unsigned short month;
//     bool isValidDate(int d, int m, int y) const {
//         if (y < 1 || m < 1 || m > 12 || d < 1) {
//             return 0;
//         }
//         int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//         if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
//             daysInMonth[2] = 29;
//         }
//         return d <= daysInMonth[m];
//     }

// public:
//     DATEBIRTH(int d = 1, int m = 1, int y = 1970) : year(y), month(m), day(d) {
//         if (!isValidDate(day, month, year)) {
//             cerr << "Ошибка: Некорректная дата. Установлена дата по умолчанию (01-01-1970)." << endl;
//             year = 1970;
//             month = 1;
//             day = 1;
//         }
//     }
//     unsigned short get_day(){return day;}
//     unsigned short get_month(){return month;}
//     unsigned short get_year(){return year;}
//     string to_str(){
//         return string{to_string(day)+'.'+to_string(month)+'.'+to_string(year)};
//     }
//     bool operator>(const DATEBIRTH& other) const{
//         if(year==other.year){
//             if(month==other.month){
//                 return day>other.day;
//             }return month>other.month;
//         }return year>other.year;
//     }
// };

// enum GENDER{
//     male, femail
// };


// class Human{
//     private:
//         string name{};
//         DATEBIRTH birth{};
//         GENDER gender;
//         string login{};
//         string password{};

//     public:
//         Human(string name, DATEBIRTH birth, GENDER gender, string login, string password);
//         ~Human();
//         void set_name(string name);
//         void set_password(string password);

//         string get_name();
//         string get_login();
//         string get_password();
//         DATEBIRTH get_datebirth();
//         unsigned short get_age();
//         GENDER get_gender();
// };



#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct DATEBIRTH {
private:
    unsigned short year;
    unsigned short day;
    unsigned short month;

    bool isValidDate(int d, int m, int y) const;

public:
    DATEBIRTH(int d = 1, int m = 1, int y = 1970);
    unsigned short get_day() const;
    unsigned short get_month() const;
    unsigned short get_year() const;
    string to_str() const;
    bool operator>(const DATEBIRTH& other) const;

    // Дружественные функции для ввода/вывода
    friend ostream& operator<<(ostream& os, const DATEBIRTH& date);
    friend istream& operator>>(istream& is, DATEBIRTH& date);
};

enum GENDER {
    male,
    femail
};

// Дружественные функции для ввода/вывода GENDER
ostream& operator<<(ostream& os, const GENDER& gender);
istream& operator>>(istream& is, GENDER& gender);

class Human {
private:
    string name;
    DATEBIRTH birth;
    GENDER gender;
    string login;
    string password;

public:
    Human(); 
    Human(string name, DATEBIRTH birth, GENDER gender, string login, string password);
    ~Human();  // Деструктор лучше объявлять даже если он пустой, для явности
    void set_name(string name);
    void set_password(string password);

    string get_name() const;  // Добавлено const
    string get_login() const; // Добавлено const
    string get_password() const; // Добавлено const
    DATEBIRTH get_datebirth() const; // Добавлено const
    GENDER get_gender() const;   // Добавлено const
    unsigned short get_age();

    // Дружественные функции для ввода/вывода
    friend ostream& operator<<(ostream& os, const Human& human);
    friend istream& operator>>(istream& is, Human& human);
};

// Функции для записи и чтения массива Human из файла
bool writeHumansToFile(const string& filename, const vector<Human>& humans);
bool readHumansFromFile(const string& filename, vector<Human>& humans);

#endif // HUMAN_H