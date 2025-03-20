#ifndef CHATBOT_H
#define CHATBOT_H

#include <iostream>
#include <string>
#include <vector>
#include "../date/date.h"

struct  NOTE{
private:
    DATE date;
    string message;

public:
    NOTE();
    NOTE(DATE,string);
    ~NOTE();

    DATE get_date();
    string get_message();

    void set_date(DATE);
    void set_message(string);

    bool operator>(const NOTE& other) const;
    bool operator>=(const NOTE& other) const;
    bool operator<=(const NOTE& other) const;
    bool operator<(const NOTE& other) const;
    bool operator==(const NOTE& other) const;
    bool operator!=(const NOTE& other) const;

    friend ostream& operator<<(ostream& os, const NOTE& note);
    friend istream& operator>>(istream& is, NOTE& note);
};


class CHATBOT
{
private:
    vector<NOTE> notes;
    DATE today;
    
    void sorted();
public:
    CHATBOT();
    CHATBOT(vector<NOTE> notes);
    ~CHATBOT();

    DATE get_today();
    int get_len();

    void add_note(NOTE note);
    vector<string> notes_today();
    vector<string> notes_day(DATE date);
    void pop_note(int pos);
    void del_note(NOTE note);
    void del_all_notes();
    void del_note_completed(int pos);
    void del_all_completed();

    void getWhatDayIsToday();
    void getWhatDayIs(DATE);

    friend ostream& operator<<(ostream& os, const CHATBOT& bot);
    friend istream& operator>>(istream& is, CHATBOT& bot);
    NOTE& operator[](int pos);
};

#endif //CHATBOT_H