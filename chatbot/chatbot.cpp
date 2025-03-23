#include <ctime>
#include <fstream>
#include <cstring>
#include <iomanip>

#include "chatbot.h"

#ifdef _WIN32
#include <windows.h> // Для Windows API
#else
#include <sys/stat.h> // Для mkdir и stat
#include <unistd.h>   // Для доступа к POSIX-функциям
#endif

// Функция для создания директории
bool create_directory(const string& path) {
#ifdef _WIN32
    // Windows: используем CreateDirectory
    if (CreateDirectory(path.c_str(), NULL)){
        return true;
    } else {
        return GetLastError() == ERROR_ALREADY_EXISTS;
    }
#else
    // Linux: используем mkdir
    if (mkdir(path.c_str(), 0777) == 0) {
        return true;
    } else {
        return errno == EEXIST;
    }
#endif
}

// Функция для проверки существования файла или директории
bool exists(const string& path) {
    #ifdef _WIN32
        // Windows: используем GetFileAttributes
        DWORD attributes = GetFileAttributes(path.c_str());
        return attributes != INVALID_FILE_ATTRIBUTES;
    #else
        // Linux: используем stat
        struct stat info;
        return stat(path.c_str(), &info) == 0;
    #endif
}


NOTE::NOTE(): date(MYDATE()), message((string)""){}
NOTE::NOTE(MYDATE date, string message): date(date), message(message){}
NOTE::~NOTE(){}

MYDATE NOTE::get_date(){return date;}
string NOTE::get_message(){return message;}

void NOTE::set_date(MYDATE date){this->date=date;}
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
    if(!is.fail()){
        size_t message_len;
        is.read((char*)(&message_len), sizeof(message_len));
        char *str = new char[message_len+1];
        is.read(str, message_len);
        note.message=str;
        delete[] str;
    }
    return is;
}

NOTE& NOTE::operator=(const NOTE& other){
    if (this != &other) {
        date = other.date;
        message = other.message;
    }
    return *this;
}

