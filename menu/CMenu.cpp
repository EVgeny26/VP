#include "./CMenu.h"

CMenu::CMenu(string title, CMenuItem *items, size_t count) : title(title), items(items), count(count) {}

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
    for (size_t i{}; i < count; ++i) {
        std::cout << i + 1 << ". ";
        items[i].print();
        std::cout << std::endl;
    }
    std::cout << "0. выйти" << std::endl;
}

void CMenu::runCommand() {
    do{
        print();
        std::cout << "\n   Ввод >> ";
        std::cin >> select;
    }while(select<0 || select>count);
    if (select==0) {
        setRunning(false); // Устанавливаем running в false при выборе "выйти"
        return;
    }items[select - 1].run();
    
}