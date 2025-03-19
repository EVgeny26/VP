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
    cout<<localTime->tm_mday<<' '<<localTime->tm_mon<<' '<<localTime->tm_year<<endl;
    DATEBIRTH date{"19.3.2025"};
    cout<<(date<=localTime);
    return 0;
}