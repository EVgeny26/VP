#include "CMenu/CMenu.h"
#include "CMenu/CMenuItem.h"
#include "../users/user.h"
#include "userMenu.h"
#include "../controlEnter/control.h"

#include <functional>
#include <iostream>

using namespace std;

CMenu* getUserMenu(User& user){

    // --- Подменю Вывод заметок ---
    const int displayNotesItemsAmount=4;
    CMenuItem *displayNotesItems = new CMenuItem[displayNotesItemsAmount]{
        {"Все заметки", bind(&User::printNotes, &user)},
        {"Выполненые заметки на сегодня", bind([](User& user) {
            user.get_bot()->notes_today();
        }, ref(user))},
        {"Заметки за н-ый день", bind([](User& user){
                MYDATE date = getCorDate();
                user.get_bot()->notes_day(date);
            }, ref(user))
        },
        {"Возвращение в главное меню", returnToMainMenu}
    };
    CMenu* displayNotesMenu = new CMenu("Меню вывода заметок", displayNotesItems, displayNotesItemsAmount);

    // --- Подменю Удаление заметок ---
    const int deleteNotesItemsNumberAmount=5;
    CMenuItem *deleteNotesItems = new CMenuItem[deleteNotesItemsNumberAmount]{
        {"По индексу", bind([](User& user){
                cout << "Введите позицию выбранной заметки: ";
                int position=getCorNum();
                user.get_bot()->pop_note(position-1);
            }, ref(user))
        },
        {"Выполненую по индексу", bind([](User& user){
                    cout << "Введите позицию выбранной выполненой заметки: ";
                    int position=getCorNum();
                    user.get_bot()->del_note_completed(position-1);
            }, ref(user))
        },
        {"Все выполненые", bind([](User& user){
                    user.get_bot()->del_all_completed();
            }, ref(user))
        },
        {"Все",  bind([](User& user){
                    user.get_bot()->del_all_notes();
            }, ref(user))
        },
        {"Возвращение в главное меню", returnToMainMenu}
    };
    CMenu *deleteNotesMenu = new CMenu("Меню удаления заметок", deleteNotesItems, deleteNotesItemsNumberAmount);

    // --- Подменю Какой сегодня праздник ---
    const int holidayItemsAmount=3;
    CMenuItem *holidayItems = new CMenuItem[holidayItemsAmount]{
        {"Сегодня", bind([](User& user) {
                user.get_bot()->getWhatDayIsToday();
        }, ref(user))},
        {"В выбранный день", bind([](User& user){
                MYDATE date = getCorDate();
                user.get_bot()->getWhatDayIs(date);
            }, ref(user))
        },
        {"Возвращение в главное меню", returnToMainMenu}
    };
    CMenu *holidayMenu = new CMenu("Меню праздников", holidayItems, holidayItemsAmount);

    // --- Подменю Изменение данных пользователя ---
    const int editProfileItemsAmount=3;
    CMenuItem *editProfileItems = new CMenuItem[editProfileItemsAmount]{
        {"Имя", bind([](User& user){
                string newName=getCorName();
                user.set_name(newName);
            }, ref(user))
        },
        {"Пароль", bind([](User& user){
                string newPassword=getCorPassword();
                user.set_password(newPassword);
            }, ref(user))
        },
        {"Возвращение в главное меню", returnToMainMenu}
    };
    CMenu *editProfileMenu = new CMenu("Изменение профиля", editProfileItems, editProfileItemsAmount);

    // --- Главное меню ---
    const int mainMenuItemsAmount=7;
    CMenuItem *mainMenuItems = new CMenuItem[mainMenuItemsAmount]{
        {"Ввывод заметок", bind(&CMenu::runCommand, displayNotesMenu)},
        {"Добавить заметку", bind([](User& user){
                cout << "Ввод даты:\n";
                MYDATE date=getCorDate();
                
                string message;
                cout << "Введи сообщение: ";
                getline(cin >> ws, message);

                NOTE note(date, message);
                user.get_bot()->add_note(note);
        }, ref(user))},
        {"Удаление заметок", bind(&CMenu::runCommand, deleteNotesMenu)},
        {"Какой праздник?", bind(&CMenu::runCommand, holidayMenu)},
        {"Изменение профиля", bind(&CMenu::runCommand, editProfileMenu)},
        {"Вывести свои данные", bind(&User::get_info, &user)},
        {"Выйти", {}}
    };
    CMenu *userMenu = new CMenu("Меню пользователя", mainMenuItems, mainMenuItemsAmount);
    
    // return displayNotesMenu;
    return userMenu;
}