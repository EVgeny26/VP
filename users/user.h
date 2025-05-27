#ifndef USER_H
#define USER_H

#include "parent/human.h"
#include "../chatbot/chatbot.h"

class User : public Human {
    CHATBOT* bot;

public:
    User();
    User(string login, string password, string name, MYDATE birth, GENDER gender);
    User(const Human& human);
    ~User();

    CHATBOT* get_bot();
    void loudBot();
    void saveBot();

    void printNotes();

    friend ostream& operator<<(ostream& os, const User& obj);
    friend istream& operator>>(istream& is, User& obj);
};

#endif