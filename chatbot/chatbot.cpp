#include <ctime>

#include "chatbot.h"

NOTE::NOTE(): date(DATE()), message((string)""){}
NOTE::NOTE(DATE date, string message): date(date), message(message){}
NOTE::~NOTE(){}

DATE NOTE::get_date(){return date;}
string NOTE::get_message(){return message;}

void NOTE::set_date(DATE date){this->date=date;}
void NOTE::set_message(string message){this->message=message;}

bool NOTE::operator>(const NOTE& other) const{
    if(this->date==other.date)return this->message>other.message;
    return this->date>other.date;
}
bool NOTE::operator<(const NOTE& other) const{
    if(this->date==other.date)return this->message<other.message;
    return this->date<other.date;
}
bool NOTE::operator<=(const NOTE& other) const{
    return !operator>(other);
}
bool NOTE::operator>=(const NOTE& other) const{
    return !operator<(other);
}
bool NOTE::operator==(const NOTE& other) const{
    return this->date==other.date && this->message==other.message;
}
bool NOTE::operator!=(const NOTE& other) const{
    return !operator==(other);
}

ostream& operator<<(ostream& os, const NOTE& note){
    os<<note.date;

    size_t message_len = note.message.size();
    os.write((char*)(&message_len), sizeof(message_len));
    os.write(note.message.c_str(), message_len);

    return os;
}
istream& operator>>(istream& is, NOTE& note){
    is>>note.date;

    size_t message_len;
    is.read((char*)(&message_len), sizeof(message_len));
    char *str = new char[message_len];
    is.read(str, message_len);
    note.message=str;
    delete str;

    return is;
}

CHATBOT::CHATBOT(){
    time_t currentTime = time(0);
    tm* localTime = localtime(&currentTime);
    today=DATE(localTime);
}
CHATBOT::CHATBOT(vector<NOTE> notes): notes(notes) {
    time_t currentTime = time(0);
    tm* localTime = localtime(&currentTime);
    today=DATE(localTime);
}
CHATBOT::~CHATBOT(){}

void CHATBOT::sorted(){
    int size=notes.size();
    for(int i=0;i<size;i++){
        for(int j=0;j<size-1;j++){
            if(notes[j]>notes[j+1]){
                NOTE temp = notes[j];
                notes[j]=notes[j+1];
                notes[j+1]=temp;
            }
        }
    }
}
DATE CHATBOT::get_today(){return today;}
int CHATBOT::get_len(){return notes.size();}

void CHATBOT::add_note(NOTE note){
    for(int i=0;i<notes.size();i++){
        if(notes[i]>note){
            notes.insert(notes.begin()+i,note);
            return;
        }
    }notes.push_back(note);
}
vector<string> CHATBOT::notes_today(){
    vector<string> notesToday;
    NOTE note;
    for(int i=0;i<notes.size();i++, note=notes[i]){
        if(note.get_date()>today)break;
        notesToday.push_back(note.get_message());
    }return notesToday;
}
vector<string> CHATBOT::notes_day(DATE date){
    vector<string> notesDay;
    NOTE note;
    for(int i=0;i<notes.size();i++, note=notes[i]){
        if(note.get_date()==date)notesDay.push_back(note.get_message());
        if(note.get_date()>date)break;
    }return notesDay;
}
void CHATBOT::pop_note(int pos){
    if(pos>=notes.size()){
        cerr<<"Out of range\n";
        return;
    }
    notes.erase(notes.begin()+pos);
}
void CHATBOT::del_note(NOTE note){
    for(int i=0;i<notes.size();i++){
        if(note==notes[i]){
            notes.erase(notes.begin()+i);
            return;
        }
    }cerr<<"Note don\'t find\n";
}
void CHATBOT::del_all_notes(){
    cout<<"Вы уверены? Введите 1, чтобы удалить, или 0, чтобы отменить действие:";
    char *ch = new char[2];
    cin.getline(ch,2);
    if(ch[0]=='1')notes.clear();
}
void CHATBOT::del_note_completed(int pos){
    if(pos>=notes.size()){
        cerr<<"Out of range\n";
        return;
    }
    if(notes[pos].get_date()>today)cerr<<"Out of range of completed\n";
    else notes.erase(notes.begin()+pos);
}
void CHATBOT::del_all_completed(){
    while(!notes.empty()){
        if(notes[0].get_date()<=today)notes.erase(notes.begin());
        else break;
    }
}




ostream& operator<<(ostream& os, const CHATBOT& bot){
    for (int i = 0; i < bot.notes.size(); i++){
        os<<bot.notes[i];
    }
    return os;
}
istream& operator>>(istream& is, CHATBOT& bot){
    NOTE note;
    while(is>>note)bot.notes.push_back(note);
    return is;
}
NOTE& CHATBOT::operator[](int pos){
    if(pos>=notes.size()){
        cerr<<"Out of range\n";
        NOTE note;
        return note;
    }
    return notes[pos];
}