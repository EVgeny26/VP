#include "admin.h"
#include "../controlEnter/control.h"
#include <iomanip>
#include <fstream>

Admin::Admin(string name, MYDATE birth, GENDER gender, string login, string password): Human(name, birth, gender, login, password) {}
Admin::~Admin(){}

void Admin::add_user(User user){
    users.push_back(user);
}
void Admin::add_user(){
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
    users.push_back(User{name,birth,(GENDER)gender,login,password});
    cout<<"Пользователь введен\n\n";
}
void Admin::del_user(int pos){
    if(pos>=users.size()){
        cerr<<"Out of range\n";
        return;
    }
    users.erase(users.begin()+pos);
}
void Admin::del_user(string login){
    for(int i=0;i<users.size();i++){
        if(login==users[i].get_login()){
            users.erase(users.begin()+i);
            return;
        }
    }cerr<<"Login don\'t find\n";
}

void Admin::sorted(int pole=0, bool revers=0){
    bool isChangee{};
    for (int i = 0; i < users.size(); i++) {
        for (int j = 0; j < users.size() - i-1; j++) {
            switch (pole){
                case 0: 
                    isChangee=users[j].get_name()>users[j+1].get_name();
                    break;
                case 1: 
                    isChangee=users[j].get_login()>users[j+1].get_login();
                    break;
                case 2: 
                    isChangee=users[j].get_DATE()>users[j+1].get_DATE();
                    break;
                default:
                    return;
            }
            if (revers)isChangee-=1;
            if (isChangee) {
                User temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }
}

void printLine(int indents[5]) {
    cout << setfill('-')
              << '+' << right << setw(indents[0] + 1) << "+"
              << setw(indents[1] + 1) << "+"
              << setw(indents[2] + 1) << "+"
              << setw(indents[3] + 1) << "+"
              << setw(indents[4] + 1) << "+"
              << endl;
}

void printNameColumn(int indents[5]) {
    cout << setfill(' ')
              << left << "|" << setw(indents[0]) <<"login"
              << left << "|" << setw(indents[1]) << "name"
              << left << "|" << setw(indents[2]) << "DATE"
              << right << "|" << setw(indents[3]) << "gen"
              << right << "|" << setw(indents[4])<< "password"<<"|" << endl;
}

void Admin::pritall(){
    int indents[5]{15,20,16,10,12};
    printLine(indents);
    printNameColumn(indents);
    for(int i=0;i<users.size();i++){
        printLine(indents);
        users[i].printToConsoleInTable(cout, indents);
    }printLine(indents);
}

bool Admin::loud_to_file(string filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл для записи: " << filename << endl;
        return 0;
    }

    size_t num_users = users.size();
    file.write((char*)(&num_users), sizeof(num_users));

    for (const User& user : users) {
        file << user; // Используем перегруженный оператор << для User
    }

    file.close();
    return 1;
}

bool Admin::loud_from_file(string filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл для чтения: " << filename << endl;
        return 0;
    }

    size_t num_users;
    file.read((char*)(&num_users), sizeof(num_users));
    users.resize(num_users);

    for (size_t i = 0; i < num_users; ++i) {
        file >> users[i]; // Используем перегруженный оператор >> для User
    }

    file.close();
    return 1;
}

// ostream& operator<<(ostream& os, const Admin& obj) {
//     os << static_cast<const Human&>(obj);
//     return os;
// }

// istream& operator>>(istream& is, Admin& obj) {
//     is >> static_cast<Human&>(obj);
//     return is;
// }