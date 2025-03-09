#include "user.h"
#include <iostream>
#include <iomanip>

using namespace std;

User::User(): Human(){}
User::User(string name, DATEBIRTH birth, GENDER gender, string login, string password)
    : Human(name, birth, gender, login, password) {}

User::~User() {}

int CountRu(string str){
    int count=0;
    for(int i=0;i<str.length();i++){
        if(str[i]<0){count++;i++;}
    }return count;
}

void User::printToConsole(ostream& os, int indents[5]) {
    os<<setfill(' ');
    os <<left<<'|'<< setw(indents[0]+CountRu(get_login())) << get_login() <<'|'<< setw(indents[1]+CountRu(get_name())) << get_name() <<'|'<< setw(indents[2]) << get_datebirth().to_str();
    os <<'|'<< setw(indents[3]) << (get_gender() == male ? "Male" : "Female") <<'|'<< setw(indents[4]+CountRu(get_password())) << get_password() <<'|'<< endl;
}

// Дружественная функция для записи User в бинарный файл
ostream& operator<<(ostream& os, const User& obj) {
    os << static_cast<const Human&>(obj);
    return os;
}

// Дружественная функция для чтения User из бинарного файла
istream& operator>>(istream& is, User& obj) {
    // Используем оператор >> для Human, чтобы прочитать общие поля
    is >> static_cast<Human&>(obj);
    return is;
}