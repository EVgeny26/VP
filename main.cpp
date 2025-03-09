#include "menu/CMenu.h"
#include "menu/CMenuItem.h"
#include "users/admin.h"
#include "users/user.h"

#include <cmath>
#include <ctime>
#include <functional>

using namespace std;


#pragma region функции-заглушки
int f1() {
    cout << "function f1 is running...\n\n";
    return 1;
}

int f2() {
    cout << "function f2 is running...\n\n";
    return 2;
}

int f3() {
    cout << "function f3 is running...\n\n";
    return 3;
}


int sqrt_25() {
    cout << "Корень 25 - это "<< sqrt(25) <<"\n\n";
    return 1;
}

int sqrt_25_graf() {
    cout<<"       ==============================                           "<<endl;
    cout<<"      ==                                                          "<<endl;
    cout<<"      =    =======          ======                ======              "<<endl;
    cout<<"     ==   ==      ==        =          =====      =                "<<endl;
    cout<<"     =             ==       =  ==                 =  ==           "<<endl;
    cout<<"    ==              =       ==    =    =====      ==    =           "<<endl;
    cout<<"==  =            ==                =                      =            "<<endl;
    cout<<" ====       ====                 ==                     ==            "<<endl;
    cout<<"  ==     =============       ====                   ====               "<<endl<<endl;

    return 2;
}

int sqrt_with_enter() {
    float num;
    cout<<"Введите число для вычисления корня: ";
    do{
        cin>>num;
        if(num<0)cout<<"Введите положительное число: ";
    }while (num<0);
    
    cout << "Корень "<<num<<" = "<<sqrt(num)<<endl<<endl;
    return 3;
}
#pragma endregion

const int ITEMS_NUMBER = 7;


int main() {
    Admin admin{"Evgeny", DATEBIRTH{26,9,2006}, male, "MainAd", "12345678"};

    CMenuItem items[ITEMS_NUMBER] = {
        {"Print All Users", bind(&Admin::pritall, &admin)},
        {"Add User (interactive)", bind(static_cast<void (Admin::*)()>(&Admin::add_user), &admin)},
        //{"Add User (from User object)", std::bind(&Admin::add_user, &admin, /*Здесь нужно передать объект User, но пока его нет*/)},
        {"Delete User (by position)", bind([&admin](){
           int pos;
           cout << "Enter position to delete: ";
           cin >> pos;
           admin.del_user(pos);
        })},
        {"Delete User (by login)", bind([&admin](){
           string login;
           cout << "Enter login to delete: ";
           cin >> login;
           admin.del_user(login);
        })},
        {"Sort Users",bind([&admin](){
            int pole;
            bool revers;
            cout << "Enter sort pole (0, 1, 2...): ";
            cin >> pole;
            cout << "Enter reverse (0 or 1): ";
            cin >> revers;
            admin.sorted(pole, revers);
        })},
        {"Load Users From File", std::bind(&Admin::loud_from_file, &admin)},
        {"Save Users To File", std::bind(&Admin::loud_to_file, &admin)}
    };

    CMenu menu("Admin Menu", items, sizeof(items) / sizeof(items[0]));


    while (menu.isRun()) {
        menu.runCommand();
    }
    return 0;
}