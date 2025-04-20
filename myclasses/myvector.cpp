#include "myvector.h"
#include "../users/parent/human.h"  
#include "../chatbot/chatbot.h"

template <typename T>
Vector<T>::VectorIterator::VectorIterator(const VectorIterator& _it) : m_item(_it.m_item) {}

template <typename T>
bool Vector<T>::VectorIterator::operator==(const VectorIterator& _it) const {
    return m_item == _it.m_item;
}

template <typename T>
bool Vector<T>::VectorIterator::operator!=(const VectorIterator& _it) const {
    return m_item != _it.m_item;
}

template <typename T>
typename Vector<T>::VectorIterator& Vector<T>::VectorIterator::operator++() {
    m_item++;
    return *this;
}

template <typename T>
typename Vector<T>::VectorIterator& Vector<T>::VectorIterator::operator--(){
    m_item--;
    return *this;
}

template <typename T>
typename Vector<T>::VectorIterator& Vector<T>::VectorIterator::operator+(size_t index){
    m_item+=index;
    return *this;
}

template <typename T>
T& Vector<T>::VectorIterator::operator*() const {
    return *m_item;
}
template <typename T>
Vector<T>::VectorIterator::VectorIterator(T* _p) : m_item(_p) {}

template <typename T>
Vector<T>::Vector() : m_array(nullptr), m_end(nullptr), m_size(0) {}

template <typename T>
Vector<T>::Vector(unsigned _size) : m_size(_size) {
    m_array = new T[m_size];
    if (m_size) {
        T temp;
        for (int i = 0; i < m_size; ++i) {
            m_array[i] = temp;
        }
    }
    m_end = m_array + m_size;
}

template <typename T>
Vector<T>::~Vector<T>() {
    delete[] m_array;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {
    return iterator(m_array);
}
template <typename T>
typename Vector<T>::iterator Vector<T>::end() {
    return iterator(m_end);
}
template <typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const {
    return const_iterator(m_array);
}
template <typename T>
typename Vector<T>::const_iterator Vector<T>::end() const {
    return const_iterator(m_end);
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    if (index < m_size) {
        return m_array[index];
    }
    throw out_of_range("Index out of range"); // Или другой способ обработки ошибки
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index < m_size) {
        return m_array[index];
    }
    throw out_of_range("Index out of range"); // Или другой способ обработки ошибки
}

template <typename T>
void Vector<T>::push_back(const T& note) {
    insert(end(), note);
}

template <typename T>
void Vector<T>::pop_back() {
    if (m_size > 0) {
        erase(--end());
    }
}

template <typename T>
void Vector<T>::insert(iterator position, const T& value) {
    size_t index = 0;
    for (iterator it = begin(); it != end(); ++it, ++index) {
        if (it == position) {
            break;
        }
    }

    T* new_array = new T[m_size + 1];
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

template <typename T>
void Vector<T>::erase(iterator position) {
    size_t index = 0;
    for (iterator it = begin(); it != end(); ++it, ++index) {
        if (it == position) {
            break;
        }
    }

    T* new_array = new T[m_size - 1];
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

template <typename T>
void Vector<T>::resize(size_t size){
    T* new_array = new T[size];
    if(m_size>=size){
        for (size_t i = 0; i < size; ++i) {
            new_array[i] = m_array[i];
        }
    }else{
        for (size_t i = 0; i < m_size; ++i) {
            new_array[i] = m_array[i];
        }
        for (size_t i = m_size; i < size; ++i) {
            new_array[i] = T();
        }
    }

    delete[] m_array;
    m_array = new_array;
    m_size=size;
    m_end = m_array + m_size;
}

template <typename T>
void Vector<T>::clear() {
    delete[] m_array;
    m_array = nullptr;
    m_end = nullptr;
    m_size = 0;
}

template <typename T>
bool Vector<T>::empty() const {
    return m_size == 0;
}

template class Vector<NOTE>;
template class Vector<Human>;