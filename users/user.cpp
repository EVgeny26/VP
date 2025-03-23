#include "user.h"
#include <iostream>
#include <iomanip>

using namespace std;

User::User(): Human(), bot(new CHATBOT()){}
User::User(string name, MYDATE birth, GENDER gender, string login, string password)
    : Human(name, birth, gender, login, password), bot(new CHATBOT()) {}

User::~User() {
    saveBot();
}
CHATBOT* User::get_bot(){return bot;}
void User::loudBot(){bot->loud(get_login());}
void User::saveBot(){bot->save(get_login());}

void User::printNotes(){
    vector<NOTE> notes = bot->get_notes();
    if(notes.empty()){
        cout<<"\nЗаметок нет\n";
        return;
    }
    cout<<"\nЗаметки в следующем формате:\n"<<notes;

}
// void User::printCompletedNotes(){
//     vector<NOTE> *notes = bot->notes_today();
//     if(notes->empty()){
//         cout<<"\nЗаметок нет\n";
//         delete[] notes;
//         return;
//     }
//     cout<<"\nЗаметки выполненые на сегодня:\n"<<notes;
//     delete[] notes;
// }
// void User::printNotesDay(MYDATE date){
//     vector<string> *notes = bot->notes_day(date);
//     if(notes->empty()){
//         cout<<"\nЗаметок нет\n";
//         delete[] notes;
//         return;
//     }
//     cout<<"\nЗаметки за "<<date.to_str()<<":\n";
//     for(int i=0;i<notes->size();i++)cout<<(*notes)[i]<<endl;
//     delete[] notes;
// }

int CountRu(string str){
    int count=0;
    for(int i=0;i<str.length();i++){
        if(str[i]<0){count++;i++;}
    }return count;
}

void User::printToConsoleInTable(ostream& os, int indents[5]) {
    os<<setfill(' ');
    os <<left<<'|'<< setw(indents[0]+CountRu(get_login())) << get_login() <<'|'<< setw(indents[1]+CountRu(get_name())) << get_name() <<'|'<< setw(indents[2]) << get_DATE().to_str();
    os <<'|'<< setw(indents[3]) << (get_gender() == male ? "Male" : "Female") <<'|'<< setw(indents[4]+CountRu(get_password())) << get_password() <<'|'<< endl;
}

ostream& operator<<(ostream& os, const User& obj) {
    os << static_cast<const Human&>(obj);
    return os;
}

istream& operator>>(istream& is, User& obj) {
    is >> static_cast<Human&>(obj);
    return is;
}