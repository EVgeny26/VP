#include "CMenu/CMenu.h"
#include "CMenu/CMenuItem.h"
#include "../users/user.h"
#include "../users/admin.h"
#include "../controlEnter/control.h"
#include "allMenu.h"
#include <functional>
#include <fstream>

using namespace std;

// --- Глобальные переменные для хранения данных ---
Vector<Human> allUsers;    
Vector<Human> allAdmins;   

CMenu* getAdminMenu(Admin& admin) {
    admin.loud("usersInfo/users.bin");
    // --- Подменю Удаление пользователей ---
    const int deleteNotesItemsNumberAmount=3;
    CMenuItem *deleteNotesItems = new CMenuItem[deleteNotesItemsNumberAmount]{
        {"По индексу", bind([&admin](){
            cout << "Введи номер пользователя: ";
            int pos=getCorNum();
            try{
                admin.del_user(pos-1);
                Logger::getInstance().log(LogLevel::ACTION, "Админ удалил пользователя по индексу: " + to_string(pos));
            }catch (const char* my_exce){
                cerr<< "Error! Name error: " << my_exce << endl;
                Logger::getInstance().log(LogLevel::ERROR, "Ошибка удаления пользователя по индексу: " + string(my_exce));
            }
         })},
         {"По логину", bind([&admin](){
            string login=getCorLogin();
            
            try{
                admin.del_user(login);
                Logger::getInstance().log(LogLevel::ACTION, "Админ удалил пользователя по логину: " + login);
            }catch (const char* my_exce){
                cerr<< "Error! Name error: " << my_exce << endl;
                Logger::getInstance().log(LogLevel::ERROR, "Ошибка удаления пользователя по логину: " + string(my_exce));
            }
         })},
        {"Возвращение в главное меню", returnToMainMenu}
    };
    CMenu *deleteNotesMenu = new CMenu("Меню удаления пользователей", deleteNotesItems, deleteNotesItemsNumberAmount);

    // --- Подменю Изменение данных пользователя ---
    const int editProfileItemsAmount=3;
    CMenuItem *editProfileItems = new CMenuItem[editProfileItemsAmount]{
        {"Имя", bind([](Admin& admin){
                string newName=getCorName();
                admin.set_name(newName);
                Logger::getInstance().log(LogLevel::CHANGE, "Изменение имени");
            }, ref(admin))
        },
        {"Пароль", bind([](Admin& admin){
                string newPassword=getCorPassword();
                admin.set_password(newPassword);
                Logger::getInstance().log(LogLevel::CHANGE, "Изменение пароля");
            }, ref(admin))
        },
        {"Возвращение в главное меню", returnToMainMenu}
    };
    CMenu *editProfileMenu = new CMenu("Изменение профиля", editProfileItems, editProfileItemsAmount);

    const int mainMenuItemsAmount = 7;
    CMenuItem *items = new CMenuItem[mainMenuItemsAmount]{
        {"Ввести всех пользователей", bind([&admin](){
            admin.pritall();
            Logger::getInstance().log(LogLevel::ACTION, "Админ запросил список всех пользователей");
        })},
        {"Добавить пользователя", bind([&admin](){
            admin.add_user();
            Logger::getInstance().log(LogLevel::CHANGE, "Админ добавил нового пользователя");
        })},
        {"Удаление пользователя", bind(&CMenu::runCommand, deleteNotesMenu)},
        {"Сортировка пользователей",bind([&admin](){
            cout << "Введите поле для сортировки(1, 2, 3): ";
            int pole=getCorNumDiaposone(1,3)-1;
            cout << "Требуется ли реверс(0 или 1): ";
            bool revers=getCorNumDiaposone(0,1);
            try{
                admin.sorted(pole, revers);
                Logger::getInstance().log(LogLevel::ACTION, "Сортировка пользователей");
            }catch (const char* my_exce){
                cerr<< "Error! Name error: " << my_exce << endl;
                Logger::getInstance().log(LogLevel::ERROR, "Ошибка сортировки: " + string(my_exce));
            }
        })},
        {"Вывести свои данные", bind([&admin](){
            admin.get_info();
            Logger::getInstance().log(LogLevel::ACTION, "Админ запросил свои данные");
        })},
        {"Изменить свои данные", bind(&CMenu::runCommand, editProfileMenu)},
        {"Выйти", bind([](Admin& admin){
            admin.save("usersInfo/users.bin");
        }, ref(admin))}
    };

    CMenu* adminMenu = new CMenu("Меню админа", items, mainMenuItemsAmount);
    return adminMenu;
}

