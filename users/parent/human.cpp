#include "human.h"  // Всегда первым включаем заголовочный файл класса
#include <ctime>   // Для локального времени при обработке даты
#include <iomanip> // Для put_time
#include <iostream> // для cerr
#include <limits>  // для numeric_limits

using namespace std;

bool DATEBIRTH::isValidDate(int d, int m, int y) const {
    if (y < 1 || m < 1 || m > 12 || d < 1) {
        return false;
    }
    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
        daysInMonth[2] = 29;
    }
    return d <= daysInMonth[m];
}

DATEBIRTH::DATEBIRTH(int d, int m, int y) : year(y), month(m), day(d) {
    while (!isValidDate(day, month, year)) {
        cerr << "Ошибка: Некорректная дата. Введите повторно(например: 3 5 2005)" << endl;
        cin>>day>>month>>year;
    }
}

unsigned short DATEBIRTH::get_day() const { return day; }
unsigned short DATEBIRTH::get_month() const { return month; }
unsigned short DATEBIRTH::get_year() const { return year; }
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

string DATEBIRTH::to_str() const {
    return to_string(day) + '.' + to_string(month) + '.' + to_string(year);
}

bool DATEBIRTH::operator>(const DATEBIRTH& other) const {
    if (year == other.year) {
        if (month == other.month) {
            return day > other.day;
        }
        return month > other.month;
    }
    return year > other.year;
}

// Дружественная функция для записи DATEBIRTH в бинарный файл
ostream& operator<<(ostream& os, const DATEBIRTH& date) {
    os.write((char*)(&date.year), sizeof(date.year));
    os.write((char*)(&date.month), sizeof(date.month));
    os.write((char*)(&date.day), sizeof(date.day));
    return os;
}

// Дружественная функция для чтения DATEBIRTH из бинарного файла
istream& operator>>(istream& is, DATEBIRTH& date) {
    is.read((char*)(&date.year), sizeof(date.year));
    is.read((char*)(&date.month), sizeof(date.month));
    is.read((char*)(&date.day), sizeof(date.day));
    if (!date.isValidDate(date.day, date.month, date.year)) {
        cerr << "Ошибка: Прочитана некорректная дата из файла. Установлена дата по умолчанию (01-01-1970)." << endl;
        date.year = 1970;
        date.month = 1;
        date.day = 1;
    }
    return is;
}

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

Human::Human() : name(""), birth(), gender(male), login(""), password("") {}
Human::Human(string name, DATEBIRTH birth, GENDER gender, string login, string password) :
    name(name), birth(birth), gender(gender), login(login), password(password) {}

Human::~Human() {}

void Human::set_name(string name) { this->name = name; }
void Human::set_password(string password) { this->password = password; }

string Human::get_name() const { return name; }
string Human::get_login() const { return login; }
string Human::get_password() const { return password; }
DATEBIRTH Human::get_datebirth() const { return birth; }
GENDER Human::get_gender() const { return gender; }

// Дружественная функция для записи Human в бинарный файл
ostream& operator<<(ostream& os, const Human& human) {
    size_t name_len = human.name.size();
    os.write((char*)(&name_len), sizeof(name_len));
    os.write(human.name.c_str(), name_len);

    os << human.birth; // Используем перегруженный оператор << для DATEBIRTH
    os << human.gender; // Используем перегруженный оператор << для GENDER

    size_t login_len = human.login.size();
    os.write((char*)(&login_len), sizeof(login_len));
    os.write(human.login.c_str(), login_len);

    size_t password_len = human.password.size();
    os.write((char*)(&password_len), sizeof(password_len));
    os.write(human.password.c_str(), password_len);

    return os;
}

// Дружественная функция для чтения Human из бинарного файла
istream& operator>>(istream& is, Human& human) {
    size_t name_len;
    is.read((char*)(&name_len), sizeof(name_len));
    char *str = new char[name_len];
    is.read(str, name_len);
    human.name=str;
    delete str;

    is >> human.birth; // Используем перегруженный оператор >> для DATEBIRTH
    is >> human.gender; // Используем перегруженный оператор >> для GENDER

    size_t login_len;
    is.read((char*)(&login_len), sizeof(login_len));
    str = new char[login_len];
    is.read(str, login_len);
    human.login=str;
    delete str;

    size_t password_len;
    is.read((char*)(&password_len), sizeof(password_len));
    str = new char[password_len];
    is.read(str, password_len);
    human.password=str;
    delete str;

    return is;
}

// Функция для записи массива Human в бинарный файл
bool writeHumansToFile(const string& filename, const vector<Human>& humans) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл для записи: " << filename << endl;
        return false;
    }

    size_t num_humans = humans.size();
    file.write((char*)(&num_humans), sizeof(num_humans));

    for (const auto& human : humans) {
        file << human; // Используем перегруженный оператор << для Human
    }

    file.close();
    return true;
}

// Функция для чтения массива Human из бинарного файла
bool readHumansFromFile(const string& filename, vector<Human>& humans) {
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