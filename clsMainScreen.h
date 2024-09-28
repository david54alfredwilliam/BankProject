#pragma once 
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsers.h"
#include "Global.h"
#include "clsLoginScreen.h"
#include <iomanip>

using namespace std ;

class clsMainScreen:protected clsScreen 
{
private:
    enum enMainMenueOptions{
       eListClients = 1 , eAddNewClient = 2 , eDeleteClient = 3 , eUpdateClient = 4 , eFindClient = 5 , eShowTransactionsMenue = 6 ,
       eManageUsers = 7 , eExist = 8 
    };

    static short _ReadMainMenueOption() 
    {
        cout << setw(37) << left << "" << "Choose What do you want to do ? [1 to 8] ? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1,8,"Enter Number Between 1 to 8? ") ;
        return Choice ; 
    }
    static void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tpress any key to go back to main menue ..\n";
        system("pause>0");
        ShowMainMenue();

    }
    static void _ShowAllClientsScreen() 
    {
        clsClientListScreen::ShowClientsList();
    }
    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }
    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }
    static void _ShowUpdateClientScreen() 
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }
    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }
    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsMenue();
    }
    static void _ShowManageUsresMenue()
    {
        clsManageUsersScreen::ShowManageUsersMenue();
    }
    static void _Logout()
    {
        CurrentUser = clsUser::Find("","");
    }

    static void _PerformMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption) 
        {
            case enMainMenueOptions::eListClients:
            {
                system("cls");
                _ShowAllClientsScreen();
                _GoBackToMainMenue();
                break ;
            }
            case enMainMenueOptions::eAddNewClient:
            {
                system("cls");
                _ShowAddNewClientsScreen();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eDeleteClient:
            {
                system("cls");
                _ShowDeleteClientScreen();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eUpdateClient:
            {
                system("cls");
                _ShowUpdateClientScreen();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eFindClient:
            {
                system("cls");
                _ShowFindClientScreen();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eShowTransactionsMenue:
            {
                system("cls") ;
                _ShowTransactionsMenue();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eManageUsers:
            {
                system("cls");
                _ShowManageUsresMenue();
                _GoBackToMainMenue();
                break;
            }
            case enMainMenueOptions::eExist:
            {
                system("cls");
                _Logout();
                break;
            }
        }
    }
public :
 static void ShowMainMenue() 
 {
    system("cls") ;
    _DrawScreenHeader("\t\tMain Screen") ;

    cout << setw(37) << left << "" << "==========================================================\n";
    cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
    cout << setw(37) << left << "" << "==========================================================\n";
    cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
    cout << setw(37) << left << "" << "\t[2] Add New Client.\n" ;
    cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
    cout << setw(37) << left << "" << "\t[4] Update Client.\n";
    cout << setw(37) << left << "" << "\t[5] Find Client.\n";
    cout << setw(37) << left << "" << "\t[6] Transactions.\n";
    cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
    cout << setw(37) << left << "" << "\t[8] Logout.\n" ;

    _PerformMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
 }
};