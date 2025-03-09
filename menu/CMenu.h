#pragma once

//#include <cstddef>
#include <string>
#include "./CMenuItem.h"

using namespace std;


class CMenu {
    public:
        CMenu(string, CMenuItem *, size_t);
        int getSelect() const;
        bool isRun() const;
        string getTitle();
        size_t getCount() const;
        CMenuItem *getItems();
        void print();
        void runCommand();
        void setRunning(bool run);

    private:
        int select{-1};
        size_t count{};
        bool running{1};
        string title{};
        CMenuItem *items{};
};