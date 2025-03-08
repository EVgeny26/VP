#include "human.h"
#include <ctime>

Human::Human(string name, DATEBIRTH birth, GENDER gender, string login, string password): name(name), birth(birth), gender(gender), login(login), password(password) {}

Human::~Human(){}

void Human::set_name(string name){this->name=name;}
void Human::set_password(string password){this->password=password;}

string Human::get_name(){return name;}
string Human::get_login(){return login;}
string Human::get_password(){return password;}
DATEBIRTH Human::get_datebirth(){return birth;}
GENDER Human::get_gender(){return gender;}
unsigned short Human::get_age(){
    time_t currentTime = time(0);  // nullptr эквивалентно 0
    tm* localTime = localtime(&currentTime);
    unsigned short age=birth.get_year()-1900-localTime->tm_year; // Год начинается с 1900
    if(localTime->tm_mon+1>birth.get_month())return age;
    if(localTime->tm_mon+1==birth.get_month()){
        if(localTime->tm_mday>=birth.get_day())return age;
        else return age-1;
    }else return age-1;
}