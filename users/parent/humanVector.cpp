#include "humanVector.h"

humanVector::humanVector() : m_array(nullptr), m_end(nullptr), m_size(0) {}
humanVector::humanVector(unsigned _size) : m_array(nullptr), m_end(nullptr), m_size(0) {
    if (_size > 0) {
        m_array = new Human[_size]; 
        m_end = m_array + _size;    
    }
}

humanVector::~humanVector() {
    clear(); 
    delete[] m_array; 
}

humanVector::VectorIterator::VectorIterator(const VectorIterator& _it) : m_human(_it.m_human) {}
bool humanVector::VectorIterator::operator==(const VectorIterator& _it) const { return m_human == _it.m_human; }
bool humanVector::VectorIterator::operator!=(const VectorIterator& _it) const { return m_human != _it.m_human; }

humanVector::VectorIterator& humanVector::VectorIterator::operator++() {
    ++m_human;
    return *this;
}
humanVector::VectorIterator& humanVector::VectorIterator::operator--() {
    --m_human;
    return *this;
}
humanVector::VectorIterator humanVector::VectorIterator::operator+(size_t index) const{
    return VectorIterator(m_human + index);
}
Human& humanVector::VectorIterator::operator*() const { return *m_human; }
humanVector::VectorIterator::VectorIterator(Human* _p) : m_human(_p) {}
humanVector::iterator humanVector::begin() { return iterator(m_array); }
humanVector::iterator humanVector::end() { return iterator(m_array + m_size); }
humanVector::const_iterator humanVector::begin() const { return const_iterator(m_array); }
humanVector::const_iterator humanVector::end() const { return const_iterator(m_array + m_size); }
Human& humanVector::operator[](size_t index) {
    if (index >= m_size) {
        throw out_of_range("Index out of bounds");
    }
    return m_array[index];
}

// Constant access to an element
const Human& humanVector::operator[](size_t index) const {
    if (index >= m_size) {
        throw out_of_range("Index out of bounds");
    }
    return m_array[index];
}

// Adds an element to the end
void humanVector::push_back(const Human& human) {
    insert(end(), human);
}

// Removes the last element
void humanVector::pop_back() {
    if (m_size > 0) {
        --m_size;
    }
}

// Inserts an element at a specific position
void humanVector::insert(iterator position, const Human& value) {
    size_t index = 0;
    for (iterator it = begin(); it != end(); ++it, ++index) {
        if (it == position) {
            break;
        }
    }

    Human* new_array = new Human[m_size + 1];
    for (size_t i = 0; i < index; ++i) {
        new_array[i] = m_array[i];
    }
    new_array[index] = value;
    for (size_t i = index; i < m_size; ++i) {
        new_array[i + 1] = m_array[i];
    }

    delete[] m_array;
    m_array = new_array;
    m_size++;
    m_end = m_array + m_size;
}

// Removes an element at a specific position
void humanVector::erase(iterator position) {
    size_t index = 0;
    for (iterator it = begin(); it != end(); ++it, ++index) {
        if (it == position) {
            break;
        }
    }

    Human* new_array = new Human[m_size - 1];
    for (size_t i = 0; i < index; ++i) {
        new_array[i] = m_array[i];
    }
    for (size_t i = index + 1; i < m_size; ++i) {
        new_array[i - 1] = m_array[i];
    }

    delete[] m_array;
    m_array = new_array;
    m_size--;
    m_end = m_array + m_size;
}

// Resizes the vector
void humanVector::resize(size_t size) {
    Human* new_array = new Human[size];
    if(m_size>=size){
        for (size_t i = 0; i < size; ++i) {
            new_array[i] = m_array[i];
        }
    }else{
        for (size_t i = 0; i < m_size; ++i) {
            new_array[i] = m_array[i];
        }
        for (size_t i = m_size; i < size; ++i) {
            new_array[i] = Human();
        }
    }

    delete[] m_array;
    m_array = new_array;
    m_size=size;
    m_end = m_array + m_size;
}

// Removes all elements
void humanVector::clear() {
    //Explicitly iterate and call the destructor.  This prevents memory errors down the line.
    for(size_t i = 0; i < m_size; i++){
        m_array[i] = Human();
    }
    m_size = 0; // Reset the size
}

// Checks if the vector is empty
bool humanVector::empty() const { return m_size == 0; }

// Friend function for output
ostream& operator<<(ostream& os, const humanVector& humans) {
    os << "[";
    for (size_t i = 0; i < humans.size(); ++i) {
        os << humans[i].get_name(); // Assuming Human has a get_name() method
        if (i < humans.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}