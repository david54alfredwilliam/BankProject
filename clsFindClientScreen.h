#pragma once 
#include <iostream>
#include "clsPerson.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsFindClientScreen:protected clsScreen
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
  static void ShowFindClientScreen() 
  {
    if(!CheckAccessRights(clsUser::enPermissions::pFindClient))
    {
      return;
    }
    _DrawScreenHeader("\tFind Client Screen ");
    string AccountNumber = "";

    cout << "\nEnter the Account Number : ";
    AccountNumber = clsInputValidate::ReadString() ;

    while (!clsBankClient::IsClientExist(AccountNumber)) 
    {
        cout << "\nAccount Number was not found enter another one : ";
        AccountNumber = clsInputValidate::ReadString();
    }
    clsBankClient Client1 = clsBankClient::Find(AccountNumber);
    if(Client1.IsEmpty())
    {
        cout << "\nAccount was not Founded ";
    }else {
        cout << "\nAccount was Founded Successfuly ";
    }
    _PrintClient(Client1);
  } 
};