#include "date.h"
#include <cstring>
#include <ctime>

bool DATEBIRTH::isValidDate(int d, int m, int y) const {
    if (y < 1 || m < 1 || m > 12 || d < 1) {
        return false;
    }
    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
        daysInMonth[2] = 29;
    }
    return d <= daysInMonth[m];
}

DATEBIRTH::DATEBIRTH(int d, int m, int y) : year(y), month(m), day(d) {
    while (!isValidDate(day, month, year)) {
        cerr << "Ошибка: Некорректная дата. Введите повторно(например: 3 5 2005)" << endl;
        cin>>day>>month>>year;
    }
}

int *StrDateToInt(string date){
    char cdate[date.length()+1];
    strcpy(cdate,date.c_str());
    int *idate = new int[3];
    char *word = strtok(cdate,".");
    idate[0]=stoi(word);
    word = strtok(nullptr,".");
    idate[1]=stoi(word);
    word = strtok(nullptr,".");
    idate[2]=stoi(word);
    return idate;
}

DATEBIRTH::DATEBIRTH(string date){
    int *idate=StrDateToInt(date);
    while (!isValidDate(idate[0], idate[1], idate[2])) {
        cerr << "Ошибка: Некорректная дата. Введите повторно(например: 4.5.2006)" << endl;
        cin>>date;
        idate=StrDateToInt(date);
    }
    day=idate[0];
    month=idate[1];
    year=idate[2];
    delete idate;
}

DATEBIRTH::DATEBIRTH(tm* localTime): day(localTime->tm_mday), month(localTime->tm_mon+1), year(localTime->tm_year+1900){}

unsigned short DATEBIRTH::get_day() const { return day; }
unsigned short DATEBIRTH::get_month() const { return month; }
unsigned short DATEBIRTH::get_year() const { return year; }


string DATEBIRTH::to_str() const {
    return to_string(day) + '.' + to_string(month) + '.' + to_string(year);
}


// Операторы сравнения DATEBIRTH
bool DATEBIRTH::operator>(const DATEBIRTH& other) const {
    if (year == other.year) {
        if (month == other.month) {
            return day > other.day;
        }
        return month > other.month;
    }
    return year > other.year;
}
bool DATEBIRTH::operator<=(const DATEBIRTH& other) const {
    return !operator>(other);
}
bool DATEBIRTH::operator<(const DATEBIRTH& other) const {
    if (year == other.year) {
        if (month == other.month) {
            return day < other.day;
        }
        return month < other.month;
    }
    return year < other.year;
}
bool DATEBIRTH::operator>=(const DATEBIRTH& other) const {
    return !operator<(other);
}
bool DATEBIRTH::operator==(const DATEBIRTH& other) const {
    return year==other.year && month==other.month && day==other.day;
}
bool DATEBIRTH::operator!=(const DATEBIRTH& other) const {
    return !operator==(other);
}


// Дружественная функция для записи DATEBIRTH в бинарный файл
ostream& operator<<(ostream& os, const DATEBIRTH& date) {
    os.write((char*)(&date.year), sizeof(date.year));
    os.write((char*)(&date.month), sizeof(date.month));
    os.write((char*)(&date.day), sizeof(date.day));
    return os;
}

// Дружественная функция для чтения DATEBIRTH из бинарного файла
istream& operator>>(istream& is, DATEBIRTH& date) {
    is.read((char*)(&date.year), sizeof(date.year));
    is.read((char*)(&date.month), sizeof(date.month));
    is.read((char*)(&date.day), sizeof(date.day));
    if (!date.isValidDate(date.day, date.month, date.year)) {
        cerr << "Ошибка: Прочитана некорректная дата из файла. Установлена дата по умолчанию (01-01-1970)." << endl;
        date.year = 1970;
        date.month = 1;
        date.day = 1;
    }
    return is;
}





// Операторы сравнения tm и DATEBIRTH
bool operator>(const DATEBIRTH& date, const tm* localTime){
    if (date.get_year() == localTime->tm_year+1900) {
        if (date.get_month() == localTime->tm_mon+1) {
            return date.get_day() > localTime->tm_mday;
        }
        return date.get_month() > localTime->tm_mon+1;
    }
    return date.get_year() > localTime->tm_year+1900;
}
bool operator<=(const DATEBIRTH& date, const tm* localTime){
    return !operator>(date, localTime);
}
bool operator<(const DATEBIRTH& date, const tm* localTime){
    if (date.get_year() == localTime->tm_year+1900) {
        if (date.get_month() == localTime->tm_mon+1) {
            return date.get_day() < localTime->tm_mday;
        }
        return date.get_month() < localTime->tm_mon+1;
    }
    return date.get_year() < localTime->tm_year+1900;
}
bool operator>=(const DATEBIRTH& date, const tm* localTime){
    return !operator<(date, localTime);
}
bool operator==(const DATEBIRTH& date, const tm* localTime){
    return date.get_day()==localTime->tm_mday && date.get_month()==localTime->tm_mon+1 && date.get_year()==localTime->tm_year+1900;
}
bool operator!=(const DATEBIRTH& date, const tm* localTime){
    return !operator==(date, localTime);
}



bool operator>(const tm* localTime, const DATEBIRTH& date){
    return date<localTime;
}
bool operator<=(const tm* localTime, const DATEBIRTH& date){
    return date>=localTime;
}
bool operator<(const tm* localTime, const DATEBIRTH& date){
    return date>localTime;
}
bool operator>=(const tm* localTime, const DATEBIRTH& date){
    return date<localTime;
}
bool operator==(const tm* localTime, const DATEBIRTH& date){
    return operator==(date, localTime);
}
bool operator!=(const tm* localTime, const DATEBIRTH& date){
    return operator!=(date, localTime);
}