CHATBOT::CHATBOT(){
    time_t currentTime = time(0);
    tm* localTime = localtime(&currentTime);
    today=MYDATE(localTime);
}
CHATBOT::CHATBOT(vector<NOTE> notes): notes(notes) {
    time_t currentTime = time(0);
    tm* localTime = localtime(&currentTime);
    today=MYDATE{localTime};
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
MYDATE CHATBOT::get_today(){return today;}
int CHATBOT::get_len(){return notes.size();}
vector<NOTE> CHATBOT::get_notes(){return notes;}

void CHATBOT::add_note(NOTE note){
    for(int i=0;i<notes.size();i++){
        if(notes[i]>note){
            notes.insert(notes.begin()+i,note);
            return;
        }
    }notes.push_back(note);
}
void CHATBOT::notes_today(){
    vector<NOTE> notesToday;
    for(NOTE note : notes){
        if(note.get_date()>today)break;
        notesToday.push_back(note);
    }
    if(notes.empty()){
        cout<<"\nЗаметок нет\n";
        return;
    }
    cout<<"\nЗаметки выполненые на сегодня:\n"<<notesToday;
}
void CHATBOT::notes_day(MYDATE date){
    vector<string> notesDay;
    for(NOTE note : notes){
        if(note.get_date()==date)notesDay.push_back(note.get_message());
        if(note.get_date()>date)break;
    }
    if(notes.empty()){
        cout<<"\nЗаметок нет\n";
        return;
    }
    cout<<"\nЗаметки за "<<date.to_str()<<":\n";
    for(int i=0;i<notesDay.size();i++)cout<<(notesDay)[i]<<endl;
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
    cin>>ch;
    if(ch[0]=='1')notes.clear();
    delete[] ch;
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

void CHATBOT::getWhatDayIsToday(){getWhatDayIs(today);}
void skipLine(ifstream& fin){
    char next;
    while(fin.get(next)){if (next == '\n')break;}
}
void CHATBOT::getWhatDayIs(MYDATE date){
    string filename="chatbot/holidays.txt";
    ifstream fin(filename);
    if(!fin.good()){
        cerr<<"Ошибка: Не удалось открыть файл для чтения "<<filename<<endl;
        fin.close();
    }else{
        while(fin.is_open()){
            string sdate_hol;
            fin>>sdate_hol;
            sdate_hol.resize(sdate_hol.size()-1);
            MYDATE ddate_hol{sdate_hol};
            if(ddate_hol.get_day()==date.get_day() && ddate_hol.get_month()==date.get_month()){
                char holidays[1000];
                fin.getline(holidays, 1000);
                char *word = strtok(holidays, "|");
                word++;
                if(date==today)cout<<"Сегодня празднуются следующие дни:\n";
                else cout<<date.to_str()<<" празднуются следующие дни:\n";
                while(word!=nullptr){
                    cout<<word<<endl;
                    word = strtok(nullptr, "|");
                }cout<<endl;
                delete[] word;
                return;
            }skipLine(fin);
        }
        if(date==today)cout<<"Сегодня нет праздников\n";
        else cout<<date.to_str()<<" нет праздников\n";
    }
}

void CHATBOT::loud(string login){
    string pathToDir="usersInfo/usersHistory/"+login, pathToFile=pathToDir+"/chatbot.bin";
    
    // Проверяем, существует ли директория
    if (!exists(pathToDir)) {
        // Если директории нет, создаём её
        if (!create_directory(pathToDir)) {
            cerr << "Ошибка при создании директории: " << pathToDir << endl;
            return;
        }
    } 
    // Проверяем, существует ли файл
    if (!exists(pathToFile)) {
        // Если файла нет, создаём его
        ofstream file(pathToFile, ios::binary);
        if (!file.is_open()) {
            cerr << "Ошибка при создании файла: " << pathToFile << endl;
            file.close();
            return;
        }file.close();
    }else{
        ifstream fin(pathToFile, ios::binary);
        if (!fin.is_open()) {
            cerr << "Ошибка при открытии файла: " << pathToFile << endl;
        }else{
            fin>>*this;
            if (fin.fail()) {
                cerr << "Ошибка при чтении данных из файла: " << pathToFile << endl;
                // Установите объект CHATBOT в состояние по умолчанию
                *this = CHATBOT();
            }
            fin.close();
        }
    } 
}
void CHATBOT::save(string login){
    string pathToDir="usersInfo/usersHistory/"+login, pathToFile=pathToDir+"/chatbot.bin";
    
    // Проверяем, существует ли директория
    if (!exists(pathToDir)) {
        // Если директории нет, создаём её
        if (!create_directory(pathToDir)) {
            cerr << "Ошибка при создании директории: " << pathToDir << endl;
            return;
        }
    } 
    
    // Если файла нет, создаём его
    ofstream fout(pathToFile, ios::binary);
    if (!fout.is_open()) {
        cerr << "Ошибка при создании файла: " << pathToFile << endl;
        fout.close();
        return;
    }
    fout<<*this;
    fout.close();
}

ostream& operator<<(ostream& os, const CHATBOT& bot){
    size_t notes_size = bot.notes.size();
    os.write((char*)(&notes_size), sizeof(notes_size)); // Записываем размер вектора notes
    for (const auto& note : bot.notes) {
        os << note; // Используем перегруженный оператор для NOTE
    }
    return os;
}
istream& operator>>(istream& is, CHATBOT& bot){
    size_t notes_size;
    is.read((char*)(&notes_size), sizeof(notes_size)); // Читаем размер вектора notes

    // Проверяем размер вектора на разумность
    if (notes_size > 1000) { // Например, максимальное количество заметок 1000
        cerr << "Ошибка: Слишком много заметок в файле.\n";
        is.setstate(ios::failbit);
        return is;
    }

    bot.notes.resize(notes_size); // Изменяем размер вектора notes
    for (size_t i = 0; i < notes_size; ++i) {
        is >> bot.notes[i]; // Используем перегруженный оператор для NOTE
        if (is.fail()) {
            cerr << "Ошибка: Не удалось прочитать заметку из файла.\n";
            return is;
        }
    }
    return is;
}
NOTE& CHATBOT::operator[](int pos){
    if(pos>=notes.size()){
        cerr<<"Out of range\n";
        NOTE *note=nullptr;
        return *note;
    }
    return notes[pos];
}

ostream& operator<<(ostream& os, const vector<NOTE> notes){
    os<<"   ДАТА   : Заметка"<<endl;
    for(NOTE note : notes){
        os<<right<<setw(10)<<note.get_date().to_str()<<": "<<note.get_message()<<endl;
    }return os;
}


void CHATBOT::temp(){
    ofstream fout("test.txt");
    fout<<*this;
    fout.close();
}