#include "user.h"
#include <iostream>

using namespace std;

User::User(): Human(){}
User::User(string name, DATEBIRTH birth, GENDER gender, string login, string password)
    : Human(name, birth, gender, login, password) {}

User::~User() {}

// Дружественная функция для записи User в бинарный файл
ostream& operator<<(ostream& os, const User& obj) {
    // Используем оператор << для Human, чтобы записать общие поля
    os << static_cast<const Human&>(obj);
    return os;
}

// Дружественная функция для чтения User из бинарного файла
istream& operator>>(istream& is, User& obj) {
    // Используем оператор >> для Human, чтобы прочитать общие поля
    is >> static_cast<Human&>(obj);
    return is;
}