#include "CMenu/CMenu.h"
#include "CMenu/CMenuItem.h"
#include "../users/user.h"
#include "userMenu.h"

#include <functional>
#include <iostream>

using namespace std;

void returnToMainMenu() {
        cout << "Returning to main menu...\n";
}

CMenu* getUserMenu(User& user){
    user.loudBot();
    CHATBOT* chatbot = user.get_bot();

    // --- Подменю Вывод заметок ---
    const int displayNotesItemsAmount=4;
    CMenuItem *displayNotesItems = new CMenuItem[displayNotesItemsAmount]{
        {"All Notes", bind(&User::printNotes, &user)},
        {"Completed Notes for Today", bind([](User& user) {
            user.printCompletedNotes();
        }, ref(user))},
        {"Notes for a Specific Day", bind([](User& user){
                int day, month, year=1904;
                cout << "Enter day: ";
                cin >> day;
                cout << "Enter month: ";
                cin >> month;
                MYDATE date = {day, month, year};
                user.printNotesDay(date);
            }, ref(user))
        },
        {"Return to Main Menu", returnToMainMenu}
    };
    CMenu* displayNotesMenu = new CMenu("Display Notes Menu", displayNotesItems, displayNotesItemsAmount);

    // --- Подменю Удаление заметок ---
    const int deleteNotesItemsNumberAmount=5;
    CMenuItem *deleteNotesItems = new CMenuItem[deleteNotesItemsNumberAmount]{
        {"By Position", bind([](User& user){
                int position;
                cout << "Enter position to delete: ";
                cin >> position;
                CHATBOT* bot = user.get_bot();
                bot->pop_note(position);
            }, ref(user))
        },
        {"Completed by Position", bind([](User& user){
                    int position;
                    cout << "Enter position of completed note to delete: ";
                    cin >> position;
                    //user.deleteCompletedNoteByPosition(position); // This method doesn't exist in your class
            }, ref(user))
        },
        {"All Completed", bind([](User& user){
                    CHATBOT* bot = user.get_bot();
                    bot->del_all_completed();
            }, ref(user))
        },
        {"All Notes",  bind([](User& user){
                    CHATBOT* bot = user.get_bot();
                    bot->del_all_notes();
            }, ref(user))
        },
        {"Return to Main Menu", returnToMainMenu}
    };
    CMenu *deleteNotesMenu = new CMenu("Delete Notes Menu", deleteNotesItems, deleteNotesItemsNumberAmount);

    // --- Подменю Какой сегодня праздник ---
    const int holidayItemsAmount=3;
    CMenuItem *holidayItems = new CMenuItem[holidayItemsAmount]{
        {"Today", bind([](CHATBOT* bot) {
                bot->getWhatDayIsToday();
        }, chatbot)},
        {"For a Specific Day", bind([](CHATBOT* bot){
                int day, month, year;
                cout << "Enter day: ";
                cin >> day;
                cout << "Enter month: ";
                cin >> month;
                cout << "Enter year: ";
                cin >> year;
                    MYDATE date = {year, month, day};
                bot->getWhatDayIs(date);
            }, chatbot)
        },
        {"Return to Main Menu", returnToMainMenu}
    };
    CMenu *holidayMenu = new CMenu("Holiday Menu", holidayItems, holidayItemsAmount);

    // --- Подменю Изменение данных пользователя ---
    const int editProfileItemsAmount=3;
    CMenuItem *editProfileItems = new CMenuItem[editProfileItemsAmount]{
        {"Name", bind([](User& user){
                string newName;
                cout << "Enter new name: ";
                cin >> newName;
                user.set_name(newName);
            }, ref(user))
        },
        {"Password", bind([](User& user){
                string newPassword;
                cout << "Enter new password: ";
                cin >> newPassword;
                user.set_password(newPassword);
            }, ref(user))
        },
        {"Return to Main Menu", returnToMainMenu}
    };
    CMenu *editProfileMenu = new CMenu("Edit Profile Menu", editProfileItems, editProfileItemsAmount);

    // --- Главное меню ---
    const int mainMenuItemsAmount=6;
    CMenuItem *mainMenuItems = new CMenuItem[mainMenuItemsAmount]{
        {"Display Notes", [&]() { displayNotesMenu->runCommand(); }},
        {"Add Note", bind([](User& user){
                string sdate;
                string message;
                cout << "Enter date: ";
                getline(cin, sdate);
                cout << "Enter message: ";
                cin.ignore();
                getline(cin, message);
                NOTE note(MYDATE(sdate),message);
                CHATBOT* bot = user.get_bot();
                bot->add_note(note);
        }, ref(user))},
        {"Delete Note", [&]() { deleteNotesMenu->runCommand(); }},
        {"What's Today's Holiday?", [&]() { holidayMenu->runCommand(); }},
        {"Edit User Profile", [&]() { editProfileMenu->runCommand(); }},
        {"Display User Data", bind(&User::get_info, &user)},
    };
    CMenu *userMenu = new CMenu("Main Menu", mainMenuItems, mainMenuItemsAmount);
    
    return userMenu;
}