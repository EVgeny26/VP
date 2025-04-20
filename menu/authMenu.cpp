#include "CMenu/CMenu.h"
#include "CMenu/CMenuItem.h"
#include "../users/user.h"
#include "../users/admin.h"
#include "../controlEnter/control.h"
#include "adminMenu.h"
#include "userMenu.h"
#include "authMenu.h"
#include <functional>
#include <fstream>

using namespace std;

// --- Глобальные переменные для хранения данных ---
Vector<Human> allUsers;    // Все пользователи (User)
Vector<Human> allAdmins;   // Все админы (Admin)

// --- Загрузка пользователей из файлов ---
bool loadUsers() {
    return readHumansFromFile("usersInfo/users.bin", allUsers) && 
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
    loadUsers(); // Загружаем пользователей при старте

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
                    while (adminMenu->isRun()) {
                        adminMenu->runCommand();
                    }
                    delete adminMenu;
                    readHumansFromFile("usersInfo/users.bin", allUsers);
                    return;
                }
            }
            // Проверяем среди пользователей
            for (auto& user : allUsers) {
                if (user.get_login() == login && user.get_password() == password) {
                    User currentUser = user;
                    CMenu* userMenu = getUserMenu(currentUser);
                    while (userMenu->isRun()) {
                        userMenu->runCommand();
                    }
                    delete userMenu;
                    return;
                }
            }
            cout << "Ошибка: Неверный логин или пароль!\n";
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
        }},
        {"Выход", []() {}}
    };
    return new CMenu("Главное меню", authItems, authMenuItemsAmount);
}