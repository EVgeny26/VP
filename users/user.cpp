#include "user.h"
#include <iomanip>

User::User(string name, DATEBIRTH birth, GENDER gender, string login, string password): Human(name, birth, gender, login, password){}
User::~User(){}

ostream& operator<<(ostream& os, User& obj){
    os<<setw(10)<<obj.get_login()<<setw(20)<<obj.get_name()<<setw(12)<<obj.get_datebirth().to_str();
    os<<' '<<obj.get_gender()<<' '<<setw(12)<<obj.get_password()<<endl;
    return os;
}