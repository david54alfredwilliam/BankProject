#pragma once 
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsPerson.h"

class clsUpdateClientScreen:protected clsScreen
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
  static void ShowUpdateClientScreen()
  {
    if(!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
    {
      return;
    }
    _DrawScreenHeader("\tUpdate Client Screen");
    string AccountNumber ="";

    cout << "\nEnter Account Number : ";
    AccountNumber = clsInputValidate::ReadString();

    while(!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount Number was not found enter another one : ";
        AccountNumber = clsInputValidate::ReadString();
    }
    clsBankClient Client1 = clsBankClient::Find(AccountNumber);
    _PrintClient(Client1) ;

    cout << "Are you sure want to update this client (y/n) : ";
    char Answer = 'n';
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        cout << "\n\nUpdate Client Info: ";
        cout << "\n_______________________\n";

        _ReadClientInfo(Client1);
        clsBankClient::enSaveResults SaveResult ;
        SaveResult = Client1.Save();

        switch(SaveResult)
        {
            case clsBankClient::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Updated Successfuly \n";
                _PrintClient(Client1);
                break;
            }
            case clsBankClient::enSaveResults::svFailedEmptyObject:
            {
                cout << "\nError account was not saved becasue its empty";
                break;
            }
        }
    }
  }
};