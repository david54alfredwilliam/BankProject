#pragma once 
#include <iostream> 
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUserListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include <iomanip>

using namespace std ;

class clsManageUsersScreen:protected clsScreen 
{
private:
 enum enManageUsersMenueOptions {
    eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
    eUpdateUser = 4, eFindUser = 5 , eMainMenue = 6 
 };
 static short ReadManageUsersMenueOption ()
 {
    cout << setw(37) << left << "" << "Choose What do you want to do ? [1 to 6]";
    short Choice = clsInputValidate::ReadShortNumberBetween(1,6,"Enter Number between 1 to 6 ?");
    return Choice ;
 }
 static void _GoBackToManageUsersMenue() 
 {
    cout << "\nPress any key to manage users Menue...";
    system("pause>0");
    ShowManageUsersMenue() ;
 }
 static void _ShowListUsersScreen() 
 {
    clsListUsersScreen::ShowUserList();
 }
 static void _ShowAddNewUserScreen() 
 {
    clsAddNewClientScreen::ShowAddNewClientScreen();
 }
 static void _ShowDeleteUserScreen() 
 {
    clsDeleteUserScreen::ShowDeleteUserScreen();
 }
 static void _ShowUpdateUserScreen() 
 {
    cout << "\nwill";
 }
 static void _ShowFindUserScreen() 
 {
    cout << "\nwill";
 }
 static void _PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenusOption)
 {
    switch(ManageUsersMenusOption) 
    {
        case enManageUsersMenueOptions::eListUsers:
        {
            system("cls") ;
            _ShowListUsersScreen();
            _GoBackToManageUsersMenue();
            break ;
        }
        case enManageUsersMenueOptions::eAddNewUser:
        {
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }
        case enManageUsersMenueOptions::eDeleteUser:
        {
            system("cls") ;
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }
        case enManageUsersMenueOptions::eUpdateUser:
        {
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }
        case enManageUsersMenueOptions::eFindUser:
        {
            system("cls");
            _ShowFindUserScreen();
            _GoBackToManageUsersMenue();
            break;
        }
        case enManageUsersMenueOptions::eMainMenue:
        {
            //nothing;
        }
    }
 }
public:
 
  static void ShowManageUsersMenue()
  {
     if(!CheckAccessRights(clsUser::enPermissions::pManageUsers))
     {
       return;
     }
     system("cls");
     _DrawScreenHeader("\t Manage Users Meneu");

     cout << setw(37) << left << "" << "=========================================\n";
     cout << setw(37) << left << "" << "\t\t   Manage Users Menue\n";
     cout << setw(37) << left << "" << "=========================================\n";
     cout << setw(37) << left << "" << "\t[1] List Users.\n";
     cout << setw(37) << left << "" << "\t[2] Add New User.\n";
     cout << setw(37) << left << "" << "\t[3] Delete User.\n";
     cout << setw(37) << left << "" << "\t[4] Update User.\n";
     cout << setw(37) << left << "" << "\t[5] Find User.\n";
     cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
     cout << setw(37) << left << "" << "==========================================\n";

     _PerformManageUsersMenueOption((enManageUsersMenueOptions)ReadManageUsersMenueOption());
  }
};
