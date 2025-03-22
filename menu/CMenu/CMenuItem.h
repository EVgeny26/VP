#ifndef CMENUITEM_H
#define CMENUITEM_H

#include <iostream>
#include <string>
#include <functional>

using namespace std;


 class CMenuItem {
    public:
        using Func = std::function<void()>;
        CMenuItem(string, Func);
        ~CMenuItem();
        Func func{};
        string item_name{};
        string getName();
        void print();
        void run();
};

#endif // CMENUITEM_H