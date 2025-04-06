#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <fstream>
#include <string>
#include "../../date/date.h"

using namespace std;

enum GENDER {
    male,
    femail
};

ostream& operator<<(ostream& os, const GENDER& gender);
istream& operator>>(istream& is, GENDER& gender);

class Human {
private:
    unsigned short id{};
    string name;
    MYDATE birth;
    GENDER gender;
    string login;
    string password;

public:
    Human(); 
    Human(string name, MYDATE birth, GENDER gender, string login, string password);
    ~Human();
    void set_name(string name);
    void set_password(string password);

    string get_name() const; 
    string get_login() const; 
    string get_password() const; 
    MYDATE get_DATE() const; 
    GENDER get_gender() const;   
    unsigned short get_age();
    void get_info();
    void printToConsoleInTable(ostream& os, int indents[5]);

    Human& operator=(const Human& other);
    friend ostream& operator<<(ostream& os, const Human& human);
    friend istream& operator>>(istream& is, Human& human);
};


class humanVector {
public:
    class VectorIterator {
        friend class humanVector; 

    public:
        VectorIterator(const VectorIterator& _it);
        bool operator==(const VectorIterator& _it) const;
        bool operator!=(const VectorIterator& _it) const;
        VectorIterator& operator++();
        VectorIterator& operator--();
        VectorIterator operator+(size_t index) const;
        Human& operator*() const;

    private:
        Human* m_human;
        VectorIterator(Human* _p);
    };

private:
    Human* m_array{};     
    Human* m_end{};       
    size_t m_size{};      

public:
    typedef VectorIterator iterator;       
    typedef VectorIterator const_iterator; 

    humanVector();               
    humanVector(unsigned _size); 
    ~humanVector();              

    iterator begin();               
    iterator end();                 
    const_iterator begin() const;   
    const_iterator end() const;     
    size_t size() const { return m_size; }

    Human& operator[](size_t index);       
    const Human& operator[](size_t index) const;

    void push_back(const Human& human); 
    void pop_back();                    
    void insert(iterator position, const Human& value);
    void erase(iterator position);              
    void resize(size_t size);                   
    void clear();                               
    bool empty() const;                         

    friend ostream& operator<<(ostream& os, const humanVector& humans);
};
    
bool writeHumansToFile(const string& filename, const humanVector& humans);
bool readHumansFromFile(const string& filename, humanVector& humans);

#endif // HUMAN_H