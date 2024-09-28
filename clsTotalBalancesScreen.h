#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>

class clsTotalBalancesScreen:protected clsScreen 
{
private:
  static void PrintClientRecordBalance(clsBankClient Client)
  {
    cout << setw(25) << left << "" << "| " << setw(15) << left << Client.AccountNumber() ;
    cout << "| " << setw(40) << left << Client.FullName();
    cout << "| " << setw(12) << left << Client.AccountBalance;
  }
public:
  static void ShowTotalBalances()
  {
    vector <clsBankClient> vClients = clsBankClient::GetClientsList();

    string Title = "\t Balances List Screen";
    string SubTitle = "\t   (" + to_string(vClients.size()) + ") Client(s)";

    _DrawScreenHeader(Title,SubTitle);

    cout << setw(25) << left << "" << "\n\t\t_____________________________________________________";
    cout <<"___________________________\n" <<endl ;

    cout << setw(25) << left << "" << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << setw(25) << left << "" << "\t\t________________________________________________________";
    cout << "__________________________\n" << endl ;

    double TotalBalances = clsBankClient::GetTotalBalances() ;

    if (vClients.size() == 0) 
    {
        cout << "\t\t\tNo Clients Available " ;
    }
    else 
    {
        for (clsBankClient Client : vClients) 
        {
            PrintClientRecordBalance(Client) ;
            cout << endl ;
        }
    }
    cout << setw(25) << left << "" << "\n\t\t_____________________________________________________";
    cout << "__________________________\n" << endl ;

    cout << setw(8) << left << "" << "\t\t\t\t\t\t\t      Total Balances = " << TotalBalances << endl ;
  }
};