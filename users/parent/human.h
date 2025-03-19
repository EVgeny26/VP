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

    friend ostream& operator<<(ostream& os, const DATEBIRTH& date);
    friend istream& operator>>(istream& is, DATEBIRTH& date);
};

enum GENDER {
    male,
    femail
};

ostream& operator<<(ostream& os, const GENDER& gender);
istream& operator>>(istream& is, GENDER& gender);

class Human {
private:
    unsigned short id{};
    string name;
    DATEBIRTH birth;
    GENDER gender;
    string login;
    string password;

public:
    Human(); 
    Human(string name, DATEBIRTH birth, GENDER gender, string login, string password);
    ~Human();
    void set_name(string name);
    void set_password(string password);

    string get_name() const; 
    string get_login() const; 
    string get_password() const; 
    DATEBIRTH get_datebirth() const; 
    GENDER get_gender() const;   
    unsigned short get_age();

    friend ostream& operator<<(ostream& os, const Human& human);
    friend istream& operator>>(istream& is, Human& human);
};

bool writeHumansToFile(const string& filename, const vector<Human>& humans);
bool readHumansFromFile(const string& filename, vector<Human>& humans);

#endif // HUMAN_H