CMenu* getUserMenu(User& user){
    user.loudBot();
    // --- Подменю Вывод заметок ---
    const int displayNotesItemsAmount=4;
    CMenuItem *displayNotesItems = new CMenuItem[displayNotesItemsAmount]{
        {"Все заметки", bind([&user](){
            user.printNotes();
            Logger::getInstance().log(LogLevel::ACTION, "Пользователь просмотрел все заметки");
        })},
        {"Выполненые заметки на сегодня", bind([](User& user) {
            user.get_bot()->notes_today();
            Logger::getInstance().log(LogLevel::ACTION, "Пользователь просмотрел выполненные заметки на сегодня");
        }, ref(user))},
        {"Заметки за н-ый день", bind([](User& user){
                MYDATE date = getCorDate();
                user.get_bot()->notes_day(date);
                Logger::getInstance().log(LogLevel::ACTION, "Пользователь просмотрел заметки за " + date.to_str());
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
                    Logger::getInstance().log(LogLevel::CHANGE, 
                        "Пользователь изменил дату заметки с " + note.get_date().to_str() + " на " + date.to_str());
                    note.set_date(date);
                }
                
            }catch (const char* my_exce){
                cerr<< "Error! Name error: " << my_exce << endl;
                Logger::getInstance().log(LogLevel::ERROR, "Ошибка изменения даты заметки: " + string(my_exce));
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
                    Logger::getInstance().log(LogLevel::CHANGE, 
                        "Пользователь изменил текст заметки #" + to_string(position) + " на " + message);
                    note.set_message(message);
                }
            }catch (const char* my_exce){
                cerr<< "Error! Name error: " << my_exce << endl;
                Logger::getInstance().log(LogLevel::ERROR, "Ошибка изменения текста заметки: " + string(my_exce));

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
                     Logger::getInstance().log(LogLevel::ACTION, 
                        "Пользователь удалил заметку #" + to_string(position));
                }catch (const char* my_exce){
                    cerr<< "Error! Name error: " << my_exce << endl;
                    Logger::getInstance().log(LogLevel::ERROR, 
                        "Ошибка удаления заметки #" + to_string(position) + ": " + string(my_exce));
                }
            }, ref(user))
        },
        {"Выполненую по индексу", bind([](User& user){
                cout << "Введите позицию выбранной выполненой заметки: ";
                int position=getCorNum();
                try{
                    user.get_bot()->del_note_completed(position-1);
                    Logger::getInstance().log(LogLevel::ACTION,
                        "Пользователь удалил выполненную заметку #" + to_string(position));
                }catch (const char* my_exce){
                    cerr<< "Error! Name error: " << my_exce << endl;
                    Logger::getInstance().log(LogLevel::ERROR, 
                        "Ошибка удаления выполненной заметки #" + to_string(position) + ": " + string(my_exce));
                }
                    
            }, ref(user))
        },
        {"Все выполненые", bind([](User& user){
                    user.get_bot()->del_all_completed();
                    Logger::getInstance().log(LogLevel::ACTION, 
                    "Пользователь удалил все выполненные заметки");
            }, ref(user))
        },
        {"Все",  bind([](User& user){
                    bool isDel = user.get_bot()->del_all_notes();
                    if(isDel)Logger::getInstance().log(LogLevel::CHANGE, 
                    "Пользователь удалил все заметки");
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
                Logger::getInstance().log(LogLevel::ACTION, 
                    "Пользователь запросил праздники на сегодня");
        }, ref(user))},
        {"В выбранный день", bind([](User& user){
                MYDATE date = getCorDate();
                user.get_bot()->getWhatDayIs(date);
                Logger::getInstance().log(LogLevel::ACTION, 
                    "Пользователь запросил праздники на " + date.to_str());
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
                Logger::getInstance().log(LogLevel::CHANGE, 
                    "Пользователь изменил имя");
            }, ref(user))
        },
        {"Пароль", bind([](User& user){
                string newPassword=getCorPassword();
                user.set_password(newPassword);
                Logger::getInstance().log(LogLevel::CHANGE, "Пользователь изменил пароль");
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
                 Logger::getInstance().log(LogLevel::ACTION, 
                    "Пользователь добавил новую заметку на " + date.to_str());
        }, ref(user))},
        {"Изменить заметку", bind(&CMenu::runCommand, changeNotesMenu)},
        {"Удаление заметок", bind(&CMenu::runCommand, deleteNotesMenu)},
        {"Какой праздник?", bind(&CMenu::runCommand, holidayMenu)},
        {"Изменение профиля", bind(&CMenu::runCommand, editProfileMenu)},
        {"Вывести свои данные", bind([&user](){
            user.get_info();
            Logger::getInstance().log(LogLevel::ACTION, "Пользователь запросил свои данные");
        })},
        {"Выйти", bind([](User& user){
            user.saveBot();
        }, ref(user))}
    };
    CMenu *userMenu = new CMenu("Меню пользователя", mainMenuItems, mainMenuItemsAmount);
    
    return userMenu;
}



