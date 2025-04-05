#ifndef NOTEVECTOR_H
#define NOTEVECTOR_H

#include <iostream>
#include <string>
#include "../date/date.h"

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

class notesVector {
public:
    class VectorIterator {
        friend class notesVector;
    public:
        VectorIterator(const VectorIterator& _it);
        bool operator==(const VectorIterator& _it) const;
        bool operator!=(const VectorIterator& _it) const;
        VectorIterator& operator++();
        VectorIterator& operator--();
        VectorIterator& operator+(size_t index);
        NOTE& operator*() const;
    private:
        NOTE* m_note;
        VectorIterator(NOTE* _p);
    };

private:
    NOTE* m_array{};
    NOTE* m_end;
    size_t m_size{};

public:
    typedef VectorIterator iterator;
    typedef VectorIterator const_iterator;

    notesVector();
    notesVector(unsigned _size);
    ~notesVector();

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    size_t size() const { return m_size; }

    NOTE& operator[](size_t index);
    const NOTE& operator[](size_t index) const;

    // Добавленные методы для соответствия функциональности vector
    void push_back(const NOTE& note);
    void pop_back();
    void insert(iterator position, const NOTE& value);
    void erase(iterator position);
    void resize(size_t size);
    void clear();
    bool empty() const;
    friend ostream& operator<<(ostream& os, const notesVector& notes);
};



#endif //NOTEVECTOR_H