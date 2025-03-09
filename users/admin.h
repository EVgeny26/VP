#ifndef ADMIN_H
#define ADMIN_H

#include "parent/human.h"
#include "user.h"
#include <vector>
#include <string>



class Admin: public Human{
    vector<User> users{};
    string filename;


public:
    Admin(string name, DATEBIRTH birth, GENDER gender, string login, string password);
    ~Admin();

    void add_user(User user);
    void del_user(int pos);
    void del_user(string login);
    void sorted(int pole, bool revers);

    string get_filename();
    //void filter();

    void pritall();
    bool loud_from_file();
    bool loud_to_file();
};

#endif //ADMIN_h