#pragma once 
#include <iostream> 
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsWithdrawScreen:protected clsScreen
{
private:
   static void _PrintClient(clsBankClient Client) 
   {
    cout << "\nClient Card:";
    cout << "\n____________________";
    cout << "\nFirst Name   : " << Client.FirstName;
    cout << "\nLast Name    : " << Client.LastName;
    cout << "\nFull Name    : " << Client.FullName();
    cout << "\nEmail        : " << Client.Email;
    cout << "\nPhone        : " << Client.Phone ;
    cout << "\nAcc.NUmber   : " << Client.AccountNumber();
    cout << "\nPassword     : " << Client.PinCode ;
    cout << "\nBalance      : " << Client.AccountBalance;
    cout << "\n____________________" ;
   }
   static string _ReadAccountNumber()
   {
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber ? ";
    cin >> AccountNumber;
    return AccountNumber;
   }
public:
  static void ShowWithdrawScreen()
  {
    _DrawScreenHeader("\t   Withdraw Screen");
    string AccountNumber = _ReadAccountNumber();

    while(!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nclient was not found enter another one \n";
        AccountNumber = _ReadAccountNumber();
    }

    clsBankClient Client1 = clsBankClient::Find(AccountNumber) ;
    _PrintClient(Client1) ;

    double Amount = 0;
    cout << "\nEnter withdraw amount : ";
    Amount = clsInputValidate::ReadDblNumber();

    cout << "\nAre You sure want to perform this transaction? " ;
    char Answer ='n';
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        if(Client1.Withdraw(Amount))
        {
            cout << "\nAmount withdrew Successfully.\n";
            cout << "\nNew Balance is : " << Client1.AccountBalance;
        }
        else 
        {
            cout << "\nCannot withdraw insuuficent balance \n";
            cout << "\nAmount to withdraw is : " << Amount ;
            cout << "\nYour Balance is : " << Client1.AccountBalance ;
        }
    }
    else 
    {
      cout << "\noperation was cancelled \n" ;
    }
  }
};