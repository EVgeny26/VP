#include "CMenu/CMenu.h"
#include "CMenu/CMenuItem.h"
#include "../users/admin.h"
#include "adminMenu.h"

#include <functional>

using namespace std;

const int ITEMS_NUMBER = 7;

CMenu* getAdminMenu(Admin admin) {
    CMenuItem *items = new CMenuItem[ITEMS_NUMBER]{
        {"Print All Users", bind(&Admin::pritall, &admin)},
        {"Add User (interactive)", bind(static_cast<void (Admin::*)()>(&Admin::add_user), &admin)},
        {"Delete User (by position)", bind([&admin](){
           int pos;
           cout << "Enter position to delete: ";
           cin >> pos;
           admin.del_user(pos);
        })},
        {"Delete User (by login)", bind([&admin](){
           string login;
           cout << "Enter login to delete: ";
           cin >> login;
           admin.del_user(login);
        })},
        {"Sort Users",bind([&admin](){
            int pole;
            bool revers;
            cout << "Enter sort pole (0, 1, 2...): ";
            cin >> pole;
            cout << "Enter reverse (0 or 1): ";
            cin >> revers;
            admin.sorted(pole, revers);
        })},
        {"Load Users From File", bind([&admin](){admin.loud_from_file("usersInfo/users.bin");})},
        {"Save Users To File", bind([&admin](){admin.loud_to_file("usersInfo/users.bin");})}
    };

    CMenu* adminMenu = new CMenu("Admin Menu", items, ITEMS_NUMBER);
    return adminMenu;
}