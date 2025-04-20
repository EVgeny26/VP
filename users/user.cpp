#include "user.h"
#include <iostream>
#include <iomanip>

using namespace std;

User::User(): Human(), bot(nullptr){}
User::User(string login, string password, string name, MYDATE birth, GENDER gender)
    : Human(name, birth, gender, login, password), bot(nullptr) {}
User::User(const Human& human) 
    : Human(human), bot(nullptr) {}
User::~User() {}
CHATBOT* User::get_bot(){return bot;}
void User::loudBot(){
    if(bot==nullptr)bot=new CHATBOT();
    bot->loud(get_login());
}
void User::saveBot(){
    if(bot!=nullptr)bot->save(get_login());
}

void User::printNotes(){
    if(bot==nullptr){
        cout<<"\nЗаметок нет\n";
        return;
    }
    Vector<NOTE>& notes = bot->get_notes();
    if(notes.empty()){
        cout<<"\nЗаметок нет\n";
        return;
    }
    cout<<"\nЗаметки в следующем формате:\n"<<notes;

}
ostream& operator<<(ostream& os, const User& obj) {
    os << static_cast<const Human&>(obj);
    return os;
}

istream& operator>>(istream& is, User& obj) {
    is >> static_cast<Human&>(obj);
    return is;
}