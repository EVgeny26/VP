#include <iostream>
#include <string>

using namespace std;

class Human{
    private:
        struct DATABIRTH{
            unsigned short year;
            unsigned short day;
            unsigned short month;
        };
        enum GENDER{
            main, femail
        };
        string name{};
        int age;
        DATABIRTH birth{};
        GENDER gender;

        string login{};
        string password{};

    public:
        Human(string name, int age, DATABIRTH birth, GENDER gender, string login, string password);
        ~Human();
        void set_name(string name);
        void set_age(int age);
        void set_login(string login);
        void set_password(string password);

};

