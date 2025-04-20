#include "human.h"  // Всегда первым включаем заголовочный файл класса
#include <ctime>   // Для локального времени при обработке даты
#include <iomanip> // Для put_time

using namespace std;

// Дружественная функция для записи GENDER в бинарный файл
ostream& operator<<(ostream& os, const GENDER& gender) {
    os.write((char*)(&gender), sizeof(gender));
    return os;
}

// Дружественная функция для чтения GENDER из бинарного файла
istream& operator>>(istream& is, GENDER& gender) {
    is.read((char*)(&gender), sizeof(gender));
    return is;
}

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

Human::Human() : name(""), birth(), gender(male), login(""), password("") {}
Human::Human(string name, MYDATE birth, GENDER gender, string login, string password) :
    name(name), birth(birth), gender(gender), login(login), password(password) {}

Human::~Human() {}

void Human::set_name(string name) { this->name = name; }
void Human::set_password(string password) { this->password = password; }

string Human::get_name() const { return name; }
string Human::get_login() const { return login; }
string Human::get_password() const { return password; }
MYDATE Human::get_DATE() const { return birth; }
GENDER Human::get_gender() const { return gender; }
void Human::get_info(){
    cout<<"Логин: "<<login<<endl;
    cout<<"Имя: "<<name<<endl;
    cout<<"День рождения: "<<birth.to_str()<<endl;
    cout<<"Пол: "<<(gender? "ж":  "м")<<endl;
}

int CountRu(string str){
    int count=0;
    for(int i=0;i<str.length();i++){
        if(str[i]<0){count++;i++;}
    }return count;
}
void Human::printToConsoleInTable(ostream& os, int indents[5]) {
    os<<setfill(' ');
    os <<left<<'|'<< setw(indents[0]+CountRu(get_login())) << get_login() <<'|'<< setw(indents[1]+CountRu(get_name())) << get_name() <<'|'<< setw(indents[2]) << get_DATE().to_str();
    os <<'|'<< setw(indents[3]) << (get_gender() == male ? "Male" : "Female") <<'|'<< setw(indents[4]+CountRu(get_password())) << get_password() <<'|'<< endl;
}

Human& Human::operator=(const Human& other) {
    if (this != &other) {
        name = other.name;
        birth = other.birth;
        gender = other.gender;
        login = other.login;
        password = other.password;
    }
    return *this;
}
bool Human::operator==(const Human& other){
    return password==other.password && name==other.name;
}
bool Human::operator!=(const Human& other){
    return !operator==(other);
}

// Дружественная функция для записи Human в бинарный файл
ostream& operator<<(ostream& os, const Human& human) {
    size_t login_len = human.login.size();
    os.write((char*)(&login_len), sizeof(login_len));
    os.write(human.login.c_str(), login_len);

    size_t password_len = human.password.size();
    os.write((char*)(&password_len), sizeof(password_len));
    os.write(human.password.c_str(), password_len);

    size_t name_len = human.name.size();
    os.write((char*)(&name_len), sizeof(name_len));
    os.write(human.name.c_str(), name_len);

    os << human.birth; 
    os << human.gender; 

    return os;
}

// Дружественная функция для чтения Human из бинарного файла
istream& operator>>(istream& is, Human& human) {
    size_t login_len;
    is.read((char*)(&login_len), sizeof(login_len));
    char *str = new char[login_len];
    is.read(str, login_len);
    human.login=str;
    delete str;

    size_t password_len;
    is.read((char*)(&password_len), sizeof(password_len));
    str = new char[password_len];
    is.read(str, password_len);
    human.password=str;
    delete str;

    size_t name_len;
    is.read((char*)(&name_len), sizeof(name_len));
    str = new char[name_len];
    is.read(str, name_len);
    human.name=str;
    delete str;

    is >> human.birth; // Используем перегруженный оператор >> для MYDATE
    is >> human.gender; // Используем перегруженный оператор >> для GENDER


    return is;
}


// Функция для записи массива Human в бинарный файл
bool writeHumansToFile(const string& filename, const Vector<Human>& humans) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл для записи: " << filename << endl;
        return false;
    }

    size_t num_humans = humans.size();
    file.write((char*)(&num_humans), sizeof(num_humans));

    for (const auto& human : humans) {
        file << human;
    }

    file.close();
    return true;
}

// Функция для чтения массива Human из бинарного файла
bool readHumansFromFile(const string& filename, Vector<Human>& humans) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл для чтения: " << filename << endl;
        return false;
    }

    size_t num_humans;
    file.read((char*)(&num_humans), sizeof(num_humans));
    humans.resize(num_humans);
    for (size_t i = 0; i < num_humans; ++i) {
        file >> humans[i]; // Используем перегруженный оператор >> для Human
    }

    file.close();
    return true;
}