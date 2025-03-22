#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../../date/date.h"

using namespace std;

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
    MYDATE birth;
    GENDER gender;
    string login;
    string password;

public:
    Human(); 
    Human(string name, MYDATE birth, GENDER gender, string login, string password);
    ~Human();
    void set_name(string name);
    void set_password(string password);

    string get_name() const; 
    string get_login() const; 
    string get_password() const; 
    MYDATE get_DATE() const; 
    GENDER get_gender() const;   
    unsigned short get_age();
    void get_info();

    friend ostream& operator<<(ostream& os, const Human& human);
    friend istream& operator>>(istream& is, Human& human);
};

bool writeHumansToFile(const string& filename, const vector<Human>& humans);
bool readHumansFromFile(const string& filename, vector<Human>& humans);

#endif // HUMAN_H