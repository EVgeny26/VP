#include "menu/authMenu.h"

using namespace std;


int main() {
    CMenu* menu = getAuthMenu();
    while (menu->isRun()) {
        menu->runCommand();
    }
    delete menu;
    return 0;
}