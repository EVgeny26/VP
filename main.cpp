#include "menu/CMenu/CMenu.h"
#include "users/admin.h"
#include "users/user.h"
#include "menu/adminMenu.h"
#include "menu/userMenu.h"
#include "controlEnter/control.h"

#include <functional>

using namespace std;


int main() {
    Admin admin{ "MainAd", "12345678", "Evgeny", MYDATE{26,9,2006}, male};
    User user{"Vov", "12345678", "Vova", MYDATE{26,9,2006}, male};

    cout<<"Выберете меню:\n";
    bool whatMenu=getCorNumDiaposone(0,1);
    CMenu *menu;
    if(whatMenu)menu = getAdminMenu(admin);
    else menu = getUserMenu(user);

    while (menu->isRun()) {
        menu->runCommand();
    }
    delete menu;
    return 0;
}