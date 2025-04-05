#include <ctime>
#include <fstream>
#include <cstring>
#include <iomanip>

#include "notesVector.h"

NOTE::NOTE(): date(MYDATE()), message((string)""){}
NOTE::NOTE(MYDATE date, string message): date(date), message(message){}
NOTE::~NOTE(){}

MYDATE NOTE::get_date(){return date;}
string NOTE::get_message(){return message;}

void NOTE::set_date(MYDATE date){this->date=date;}
void NOTE::set_message(string message){this->message=message;}

bool NOTE::operator>(const NOTE& other) const{
    if(this->date==other.date)return this->message>other.message;
    return this->date>other.date;
}
bool NOTE::operator<(const NOTE& other) const{
    if(this->date==other.date)return this->message<other.message;
    return this->date<other.date;
}
bool NOTE::operator<=(const NOTE& other) const{
    return !operator>(other);
}
bool NOTE::operator>=(const NOTE& other) const{
    return !operator<(other);
}
bool NOTE::operator==(const NOTE& other) const{
    return this->date==other.date && this->message==other.message;
}
bool NOTE::operator!=(const NOTE& other) const{
    return !operator==(other);
}

ostream& operator<<(ostream& os, const NOTE& note){
    os<<note.date;
    size_t message_len = note.message.size();
    os.write((char*)(&message_len), sizeof(message_len));
    os.write(note.message.c_str(), message_len);
    return os;
}
istream& operator>>(istream& is, NOTE& note){
    is>>note.date;
    if(!is.fail()){
        size_t message_len;
        is.read((char*)(&message_len), sizeof(message_len));
        char *str = new char[message_len+1];
        is.read(str, message_len);
        note.message=str;
        delete[] str;
    }
    return is;
}

NOTE& NOTE::operator=(const NOTE& other){
    if (this != &other) {
        date = other.date;
        message = other.message;
    }
    return *this;
}


// VectorIterator Implementation
notesVector::VectorIterator::VectorIterator(const VectorIterator& _it) : m_note(_it.m_note) {}

bool notesVector::VectorIterator::operator==(const VectorIterator& _it) const {
    return m_note == _it.m_note;
}

bool notesVector::VectorIterator::operator!=(const VectorIterator& _it) const {
    return m_note != _it.m_note;
}

notesVector::VectorIterator& notesVector::VectorIterator::operator++() {
    m_note++;
    return *this;
}
notesVector::VectorIterator& notesVector::VectorIterator::operator--(){
    m_note--;
    return *this;
}
notesVector::VectorIterator& notesVector::VectorIterator::operator+(size_t index){
    m_note+=index;
    return *this;
}

NOTE& notesVector::VectorIterator::operator*() const {
    return *m_note;
}

notesVector::VectorIterator::VectorIterator(NOTE* _p) : m_note(_p) {}

// notesVector Implementation
notesVector::notesVector() : m_array(nullptr), m_end(nullptr), m_size(0) {}

notesVector::notesVector(unsigned _size) : m_size(_size) {
    m_array = new NOTE[m_size];
    if (m_size) {
        NOTE temp;
        for (int i = 0; i < m_size; ++i) {
            m_array[i] = temp;
        }
    }
    m_end = m_array + m_size;
}

notesVector::~notesVector() {
    delete[] m_array;
}

notesVector::iterator notesVector::begin() {
    return iterator(m_array);
}

notesVector::iterator notesVector::end() {
    return iterator(m_end);
}

notesVector::const_iterator notesVector::begin() const {
    return const_iterator(m_array);
}

notesVector::const_iterator notesVector::end() const {
    return const_iterator(m_end);
}

ostream& operator<<(ostream& os, const notesVector& notes){
    os<<"   ДАТА   : Заметка"<<endl;
    for(NOTE note : notes){
        os<<right<<setw(10)<<note.get_date().to_str()<<": "<<note.get_message()<<endl;
    }return os;
}


NOTE& notesVector::operator[](size_t index) {
    if (index < m_size) {
        return m_array[index];
    }
    throw out_of_range("Index out of range"); // Или другой способ обработки ошибки
}

const NOTE& notesVector::operator[](size_t index) const {
    if (index < m_size) {
        return m_array[index];
    }
    throw out_of_range("Index out of range"); // Или другой способ обработки ошибки
}


void notesVector::push_back(const NOTE& note) {
    insert(end(), note);
}

void notesVector::pop_back() {
    if (m_size > 0) {
        erase(--end());
    }
}

void notesVector::insert(iterator position, const NOTE& value) {
    size_t index = 0;
    for (iterator it = begin(); it != end(); ++it, ++index) {
        if (it == position) {
            break;
        }
    }

    NOTE* new_array = new NOTE[m_size + 1];
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

void notesVector::erase(iterator position) {
    size_t index = 0;
    for (iterator it = begin(); it != end(); ++it, ++index) {
        if (it == position) {
            break;
        }
    }

    NOTE* new_array = new NOTE[m_size - 1];
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

void notesVector::resize(size_t size){
    NOTE* new_array = new NOTE[size];
    if(m_size>=size){
        for (size_t i = 0; i < size; ++i) {
            new_array[i] = m_array[i];
        }
    }else{
        for (size_t i = 0; i < m_size; ++i) {
            new_array[i] = m_array[i];
        }
        for (size_t i = m_size; i < size; ++i) {
            new_array[i] = NOTE();
        }
    }

    delete[] m_array;
    m_array = new_array;
    m_size=size;
    m_end = m_array + m_size;
}

void notesVector::clear() {
    delete[] m_array;
    m_array = nullptr;
    m_end = nullptr;
    m_size = 0;
}

bool notesVector::empty() const {
    return m_size == 0;
}