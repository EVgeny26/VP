#include <iostream>
#include "controlEnter/control.h"
#include "users/admin.h"

using namespace std;


int main() {
    Vector<Human> vect;
    readHumansFromFile("usersInfo/admins.bin", vect);
    cout<<"Ввод нового админа:\n";
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
    vect.push_back(Admin{login,password, name,birth,(GENDER)gender});
    writeHumansToFile("usersInfo/admins.bin", vect);

    return 0;
}