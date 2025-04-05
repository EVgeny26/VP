#include <iostream>
#include "controlEnter/control.h"
#include "users/admin.h"
#include <fstream>

using namespace std;

int main(){


    cout<<"Ввод нового пользователя:\n";
    cout<<"Введите логин:";
    string login=getCorName();

    cout<<"Введите пароль:";
    string password=getCorPassword();

    cout<<"Введите имя:";
    string name=getCorName();

    cout<<"Введите дату (пример: 3 5 2005)";
    MYDATE birth=getCorDate();

    cout<<"Введите пол (male - 0, female - 1):";
    int gender=getCorNumDiaposone(0,1);

    ofstream fout("usersInfo/users.bin", ios::binary);
    Admin{name,birth,(GENDER)gender,login,password};
    
    
    
    
    cout<<"Пользователь введен\n\n";
    return 0;
}