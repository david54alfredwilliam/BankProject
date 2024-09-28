#pragma once 
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include <iomanip>

class clsAddNewClientScreen:protected clsScreen
{
private:
   static void _ReadClientInfo(clsBankClient& Client)
   {
    cout << "\nEnter First Name :";
    Client.FirstName = clsInputValidate::ReadString();

    cout << "\nEnter Last Name :";
    Client.LastName = clsInputValidate::ReadString();

    cout << "\nEnter Email :";
    Client.Email = clsInputValidate::ReadString();

    cout << "\nEnter Phone :";
    Client.Phone = clsInputValidate::ReadString();

    cout << "\nEnter PinCode :";
    Client.PinCode = clsInputValidate::ReadString();

    cout << "\nEnter Account Balance :";
    Client.AccountBalance = clsInputValidate::ReadFloatNumber();
   }

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
   static void ShowAddNewClientScreen ()
   {

    if(!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
    {
      return;
    }
    _DrawScreenHeader("\t   Add New Screen");
    string AccountNumber = "" ;

    cout << "\nEnter The Account Number : ";
    AccountNumber = clsInputValidate::ReadString() ;

    while (clsBankClient::IsClientExist(AccountNumber)) 
    {
      cout << "\nAccount Number is Already Exist , choose anthor one : " ;
      AccountNumber = clsInputValidate::ReadString() ;
    }

    clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber) ;
    _ReadClientInfo(NewClient) ;

     clsBankClient::enSaveResults SaveResult ;
     SaveResult = NewClient.Save();

     switch(SaveResult)
     {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Added Succssesfuly\n";
            _PrintClient(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFailedEmptyObject:
        {
            cout << "\nError was not saved because it is empty";
            break;
        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExists:
        {
            cout << "\nError account was not save because it is exist";
            break;
        }
     }
   }
};
