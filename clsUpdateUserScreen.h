#pragma once 
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsPerson.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen :protected clsScreen
{
private:
    static void _ReadUserInfo(clsUser User)
   {
     cout << "\nEnter FirstName: ";
     User.FirstName = clsInputValidate::ReadString();

     cout << "\nEnter LastName: ";
     User.LastName = clsInputValidate::ReadString();

     cout << "\nEnter Email: ";
     User.Email = clsInputValidate::ReadString();

     cout << "\nEnter Phone: ";
     User.Phone = clsInputValidate::ReadString();

     cout << "\nEnter Password: ";
     User.Password = clsInputValidate::ReadString();

     cout << "\nEnter Permission: ";
     User.Permissions= _ReadPermissionsToSet();
   }
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
   static int _ReadPermissionsToSet()
   {
     int Permissions = 0 ;
     char Answer = 'n' ;

     cout << "\nDo you want to give full access? y/n?";
     cin>> Answer;
     if(Answer == 'y' || Answer == 'Y') 
     {
        return -1 ;
     }
     cout << "\nDo you want to give access to : \n";
     cout << "\nShow Client List? y/n ";
     cin >> Answer ;
     if (Answer == 'y' || Answer == 'Y')
     {
        Permissions += clsUser::enPermissions::pListClients;
     }

     cout << "\nAdd New Client? y/n ";
     cin>> Answer ;
     if (Answer == 'y' || Answer == 'Y') 
     {
        Permissions += clsUser::enPermissions::pAddNewClient;
     }

     cout << "\nDelete Client ? y/n ";
     cin >> Answer;
     if(Answer == 'y' || Answer == 'Y')
     {
        Permissions += clsUser::enPermissions::pDeleteClient;
     }

     cout << "\nUpdate Client ? y/n ";
     cin >> Answer;
     if (Answer == 'y' || Answer == 'Y')
     {
        Permissions += clsUser::enPermissions::pUpdateClients;
     }

     cout << "\nFind Client? y/n ";
     cin >> Answer;
     if(Answer == 'y' || Answer == 'Y') 
     {
        Permissions += clsUser::enPermissions::pFindClient;
     }

     cout << "\nTransactiona? y/n ";
     cin>> Answer;
     if (Answer == 'y' || Answer == 'Y')
     {
        Permissions += clsUser::enPermissions::pTransactions;
     }

     cout << "\nTransactions? y/n ";
     cin >> Answer;
     if(Answer == 'y' || Answer == 'Y')
     {
        Permissions += clsUser::enPermissions::pTransactions;
     }

     cout << "\nManage Users? y/n ";
     cin >> Answer;
     if (Answer == 'y' || Answer == 'Y')
     {
        Permissions += clsUser::enPermissions::pManageUsers;
     }

     return Permissions;
   }
public:
   static void ShowUpdateUserScreen()
   {
      _DrawScreenHeader("\tUpdate User Screen");

      string UserName = "";

      cout << "\nplease enter user name : ";
      UserName = clsInputValidate::ReadString();

      while(!clsUser::IsUserExist(UserName))
      {
         cout << "\nUser  name is already used , choose another one : ";
         UserName = clsInputValidate::ReadString();
      }

      clsUser User1 = clsUser::Find(UserName);
      _PrintUser(User1);

      cout << "\are you sure want to update this user : ";
      char Answer = 'n';
      cin >> Answer;

      if (Answer == 'y' || Answer == 'Y')
      {
         cout << "\n\nUpdate User Info:";
         cout << "\n_____________________\n";

         _ReadUserInfo(User1);

         clsUser::enSaveResults SaveResult ;
         SaveResult = User1.Save();

         switch (SaveResult)
         {
            case clsUser::enSaveResults::svSucceeded:
            {
               cout << "\nUser upadated successfuly\n";
               _PrintUser(User1);
               break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
               cout << "\nError was not not saved becasue its empty";
               break;
            }
         }
      }

   }
};