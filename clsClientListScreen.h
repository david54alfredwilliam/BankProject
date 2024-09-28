#pragma once 
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip> 

class clsClientListScreen:protected clsScreen 
{

private:
  static void PrintClientRecordLine(clsBankClient Client) 
  {
    cout << setw(8) << left << "" << "| "<< setw(15) << left << Client.AccountNumber() ;
    cout << "| " << setw(20) << left << Client.FullName();
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(20) << left << Client.Email;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(12) << left << Client.AccountBalance;
  }
public:
static void ShowClientsList ()
{
   if(!CheckAccessRights(clsUser::enPermissions::eAll))
   {
      return;
   }
   vector <clsBankClient> vClients = clsBankClient::GetClientsList() ;
   string Title = "\t Client List Screen";
   string SubTitle = "\t    (" + to_string(vClients.size()) + ") Client(s).";
   _DrawScreenHeader(Title,SubTitle) ;
   
   cout << "\n_________________________________________________________";
   cout << "____________________________________________\n"<<endl ;

   cout << setw(8) << left << "" <<"| " << left << setw(15) << "Account Number" ;
   cout << "| " << left << setw(20) << "Client Name" ;
   cout << "| " << left << setw(12) << "Phone" ;
   cout << "| " << left << setw(20) << "Email" ;
   cout << "| " << left << setw(10) << "Pin code";
   cout << "| " << left << setw(12) << "Balance";
   cout << setw(8) << left << "" <<"\n_________________________________________________________";
   cout << "____________________________________________\n" <<endl;

   if (vClients.size() == 0 ) {
      cout << "\t\t\tNo Clients Availabe in the system!" ;
   }else {
      for (clsBankClient Client : vClients) 
      {
         PrintClientRecordLine(Client) ;
         cout << endl ; 
      }
   cout << "\n_________________________________________________________";
   cout << "_____________________________________________\n" <<endl;
   }

}

};