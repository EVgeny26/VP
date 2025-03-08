#pragma once

#include "parent/human.h"

class User: public Human{
    


public:
    User(string name, DATEBIRTH birth, GENDER gender, string login, string password);
    ~User();
    friend ostream& operator<<(ostream& os, User& obj);

};

