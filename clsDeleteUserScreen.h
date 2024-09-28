#pragma once 
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen: protected clsScreen
{
private:
   static void _PrintUser(clsUser User)
   {
    cout << "\nUser Card: ";
    cout << "\n_____________________";
    cout << "\nFirstName  : " << User.FirstName;
    cout << "\nLastName   : " << User.LastName;
    cout << "\nFull Name  : " << User.FullName();
    cout << "\nEmail      : " << User.Email;
    cout << "\nPhone      : " << User.Phone;
    cout << "\nUser Name  : " << User.UserName;
    cout << "\nPassword   : " << User.Password;
    cout << "\nPermissions: " << User.Permissions;
    cout << "\n_____________________\n";
   }
public:
  static void ShowDeleteUserScreen()
  {
    _DrawScreenHeader("\tDelete User Screen");

    string UserName = "" ;
    cout << "\nPlease enter username: ";
    UserName = clsInputValidate::ReadString();
    while(!clsUser::IsUserExist(UserName))
    {
        cout << "\nUser is not found , choose another one: ";
        UserName = clsInputValidate::ReadString();
    }

    clsUser User1 = clsUser::Find(UserName);
    _PrintUser(User1);

    cout << "\nAre you sure want to delete this user (y/n) ? ";
    char Answer = 'n' ;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        if (User1.Delete())
        {
            cout << "\nUser Deleted Successfuly\n";
            _PrintUser(User1);
        }
        else
        {
            cout << "\nError User was not Deleted\n";
        }
    }
  }
};