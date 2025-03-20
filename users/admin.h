#ifndef ADMIN_H
#define ADMIN_H

#include "parent/human.h"
#include "user.h"
#include <vector>
#include <string>

class Admin: public Human{
    vector<User> users{};


public:
    Admin(string name, DATE birth, GENDER gender, string login, string password);
    ~Admin();

    void add_user(User user);
    void add_user();
    void del_user(int pos);
    void del_user(string login);
    void sorted(int pole, bool revers);

    //void filter();

    void pritall();
    bool loud_from_file(string);
    bool loud_to_file(string);
};

#endif //ADMIN_h