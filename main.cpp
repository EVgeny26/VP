#include "menu/CMenu/CMenu.h"
#include "users/admin.h"
#include "users/user.h"

#include "menu/adminMenu.h"

#include <cmath>
#include <ctime>
#include <functional>

using namespace std;


int main() {
    // Admin admin{"Evgeny", DATEBIRTH{26,9,2006}, male, "MainAd", "12345678"};

    // CMenu *menu = getAdminMenu(admin);

    // while (menu->isRun()) {
    //     menu->runCommand();
    // }


    time_t currentTime = time(0);  // nullptr эквивалентно 0
    tm* localTime = localtime(&currentTime);
    DATEBIRTH date{localTime};
    cout<<date.to_str();
    return 0;
}