// --- Загрузка пользователей из файлов ---
void loadUsers() {
    readHumansFromFile("usersInfo/users.bin", allUsers) && 
    readHumansFromFile("usersInfo/admins.bin", allAdmins);
}

// --- Проверка, занят ли логин ---
bool isLoginTaken(const string& login) {
    for (const auto& user : allUsers) {
        if (user.get_login() == login) return true;
    }
    for (const auto& admin : allAdmins) {
        if (admin.get_login() == login) return true;
    }
    return false;
}

// --- Меню авторизации ---
CMenu* getAuthMenu() {
    loadUsers();

    const int authMenuItemsAmount = 3;
    CMenuItem* authItems = new CMenuItem[authMenuItemsAmount]{
        {"Вход", [](){
            string login, password;
            login = getCorLogin();
            password = getCorPassword();

            // Проверяем среди админов
            for (auto& admin : allAdmins) {
                if (admin.get_login() == login && admin.get_password() == password) {
                    Admin currentAdmin = admin;
                    CMenu* adminMenu = getAdminMenu(currentAdmin);
                    Logger::getInstance().log(LogLevel::ENTER, "Вход админа " + login);
                    while (adminMenu->isRun()) {
                        adminMenu->runCommand();
                    }
                    delete adminMenu;
                    Logger::getInstance().log(LogLevel::EXIT, "Выход админа " + login);
                    readHumansFromFile("usersInfo/users.bin", allUsers);
                    if(currentAdmin!=admin){
                        admin.set_name(currentAdmin.get_name());
                        admin.set_password(currentAdmin.get_password());
                        writeHumansToFile("usersInfo/admin.bin", allAdmins);
                    }
                    return;
                }
            }
            // Проверяем среди пользователей
            for (auto& user : allUsers) {
                if (user.get_login() == login && user.get_password() == password) {
                    User currentUser = user;
                    CMenu* userMenu = getUserMenu(currentUser);
                    Logger::getInstance().log(LogLevel::ENTER, "Вход пользователя " + login);
                    while (userMenu->isRun()) {
                        userMenu->runCommand();
                    }
                    delete userMenu;
                    Logger::getInstance().log(LogLevel::ENTER, "Выход пользователя " + login);
                    if(currentUser!=user){
                        user.set_name(currentUser.get_name());
                        user.set_password(currentUser.get_password());
                        writeHumansToFile("usersInfo/users.bin", allUsers);
                    }
                    return;
                }
            }
            cout << "Неверный логин или пароль!\n";
            Logger::getInstance().log(LogLevel::ERROR, "Неудачный вход");
        }},
        {"Регистрация", []() {
            string login, password;
            bool isTaken;
            do{
                login = getCorLogin();
                isTaken=0;
                if (isLoginTaken(login)) {
                    cout << "Ошибка: Логин занят!\n";
                    isTaken=1;
                }
            }while (isTaken);

            password = getCorPassword();

            string name=getCorName();
            cout<<"Введите дату рождения\n";
            MYDATE birth=getCorDate();
            cout<<"Введите пол (male - 0, female - 1):";
            int gender=getCorNumDiaposone(0,1);

            // Создаём нового пользователя
            User newUser(login, password, name, birth, (GENDER)gender);
            allUsers.push_back(newUser);
            
            // Сохраняем в users.bin
            writeHumansToFile("usersInfo/users.bin", allUsers);
            cout << "Регистрация успешна!\n";
            Logger::getInstance().log(LogLevel::CHANGE, "Решистрация нового пользователя: " + login);
        }},
        {"Выход", []() {}}
    };
    return new CMenu("Главное меню", authItems, authMenuItemsAmount);
}