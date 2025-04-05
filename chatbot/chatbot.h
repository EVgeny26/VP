#ifndef CHATBOT_H
#define CHATBOT_H

#include <iostream>
#include <string>
#include "notesVector.h"
#include "../date/date.h"

class CHATBOT
{
private:
    notesVector notes;
    MYDATE today;
    
    void sorted();
public:
    CHATBOT();
    CHATBOT(notesVector notes);
    ~CHATBOT();

    MYDATE get_today();
    notesVector& get_notes();
    int get_len();

    void add_note(NOTE note);
    void notes_today();
    void notes_day(MYDATE date);
    void pop_note(int pos);
    void del_note(NOTE note);
    void del_all_notes();
    void del_note_completed(int pos);
    void del_all_completed();

    void getWhatDayIsToday();
    void getWhatDayIs(MYDATE);

    void loud(string login);
    void save(string login);

    friend ostream& operator<<(ostream& os, const CHATBOT& bot);
    friend istream& operator>>(istream& is, CHATBOT& bot);
    NOTE& operator[](int pos);

    void temp();
};

#endif //CHATBOT_H