#pragma once 
#include <iostream> 
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

class clsDepositScreen:protected clsScreen
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
  static void ShowDepositScreen()
  {
    _DrawScreenHeader("\t   Deposit Screen");
    string AccountNumber = _ReadAccountNumber();

    while(!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nclient was not found enter another one \n";
        AccountNumber = _ReadAccountNumber();
    }

    clsBankClient Client1 = clsBankClient::Find(AccountNumber) ;
    _PrintClient(Client1) ;

    double Amount = 0 ;
    cout << "\nEnter deposit Amount ? ";
    Amount = clsInputValidate::ReadDblNumber() ;

    cout << "\nAre you sure want to deposit ? ";
    char Answer = 'n' ;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y') 
    {
        Client1.Deposit(Amount);
        cout << "\nAmount Deposited Successfuly.\n";
        cout << "\nNew Balance is : " << Client1.AccountBalance;
    }
    else 
    {
       cout << "\nOperation was Cancelled\n";
    }
  }
};
