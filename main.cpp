#include "menu/CMenu.h"
#include "menu/CMenuItem.h"
#include <cmath>

using namespace std;


#pragma region функции-заглушки
int sqrt_25() {
    std::cout << "Корень 25 - это "<< sqrt(25) <<"\n\n";
    return 1;
}

int sqrt_25_graf() {
    cout<<"       ==============================                           "<<endl;
    cout<<"      ==                                                          "<<endl;
    cout<<"      =    =======          ======                ======              "<<endl;
    cout<<"     ==   ==      ==        =          =====      =                "<<endl;
    cout<<"     =             ==       =  ==                 =  ==           "<<endl;
    cout<<"    ==              =       ==    =    =====      ==    =           "<<endl;
    cout<<"==  =            ==                =                      =            "<<endl;
    cout<<" ====       ====                 ==                     ==            "<<endl;
    cout<<"  ==     =============       ====                   ====               "<<endl<<endl;

    return 2;
}

int sqrt_with_enter() {
    float num;
    cout<<"Введите число для вычисления корня: ";
    do{
        cin>>num;
        if(num<0)cout<<"Введите положительное число: ";
    }while (num<0);
    
    std::cout << "Корень "<<num<<" = "<<sqrt(num)<<endl<<endl;
    return 3;
}
#pragma endregion

const int ITEMS_NUMBER = 3;


int main() {
    CMenuItem items[ITEMS_NUMBER] {CMenuItem{"Вычислить корень 25", sqrt_25}, CMenuItem{"Вычислить корень 25 графически", sqrt_25_graf}, CMenuItem{"Вычеслить корень числа", sqrt_with_enter}};
    CMenu menu("My console menu", items, ITEMS_NUMBER);
    while (menu.runCommand()) {};

    return 0;
}