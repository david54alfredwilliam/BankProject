#pragma once 
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h" 
#include <vector>
#include <fstream> 

using namespace std ; 
class clsBankClient : public clsPerson 
{
private :
   enum enMode { EmptyMode = 0 , UpdateMode = 1 , AddNewMode = 2} ;
   enMode _Mode ;

   string _AccountNumber ;
   string _PinCode ;
   float _AccountBalance ;
   bool _MarkedForDelete = false ; 

   static clsBankClient _ConvertLineToClientObject ( string Line , string Seperator = "#//#" ) 
   {
     vector <string> vClientData ;
     vClientData = clsString::Split(Line , Seperator) ;

     return clsBankClient ( enMode::UpdateMode , vClientData[0] , vClientData[1] , vClientData[2] , vClientData[3] , vClientData[4] , vClientData[5] , stod(vClientData[6]) ) ;
   }

   static vector <clsBankClient> _LoadClientsDataFromFile () 
   {
     vector <clsBankClient> vClients ;

     fstream MyFile ;
     MyFile.open("Clients.txt" , ios::in ) ;

     if (MyFile.is_open()) 
     {
        string Line ;
        while (getline(MyFile,Line)) 
        {
            clsBankClient Client = _ConvertLineToClientObject(Line) ;
            vClients.push_back(Client) ;
        }
        MyFile.close() ;
     }
     return vClients; 
   }

   static string _ConvertClientObjectToLine(clsBankClient Client , string Seperator = "#//#") 
   {
    string stClientRecord = "" ;
    stClientRecord += Client.FirstName + Seperator ;
    stClientRecord += Client.LastName + Seperator ;
    stClientRecord += Client.Email + Seperator ;
    stClientRecord += Client.Phone + Seperator ;
    stClientRecord += Client.AccountNumber() +  Seperator ;
    stClientRecord += Client.PinCode + Seperator ;
    stClientRecord += to_string(Client.AccountBalance) ;
    
    return stClientRecord ;
   }

   static void _SaveClientsDataToFile(vector <clsBankClient> vClients) 
   {
     fstream MyFile;
     MyFile.open("Clients.txt" , ios::out ) ;
     string DataLine ; 
     if (MyFile.is_open()) 
     {
        for (clsBankClient& C : vClients) 
        {
            if (C.MarkedForDelete() == false )
            {
              DataLine = _ConvertClientObjectToLine(C) ;
              MyFile << DataLine << endl ; 
            }
             
        }
        MyFile.close() ;
     }
   }
    
    void _Update() 
    {
       vector <clsBankClient> _vClients ;
       _vClients = _LoadClientsDataFromFile() ;

       for (clsBankClient& c : _vClients) 
       {
           if(c.AccountNumber() == AccountNumber() )
           {
             c = *this ;
             break; 
           }
       }
       _SaveClientsDataToFile(_vClients) ; 
    }

    void _AddNew() 
    {
        _AddDataLineToFile(_ConvertClientObjectToLine(*this)) ;
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile ;
        MyFile.open("Clients.txt" , ios::out | ios::app) ;

        if (MyFile.is_open()) 
        {
            MyFile << stDataLine << endl ;
            MyFile.close() ;
        }
    }
   static clsBankClient _GetEmptyClientObject() 
   {
     return clsBankClient(enMode::EmptyMode , "" , "" , "" , "" ,"" ,"" , 0 ) ;
   }

public : 
    clsBankClient ( enMode Mode , string FirstName , string LastName , string Email , string Phone , string AccountNumber , string PinCode , float AccountBalance ) : clsPerson ( FirstName , LastName ,Email , Phone)
    {
       _Mode = Mode ;
       _AccountNumber = AccountNumber ;
       _PinCode = PinCode ;
       _AccountBalance = AccountBalance ;
    }

    bool IsEmpty () 
    {
        return (_Mode == enMode::EmptyMode) ;
    }

    string AccountNumber () 
    {
        return _AccountNumber ;
    }

    void SetPinCode ( string PinCode ) 
    {
      _PinCode = PinCode ;
    }
    
    string GetPinCode ()
    {
        return _PinCode ;
    }
    __declspec(property(get = GetPinCode , put = SetPinCode)) string PinCode ;

