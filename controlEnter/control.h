#ifndef CONTROL_H
#define CONTROL_H

#include "../date/date.h"

#include <string>
#include <limits> // Для numeric_limits
#include <cctype>  // Для isalnum, isdigit, isalpha

using namespace std;

MYDATE getCorDate();
string getCorName();
string getCorPassword();
string getCorLogin();
int getCorNum();
int getCorNumDiaposone(int start, int end);

#endif // CONTROL_H