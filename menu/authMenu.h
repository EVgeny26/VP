#ifndef AUTHMENU_H
#define AUTHMENU_H

#include "CMenu/CMenu.h"
#include "../users/admin.h"
#include "../users/user.h"
#include "../myclasses/logger.h"

// Объявление функции
CMenu* getUserMenu(User& user);
CMenu* getAdminMenu(Admin& admin);
CMenu* getAuthMenu();

#endif // AUTHMENU_H