#ifndef USER_H
#define USER_H

#include "parent/human.h"
#include "../chatbot/chatbot.h"

class User : public Human {
    CHATBOT* bot;

public:
    User();
    User(string login, string password, string name, MYDATE birth, GENDER gender);
    ~User();

    CHATBOT* get_bot();
    void loudBot();
    void saveBot();

    // Методы с ботом
    void printNotes();
    void printCompletedNotes();
    void printNotesDay(MYDATE date);


    // Дружественные функции для ввода/вывода
    friend ostream& operator<<(ostream& os, const User& obj);
    friend istream& operator>>(istream& is, User& obj);
};

#endif