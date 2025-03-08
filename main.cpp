#include "menu/CMenu.h"
#include "menu/CMenuItem.h"
#include <cmath>
#include <ctime>

using namespace std;


#pragma region функции-заглушки
int f1() {
    std::cout << "function f1 is running...\n\n";
    return 1;
}

int f2() {
    std::cout << "function f2 is running...\n\n";
    return 2;
}

int f3() {
    std::cout << "function f3 is running...\n\n";
    return 3;
}


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

const int ITEMS_NUMBER = 6;


int main() {
    time_t currentTime = time(0);  // nullptr эквивалентно 0
    tm* localTime = localtime(&currentTime);

    int year = localTime->tm_year + 1900; // Год начинается с 1900
    int month = localTime->tm_mon + 1;   // Месяц начинается с 0 (январь = 0)
    int day = localTime->tm_mday;  

    cout<<day<<'.'<<month<<'.'<<year;


    // CMenuItem items[ITEMS_NUMBER] {CMenuItem{"first item", f1}, CMenuItem{"second item", f2}, CMenuItem{"third item", f3},CMenuItem{"Вычислить корень 25", sqrt_25}, CMenuItem{"Вычислить корень 25 графически", sqrt_25_graf}, CMenuItem{"Вычеслить корень числа", sqrt_with_enter}};
    // CMenu menu("My console menu", items, ITEMS_NUMBER);
    // while (menu.runCommand()) {};

    return 0;
}