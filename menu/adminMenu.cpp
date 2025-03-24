#include "CMenu/CMenu.h"
#include "CMenu/CMenuItem.h"
#include "../users/admin.h"
#include "adminMenu.h"
#include "../controlEnter/control.h"

#include <functional>

using namespace std;

CMenu* getAdminMenu(Admin& admin) {
    admin.loud_from_file("usersInfo/users.bin");
    // --- Подменю Удаление пользователей ---
    const int deleteNotesItemsNumberAmount=3;
    CMenuItem *deleteNotesItems = new CMenuItem[deleteNotesItemsNumberAmount]{
        {"Удалить пользователя", bind([&admin](){
            cout << "Введи номер пользователя: ";
            int pos=getCorNum();
            admin.del_user(pos);
         })},
         {"Delete User (by login)", bind([&admin](){
            string login=getCorLogin();
            admin.del_user(login);
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
            }, ref(admin))
        },
        {"Пароль", bind([](Admin& admin){
                string newPassword=getCorPassword();
                admin.set_password(newPassword);
            }, ref(admin))
        },
        {"Возвращение в главное меню", returnToMainMenu}
    };
    CMenu *editProfileMenu = new CMenu("Изменение профиля", editProfileItems, editProfileItemsAmount);

    const int mainMenuItemsAmount = 6;
    CMenuItem *items = new CMenuItem[mainMenuItemsAmount]{
        {"Ввести всех пользователей", bind(&Admin::pritall, &admin)},
        {"Добавить пользователя", bind(static_cast<void (Admin::*)()>(&Admin::add_user), &admin)},
        {"Удаление заметок", bind(&CMenu::runCommand, deleteNotesMenu)},
        {"Сортировка пользователей",bind([&admin](){
            cout << "Введите поле для сортировки(1, 2, 3): ";
            int pole=getCorNumDiaposone(1,3)-1;
            cout << "Требуется ли реверс(0 или 1): ";
            bool revers=getCorNumDiaposone(0,1);
            admin.sorted(pole, revers);
        })},
        {"Вывести свои данные", bind(&Admin::get_info, &admin)},
        {"Выйти", bind([](Admin& admin){
            admin.loud_to_file("usersInfo/users.bin");
        }, ref(admin))},
    };

    CMenu* adminMenu = new CMenu("Меню админа", items, mainMenuItemsAmount);
    return adminMenu;
}