#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <string>

template <typename T>
class Vector {
    public:
        class VectorIterator {
            friend class Vector;
        public:
            VectorIterator(const VectorIterator& _it);
            bool operator==(const VectorIterator& _it) const;
            bool operator!=(const VectorIterator& _it) const;
            VectorIterator& operator++();
            VectorIterator& operator--();
            VectorIterator& operator+(size_t index);
            T& operator*() const;
        private:
            T* m_item;
            VectorIterator(T* _p);
        };
    
    private:
        T* m_array{};
        T* m_end;
        size_t m_size{};
    
    public:
        typedef VectorIterator iterator;
        typedef VectorIterator const_iterator;
    
        Vector();
        Vector(unsigned _size);
        ~Vector();
    
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
    
        size_t size() const { return m_size; }
    
        T& operator[](size_t index);
        const T& operator[](size_t index) const;
    
        void push_back(const T& note);
        void pop_back();
        void insert(iterator position, const T& value);
        void erase(iterator position);
        void resize(size_t size);
        void clear();
        bool empty() const;
    };
    
    
    
    #endif //VECTOR_H