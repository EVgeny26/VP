#ifndef USER_H
#define USER_H

#include "parent/human.h"

class User : public Human {
public:
    User();
    User(string name, DATEBIRTH birth, GENDER gender, string login, string password);
    ~User();

    // Дружественные функции для ввода/вывода
    friend ostream& operator<<(ostream& os, const User& obj);
    friend istream& operator>>(istream& is, User& obj);
};

#endif



