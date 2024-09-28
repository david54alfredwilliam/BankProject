#pragma once 
#include <iostream>
#include "clsPerson.h"
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen:protected clsScreen
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
public:
  static void ShowDeleteClientScreen() 
  {
    if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
    {
      return;
    }
    _DrawScreenHeader("\tDelete Client Screen") ;
    string AccountNumber = "";

    cout << "\nPlease enter Account Number : ";
    AccountNumber = clsInputValidate::ReadString() ;
    while(!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount Number is Not found enter another one : ";
        AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient Client1 = clsBankClient::Find(AccountNumber);
    _PrintClient(Client1);

    cout << "\nAre you sure you want to delete this client (y/n)? ";
    char Answer = 'n' ;
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        if (Client1.Delete()) 
        {
            cout << "\nClient was Deleted successfully :";
            _PrintClient(Client1) ;
        }
        else {
            cout << "\nError Client was Not Deleted \n";
        }
    }
  }
};