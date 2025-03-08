#include "admin.h"
#include <iomanip>

Admin::Admin(string name, DATEBIRTH birth, GENDER gender, string login, string password): Human(name, birth, gender, login, password) {}
Admin::~Admin(){}

void Admin::add_user(User user){
    users.push_back(user);
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
                    isChangee=users[j].get_datebirth()>users[j+1].get_datebirth();
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

void Admin::pritall(){
    cout<<setw(10)<<"login"<<setw(20)<<"name"<<setw(12)<<"datebirth";
    cout<<"gen"<<setw(12)<<"password"<<endl;
    for(int i=0;i<users.size();i++){
        cout<<users[i];
    }
}