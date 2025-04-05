#ifndef HUMANVECTOR_H
#define HUMANVECTOR_H

#include "human.h"
#include <iostream>


class humanVector {
public:
    class VectorIterator {
        friend class humanVector; // Allow humanVector to access private members

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

    // Iterator methods
    iterator begin();               
    iterator end();                 
    const_iterator begin() const;   
    const_iterator end() const;     

    // Size method
    size_t size() const { return m_size; } // Returns the number of elements

    // Element access methods
    Human& operator[](size_t index);       // Mutable access to an element
    const Human& operator[](size_t index) const; // Constant access to an element

    // Modifying methods (matching vector functionality)
    void push_back(const Human& human); // Adds an element to the end
    void pop_back();                    // Removes the last element
    void insert(iterator position, const Human& value); // Inserts an element at a specific position
    void erase(iterator position);                  // Removes an element at a specific position
    void resize(size_t size);                    // Resizes the vector
    void clear();                                 // Removes all elements
    bool empty() const;                           // Checks if the vector is empty

    // Friend function for output
    friend ostream& operator<<(ostream& os, const humanVector& humans);
};


#endif // HUMANVECTOR_H