    void SetAccountBalance ( float AccountBalance ) 
    {
       _AccountBalance = AccountBalance ;
    }
    float GetAccountBalance () 
    {
       return _AccountBalance ;
    }
    __declspec(property(get = GetAccountBalance , put = SetAccountBalance)) float AccountBalance ;

    bool MarkedForDelete () 
    {
        return _MarkedForDelete ; 
    }
    /*void Print() 
    {
        cout << "\nClient Card :" ;
        cout << "\n________________________" ;
        cout << "\nFirstName : " << FirstName ; 
        cout << "\nLastName  : " << LastName ;
        cout << "\nFull Name : " << FullName() ;
        cout << "\nEmail     : " << Email ;
        cout << "\nPhone     : " << Phone ;
        cout << "\nAcc.NUmber: " << _AccountNumber;
        cout << "\nPassword  : " << _PinCode ;
        cout << "\nBalance   : " << _AccountBalance;
        cout << "\n________________________" ;
    }*/

    static clsBankClient Find ( string AccountNumber ) 
    {
        fstream MyFile ;
        MyFile.open("Clients.txt" , ios::in ) ;

        if (MyFile.is_open()) 
        {
            string Line ;
            while (getline(MyFile,Line)) 
            {
                clsBankClient Client = _ConvertLineToClientObject(Line) ;
                if (Client.AccountNumber() == AccountNumber) 
                {
                    MyFile.close() ;
                    return Client ; 
                }
            }
            MyFile.close() ;
        }
       return _GetEmptyClientObject() ; 
    }

    static clsBankClient Find ( string AccountNumber , string PinCode ) 
    {
        fstream MyFile ;
        MyFile.open("Clients.txt" , ios::in ) ;

        if ( MyFile.is_open()) 
        {
            string Line ;
            while (getline(MyFile,Line)) 
            {
                clsBankClient Client = _ConvertLineToClientObject(Line) ;
                if(Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) 
                {
                   MyFile.close() ;
                   return Client ; 
                }
            }
            MyFile.close() ;
        }
        return _GetEmptyClientObject() ; 
    }

    bool Delete () 
    {
        vector <clsBankClient> _vClients ;
        _vClients = _LoadClientsDataFromFile() ;

        for (clsBankClient& C : _vClients) 
        {
            if ( C.AccountNumber() == _AccountNumber ) 
            {
                _MarkedForDelete = true ; 
                break ; 
            }
        }
        _SaveClientsDataToFile(_vClients) ;
        *this = _GetEmptyClientObject() ;
        return true ; 
    }
    enum enSaveResults {svFailedEmptyObject = 0 , svSucceeded = 1  , svFaildAccountNumberExists = 2} ;

    enSaveResults Save() 
    {
       switch (_Mode) 
       {
        case enMode::EmptyMode:
        {
            return enSaveResults::svFailedEmptyObject;
        }
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
            break ; 
        }
        case enMode::AddNewMode:
        {
            if (clsBankClient::IsClientExist(_AccountNumber)) 
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else 
            {
                _AddNew() ;
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
            break ;
        }
       }
    }
    
    static bool IsClientExist ( string AccountNumber)
    {
        clsBankClient Client = clsBankClient::Find(AccountNumber) ;
        return (!Client.IsEmpty()) ; 
    } 

    static clsBankClient GetAddNewClientObject (string AccountNumber )  
    {
        return clsBankClient (enMode::AddNewMode , "" , "" , "" , "" , AccountNumber , "" , 0) ;
    }
    static vector <clsBankClient> GetClientsList() 
    {
        return  _LoadClientsDataFromFile() ;
    }
    void Deposit(double Amount) 
    {
       _AccountBalance += Amount ;
       Save();
    }
    bool Withdraw(double Amount) 
    {
        if ( Amount > _AccountBalance) 
        {
           return false ;
        }
        else {
          _AccountBalance -= Amount;
          Save();
        }    
    }
    static double GetTotalBalances ()
    {
        vector <clsBankClient> vClients = _LoadClientsDataFromFile() ;
        double TotalBalances = 0 ;
        for (clsBankClient Client : vClients) 
        {
            TotalBalances += Client.AccountBalance ;
        }
        return TotalBalances ;
    }
} ;