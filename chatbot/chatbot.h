#ifndef CHATBOT_H
#define CHATBOT_H

#include <iostream>
#include <string>
#include "../myclasses/myvector.h"
#include "../myclasses/date.h"

struct  NOTE{
private:
    MYDATE date;
    string message;

public:
    NOTE();
    NOTE(MYDATE,string);
    ~NOTE();

    MYDATE get_date();
    string get_message();

    void set_date(MYDATE);
    void set_message(string);

    bool operator>(const NOTE& other) const;
    bool operator>=(const NOTE& other) const;
    bool operator<=(const NOTE& other) const;
    bool operator<(const NOTE& other) const;
    bool operator==(const NOTE& other) const;
    bool operator!=(const NOTE& other) const;

    friend ostream& operator<<(ostream& os, const NOTE& note);
    friend istream& operator>>(istream& is, NOTE& note);
    NOTE& operator=(const NOTE& other);
};


class CHATBOT
{
private:
    Vector<NOTE> notes;
    MYDATE today;
    
    void sorted();
public:
    CHATBOT();
    CHATBOT(Vector<NOTE> notes);
    ~CHATBOT();

    MYDATE get_today();
    Vector<NOTE>& get_notes();
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
};

ostream& operator<<(ostream& os, const Vector<NOTE>& notes);

#endif //CHATBOT_H