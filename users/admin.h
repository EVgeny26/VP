#ifndef ADMIN_H
#define ADMIN_H

#include "parent/human.h"
#include "user.h"
#include <string>

class Admin: public Human{
    humanVector users{};


public:
    Admin(string login, string password, string name, MYDATE birth, GENDER gender);
    Admin(const Human& human);
    ~Admin();

    void add_user(User user);
    void add_user();
    void del_user(int pos);
    void del_user(string login);
    void sorted(int pole, bool revers);

    //void filter();

    void pritall();
    bool loud(string);
    bool save(string);
};

#endif //ADMIN_h