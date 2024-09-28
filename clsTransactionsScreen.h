#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include <iomanip>

class clsTransactionsScreen:protected clsScreen 
{
private:
  enum enTransactionsMenueOptions {
    eDeposit = 1 , eWithdraw = 2 , eShowTotalBalances = 3 , eShowMainMenue = 4 
  };
  static short ReadTransactionsMenueOption() 
  {
    cout << setw(37) << left << "" << "Choose what you want to do ? [1 to 4] ? ";
    short Choice = clsInputValidate::ReadShortNumberBetween(1,4,"Enter number between 1 to 4 ? ");
    return Choice ;
  }
  static void _ShowDepositScreen() 
  {
    clsDepositScreen::ShowDepositScreen();
  }
  static void _ShowWithdrawScreen()
  {
    clsWithdrawScreen::ShowWithdrawScreen();
  }
  static void _showTotalBalancesScreen()
  {
    clsTotalBalancesScreen::ShowTotalBalances();
  }
  static void _GoBackToTransactionsMenue()
  {
    cout << "\n\npress any key to go back to transactions menue...";
    system("pause>0");
    ShowTransactionsMenue();
  }
  static void _PerformTransactionsMenueOptions(enTransactionsMenueOptions TransactionsMenueOption)
  {
    switch(TransactionsMenueOption) 
    {
        case enTransactionsMenueOptions::eDeposit:
        {
            system("cls") ;
            _ShowDepositScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case enTransactionsMenueOptions::eWithdraw:
        {
            system("cls") ;
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenue();
            break; 
        }
        case enTransactionsMenueOptions::eShowTotalBalances:
        {
            system("cls");
            _showTotalBalancesScreen();
            _GoBackToTransactionsMenue();
            break;
        }
        case enTransactionsMenueOptions::eShowMainMenue:
        {
           cout << "\n no thing";
        }
    }
  }
public:
   static void ShowTransactionsMenue()
   {
       if(!CheckAccessRights(clsUser::enPermissions::pTransactions))
       {
          return;
       }
      system("cls") ;
      _DrawScreenHeader("\t  Transactions Screen") ;

      cout << setw(37) << left << "" << "===========================================================\n";
      cout << setw(37) << left << "" << "\t\t   Transactions Menue\n";
      cout << setw(37) << left << "" << "===========================================================\n";
      cout << setw(37) << left << "" << "\t[1] Deposit.\n";
      cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
      cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
      cout << setw(37) << left << "" << "\t[4] Main Menue.\n";
      cout << setw(37) << left << "" << "============================================================\n";

      _PerformTransactionsMenueOptions((enTransactionsMenueOptions)ReadTransactionsMenueOption());

   }
};
