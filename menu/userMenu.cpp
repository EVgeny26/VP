#include "CMenu/CMenu.h"
#include "CMenu/CMenuItem.h"
#include "../users/user.h"
#include "userMenu.h"
#include "../controlEnter/control.h"

#include <functional>
#include <iostream>

using namespace std;

void returnToMainMenu() {
        cout << "Returning to main menu...\n";
}

CMenu* getUserMenu(User& user){

    // --- Подменю Вывод заметок ---
    const int displayNotesItemsAmount=4;
    CMenuItem *displayNotesItems = new CMenuItem[displayNotesItemsAmount]{
        {"All Notes", bind(&User::printNotes, &user)},
        {"Completed Notes for Today", bind([](User& user) {
            user.get_bot()->notes_today();
        }, ref(user))},
        {"Notes for a Specific Day", bind([](User& user){
                MYDATE date = getCorDate();
                user.get_bot()->notes_day(date);
            }, ref(user))
        },
        {"Return to Main Menu", returnToMainMenu}
    };
    CMenu* displayNotesMenu = new CMenu("Display Notes Menu", displayNotesItems, displayNotesItemsAmount);

    // --- Подменю Удаление заметок ---
    const int deleteNotesItemsNumberAmount=5;
    CMenuItem *deleteNotesItems = new CMenuItem[deleteNotesItemsNumberAmount]{
        {"By Position", bind([](User& user){
                cout << "Enter position to delete: ";
                int position=getCorNum();
                user.get_bot()->pop_note(position-1);
            }, ref(user))
        },
        {"Completed by Position", bind([](User& user){
                    cout << "Enter position of completed note to delete: ";
                    int position=getCorNum();
                    user.get_bot()->del_note_completed(position-1);
            }, ref(user))
        },
        {"All Completed", bind([](User& user){
                    user.get_bot()->del_all_completed();
            }, ref(user))
        },
        {"All Notes",  bind([](User& user){
                    user.get_bot()->del_all_notes();
            }, ref(user))
        },
        {"Return to Main Menu", returnToMainMenu}
    };
    CMenu *deleteNotesMenu = new CMenu("Delete Notes Menu", deleteNotesItems, deleteNotesItemsNumberAmount);

    // --- Подменю Какой сегодня праздник ---
    const int holidayItemsAmount=3;
    CMenuItem *holidayItems = new CMenuItem[holidayItemsAmount]{
        {"Today", bind([](User& user) {
                user.get_bot()->getWhatDayIsToday();
        }, ref(user))},
        {"For a Specific Day", bind([](User& user){
                MYDATE date = getCorDate();
                user.get_bot()->getWhatDayIs(date);
            }, ref(user))
        },
        {"Return to Main Menu", returnToMainMenu}
    };
    CMenu *holidayMenu = new CMenu("Holiday Menu", holidayItems, holidayItemsAmount);

    // --- Подменю Изменение данных пользователя ---
    const int editProfileItemsAmount=3;
    CMenuItem *editProfileItems = new CMenuItem[editProfileItemsAmount]{
        {"Name", bind([](User& user){
                cout << "Enter new name: ";
                string newName=getCorName();
                user.set_name(newName);
            }, ref(user))
        },
        {"Password", bind([](User& user){
                cout << "Enter new password: ";
                string newPassword=getCorPassword();
                user.set_password(newPassword);
            }, ref(user))
        },
        {"Return to Main Menu", returnToMainMenu}
    };
    CMenu *editProfileMenu = new CMenu("Edit Profile Menu", editProfileItems, editProfileItemsAmount);

    // --- Главное меню ---
    const int mainMenuItemsAmount=7;
    CMenuItem *mainMenuItems = new CMenuItem[mainMenuItemsAmount]{
        {"Display Notes", bind(&CMenu::runCommand, displayNotesMenu)},
        {"Add Note", bind([](User& user){
                cout << "Enter date:\n";
                MYDATE date=getCorDate();
                
                string message;
                cout << "Enter message: ";
                getline(cin >> ws, message);

                NOTE note(date, message);
                user.get_bot()->add_note(note);
        }, ref(user))},
        {"Delete Note", bind(&CMenu::runCommand, deleteNotesMenu)},
        {"What's Today's Holiday?", bind(&CMenu::runCommand, holidayMenu)},
        {"Edit User Profile", bind(&CMenu::runCommand, editProfileMenu)},
        {"Display User Data", bind(&User::get_info, &user)},
        {"Выйти", {}}
    };
    CMenu *userMenu = new CMenu("Main Menu", mainMenuItems, mainMenuItemsAmount);
    
    // return displayNotesMenu;
    return userMenu;
}