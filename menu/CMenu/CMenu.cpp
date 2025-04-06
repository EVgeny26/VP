#include "./CMenu.h"
#include "../../controlEnter/control.h"

void returnToMainMenu() {
    cout << "Возвращение в главное меню...\n";
}

CMenu::CMenu(string title, CMenuItem *items, size_t count) : title(title), items(items), count(count) {}

CMenu::~CMenu(){
    delete[] items;
}

int CMenu::getSelect() const {
    return select;
}

bool CMenu::isRun() const {
    return running;
}

size_t CMenu::getCount() const {
    return count;
}

string CMenu::getTitle() {
    return title;
}

CMenuItem *CMenu::getItems() {
    return items;
}

void CMenu::setRunning(bool run){
    running=run;
}

void CMenu::print() {
    for (size_t i{}; i < count-1; ++i) {
        cout << i + 1 << ". ";
        items[i].print();
        cout << endl;
    }
    cout << 0 << ". ";
    items[count-1].print();
    cout << endl;
}

void CMenu::runCommand() {
    cout<<endl;
    do{
        cout<<title<<endl;
        print();
        cout << "\n   Ввод >> ";
        select=getCorNum();
    }while(select<0 || select>count-1);
    if (select==0) {
        setRunning(false); // Устанавливаем running в false при выборе "выйти"
        items[count - 1].run();
        return;
    }items[select - 1].run();
    
}