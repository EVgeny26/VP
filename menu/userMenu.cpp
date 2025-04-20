#include "CMenu/CMenu.h"
#include "CMenu/CMenuItem.h"
#include "../users/user.h"
#include "userMenu.h"
#include "../controlEnter/control.h"

#include <functional>
#include <iostream>

using namespace std;

CMenu* getUserMenu(User& user){
    user.loudBot();
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

    // --- Подменю Изменение заметок ---
    const int changeNotesItemsAmount=3;
    CMenuItem *changeNotesItems = new CMenuItem[changeNotesItemsAmount]{
        {"Дату", bind([](User& user){
            cout << "Введите позицию выбранной заметки: ";
            int position=getCorNum();
            try{
                NOTE& note=(*user.get_bot())[position-1];
                if(note!=NOTE()){
                    cout << "Ввод даты:\n";
                    MYDATE date=getCorDate();
                    note.set_date(date);
                }
            }catch (const char* my_exce){
                cerr<< "Error! Name error: " << my_exce << endl;
            }
            }, ref(user))
        },
        {"Сообщение", bind([](User& user){
            cout << "Введите позицию выбранной заметки: ";
            int position=getCorNum();
            try{
                NOTE& note=(*user.get_bot())[position-1];
                if(note!=NOTE()){
                    string message;
                    cout << "Введи сообщение: ";
                    getline(cin >> ws, message);
                    note.set_message(message);
                }
            }catch (const char* my_exce){
                cerr<< "Error! Name error: " << my_exce << endl;
            }
            }, ref(user))
        },
        {"Возвращение в главное меню", returnToMainMenu}
    };
    CMenu *changeNotesMenu = new CMenu("Изменение замиток", changeNotesItems, changeNotesItemsAmount);

    // --- Подменю Удаление заметок ---
    const int deleteNotesItemsNumberAmount=5;
    CMenuItem *deleteNotesItems = new CMenuItem[deleteNotesItemsNumberAmount]{
        {"По индексу", bind([](User& user){
                cout << "Введите позицию выбранной заметки: ";
                int position=getCorNum();
                try{
                    user.get_bot()->pop_note(position-1);
                }catch (const char* my_exce){
                    cerr<< "Error! Name error: " << my_exce << endl;
                }
            }, ref(user))
        },
        {"Выполненую по индексу", bind([](User& user){
                cout << "Введите позицию выбранной выполненой заметки: ";
                int position=getCorNum();
                try{
                    user.get_bot()->del_note_completed(position-1);
                }catch (const char* my_exce){
                    cerr<< "Error! Name error: " << my_exce << endl;
                }
                    
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
    const int mainMenuItemsAmount=8;
    CMenuItem *mainMenuItems = new CMenuItem[mainMenuItemsAmount]{
        {"Вывод заметок", bind(&CMenu::runCommand, displayNotesMenu)},
        {"Добавить заметку", bind([](User& user){
                cout << "Ввод даты:\n";
                MYDATE date=getCorDate();
                
                string message;
                cout << "Введи сообщение: ";
                getline(cin >> ws, message);

                NOTE note(date, message);
                user.get_bot()->add_note(note);
        }, ref(user))},
        {"Изменить заметку", bind(&CMenu::runCommand, changeNotesMenu)},
        {"Удаление заметок", bind(&CMenu::runCommand, deleteNotesMenu)},
        {"Какой праздник?", bind(&CMenu::runCommand, holidayMenu)},
        {"Изменение профиля", bind(&CMenu::runCommand, editProfileMenu)},
        {"Вывести свои данные", bind(&User::get_info, &user)},
        {"Выйти", bind([](User& user){
            user.saveBot();
        }, ref(user))}
    };
    CMenu *userMenu = new CMenu("Меню пользователя", mainMenuItems, mainMenuItemsAmount);
    
    return userMenu;
}