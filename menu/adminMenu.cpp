#include "CMenu/CMenu.h"
#include "CMenu/CMenuItem.h"
#include "adminMenu.h"
#include "../controlEnter/control.h"

#include <functional>

using namespace std;

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
            }catch (const char* my_exce){
                cerr<< "Error! Name error: " << my_exce << endl;
            }
         })},
         {"По логину", bind([&admin](){
            string login=getCorLogin();
            
            try{
                admin.del_user(login);
            }catch (const char* my_exce){
                cerr<< "Error! Name error: " << my_exce << endl;
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

    const int mainMenuItemsAmount = 7;
    CMenuItem *items = new CMenuItem[mainMenuItemsAmount]{
        {"Ввести всех пользователей", bind(&Admin::pritall, &admin)},
        {"Добавить пользователя", bind(static_cast<void (Admin::*)()>(&Admin::add_user), &admin)},
        {"Удаление пользователя", bind(&CMenu::runCommand, deleteNotesMenu)},
        {"Сортировка пользователей",bind([&admin](){
            cout << "Введите поле для сортировки(1, 2, 3): ";
            int pole=getCorNumDiaposone(1,3)-1;
            cout << "Требуется ли реверс(0 или 1): ";
            bool revers=getCorNumDiaposone(0,1);
            try{
                admin.sorted(pole, revers);
            }catch (const char* my_exce){
                cerr<< "Error! Name error: " << my_exce << endl;
            }
        })},
        {"Вывести свои данные", bind(&Admin::get_info, &admin)},
        {"Изменить свои данные", bind(&CMenu::runCommand, editProfileMenu)},
        {"Выйти", bind([](Admin& admin){
            admin.save("usersInfo/users.bin");
        }, ref(admin))}
    };

    CMenu* adminMenu = new CMenu("Меню админа", items, mainMenuItemsAmount);
    return adminMenu;
}