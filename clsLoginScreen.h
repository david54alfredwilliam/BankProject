#pragma once 
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"

class clsLoginScreen:protected clsScreen 
{
private:
   static bool _Login()
   {
     bool LoginFaild = false;
     string UserName , Password ;
     do 
     {
        cout << "Enter UserName ? ";
        cin >> UserName;

        cout << "Enter Password ? ";
        cin >> Password;

        CurrentUser = clsUser::Find(UserName,Password);
        LoginFaild = CurrentUser.IsEmpty();
     }while(LoginFaild);

     clsMainScreen::ShowMainMenue();
     return true;
   }
public:
   static bool ShowLoginScreen()
   {
      system("cls");
      _DrawScreenHeader("\t    Login Screen");
      return _Login();
   }
};