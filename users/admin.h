#pragma once

#include "parent/human.h"
#include "user.h"
#include <vector>

class Admin: public Human{
    vector<User> users{};


public:
    Admin(string name, DATEBIRTH birth, GENDER gender, string login, string password);
    ~Admin();

    void add_user(User user);
    void del_user(int pos);
    void del_user(string login);
    void sorted(int pole, bool revers);
    //void filter();

    void pritall();
    void loud_from_file();
    void loud_to_file();
};
