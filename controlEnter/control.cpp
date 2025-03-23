#include "control.h"

bool isValidString(const string& str) {
    for (char c : str) {
        if (!isalnum(c)) {
            return false; // Если символ не буква и не цифра - строка не валидна
        }
    }
    return true;
}

// Вспомогательная функция для проверки наличия букв и цифр в строке
bool hasLettersAndDigits(const string& str) {
    bool hasLetter = false;
    bool hasDigit = false;
    for (char c : str) {
        if (isalpha(c)) {
            hasLetter = true;
        } else if (isdigit(c)) {
            hasDigit = true;
        }
    }
    return hasLetter && hasDigit;
}

// Функция для получения корректной даты
MYDATE getCorDate() {
    int day, month, year;
    while (true) {
        cout << "Введите день: ";
        cin >> day;
        cout << "Введите месяц: ";
        cin >> month;
        cout << "Введите год: ";
        cin >> year;

        if (cin.fail()) {
            cout << "Ошибка: Некорректный ввод. Пожалуйста, введите числа.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (day >= 1 && day <= 31 && month >= 1 && month <= 12 && year >= 1900) {
            // Проверка на високосный год и количество дней в месяце может быть добавлена здесь
            return MYDATE(day,month,year);
        } else {
            cout << "Ошибка: Некорректная дата. Пожалуйста, введите дату в допустимом диапазоне.\n";
        }
    }
}

// Функция для получения корректного имени
string getCorName() {
    string name;
    while (true) {
        cout << "Введите имя: ";
        getline(cin >> ws, name); // Читаем строку с учетом пробелов

        if (!isValidString(name)) {
            cout << "Ошибка: Имя должно содержать только буквы и цифры.\n";
        } else {
            return name;
        }
    }
}

// Функция для получения корректного логина
string getCorLogin() {
    string login;
    while (true) {
        cout << "Введите логин: ";
        getline(cin >> ws, login); // Читаем строку с учетом пробелов

        if (!isValidString(login)) {
            cout << "Ошибка: Логин должен содержать только буквы и цифры.\n";
        } else {
            return login;
        }
    }
}

// Функция для получения корректного пароля
string getCorPassword() {
    string password;
    while (true) {
        cout << "Введите пароль (до 20 символов, буквы и цифры): ";
        getline(cin >> ws, password); // Читаем строку с учетом пробелов

        if (password.length() > 20) {
            cout << "Ошибка: Пароль должен содержать не более 20 символов.\n";
        } else if (!isValidString(password)) {
            cout << "Ошибка: Пароль должен содержать только буквы и цифры.\n";
        } else if (!hasLettersAndDigits(password)) {
            cout << "Ошибка: Пароль должен содержать и буквы, и цифры.\n";
        } else {
            return password;
        }
    }
}

// Функция для получения корректного числа
int getCorNum() {
    int num;
    while (true) {
        cin >> num;

        if (cin.fail()) {
            cout << "Ошибка: Некорректный ввод. Пожалуйста, введите число.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return num;
        }
    }
}

// Функция для получения корректного числа в диапазоне
int getCorNumDiaposone(int start, int end) {
    int num;
    while (true) {
        num = getCorNum(); // Используем getCorNum для получения числа

        if (num >= start && num <= end) {
            return num;
        } else {
            cout << "Ошибка: Число должно быть в диапазоне от " << start << " до " << end << ".\n";
        }
    }
}