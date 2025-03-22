#include "date.h"
#include <cstring>
#include <ctime>

bool MYDATE::isValidDate(int d, int m, int y) const {
    if (y < 1 || m < 1 || m > 12 || d < 1) {
        return false;
    }
    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
        daysInMonth[2] = 29;
    }
    return d <= daysInMonth[m];
}

MYDATE::MYDATE(int d, int m, int y) : year(y), month(m), day(d) {
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

MYDATE::MYDATE(string date){
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

MYDATE::MYDATE(tm* localTime): day(localTime->tm_mday), month(localTime->tm_mon+1), year(localTime->tm_year+1900){}

unsigned short MYDATE::get_day() const { return day; }
unsigned short MYDATE::get_month() const { return month; }
unsigned short MYDATE::get_year() const { return year; }


string MYDATE::to_str() const {
    return to_string(day) + '.' + to_string(month) + '.' + to_string(year);
}


// Операторы сравнения MYDATE
bool MYDATE::operator>(const MYDATE& other) const {
    if (year == other.year) {
        if (month == other.month) {
            return day > other.day;
        }
        return month > other.month;
    }
    return year > other.year;
}
bool MYDATE::operator<=(const MYDATE& other) const {
    return !operator>(other);
}
bool MYDATE::operator<(const MYDATE& other) const {
    if (year == other.year) {
        if (month == other.month) {
            return day < other.day;
        }
        return month < other.month;
    }
    return year < other.year;
}
bool MYDATE::operator>=(const MYDATE& other) const {
    return !operator<(other);
}
bool MYDATE::operator==(const MYDATE& other) const {
    return year==other.year && month==other.month && day==other.day;
}
bool MYDATE::operator!=(const MYDATE& other) const {
    return !operator==(other);
}


// Дружественная функция для записи DATE в бинарный файл
ostream& operator<<(ostream& os, const MYDATE& date) {
    if(&os==&cout){
        os<<date.day<<'.'<<date.month<<'.'<<date.year;
    }else{
        os.write((char*)(&date.year), sizeof(date.year));
        os.write((char*)(&date.month), sizeof(date.month));
        os.write((char*)(&date.day), sizeof(date.day));
    }
    return os;
}

// Дружественная функция для чтения DATE из бинарного файла
istream& operator>>(istream& is, MYDATE& date) {
    is.read((char*)(&date.year), sizeof(date.year));
    if(is.fail()) {
        cerr << "Ошибка чтения года.\n";
        return is;
    }
    is.read((char*)(&date.month), sizeof(date.month));
     if(is.fail()) {
        cerr << "Ошибка чтения месяца.\n";
        return is;
    }
    is.read((char*)(&date.day), sizeof(date.day));
     if(is.fail()) {
        cerr << "Ошибка чтения дня.\n";
        return is;
    }
    if (!date.isValidDate(date.day, date.month, date.year)) {
        cerr << "Ошибка: Прочитана некорректная дата из файла. Установлена дата по умолчанию (01-01-1970)." << endl;
        date.year = 1970;
        date.month = 1;
        date.day = 1;
    }
    return is;
}


// Операторы сравнения tm и MYDATE
bool operator>(const MYDATE& date, const tm* localTime){
    if (date.get_year() == localTime->tm_year+1900) {
        if (date.get_month() == localTime->tm_mon+1) {
            return date.get_day() > localTime->tm_mday;
        }
        return date.get_month() > localTime->tm_mon+1;
    }
    return date.get_year() > localTime->tm_year+1900;
}
bool operator<=(const MYDATE& date, const tm* localTime){
    return !operator>(date, localTime);
}
bool operator<(const MYDATE& date, const tm* localTime){
    if (date.get_year() == localTime->tm_year+1900) {
        if (date.get_month() == localTime->tm_mon+1) {
            return date.get_day() < localTime->tm_mday;
        }
        return date.get_month() < localTime->tm_mon+1;
    }
    return date.get_year() < localTime->tm_year+1900;
}
bool operator>=(const MYDATE& date, const tm* localTime){
    return !operator<(date, localTime);
}
bool operator==(const MYDATE& date, const tm* localTime){
    return date.get_day()==localTime->tm_mday && date.get_month()==localTime->tm_mon+1 && date.get_year()==localTime->tm_year+1900;
}
bool operator!=(const MYDATE& date, const tm* localTime){
    return !operator==(date, localTime);
}



bool operator>(const tm* localTime, const MYDATE& date){
    return date<localTime;
}
bool operator<=(const tm* localTime, const MYDATE& date){
    return date>=localTime;
}
bool operator<(const tm* localTime, const MYDATE& date){
    return date>localTime;
}
bool operator>=(const tm* localTime, const MYDATE& date){
    return date<localTime;
}
bool operator==(const tm* localTime, const MYDATE& date){
    return operator==(date, localTime);
}
bool operator!=(const tm* localTime, const MYDATE& date){
    return operator!=(date, localTime);
}