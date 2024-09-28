#pragma once 
#include <iostream>
#include "clsPerson.h"
#include "clsString.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std ;
class clsUser:public clsPerson 
{
private:
 enum enMode {EmptyMode = 0 , UpdateMode = 1, AddNewMode};
 enMode _Mode;
 string _UserName;
 string _Password;
 int _Permissions;
 bool _MarkedForDelete = false ;

 static clsUser _ConvertLineToUserObject ( string Line , string Seperator = "#//#")
 {
    vector <string> vUserData = clsString::Split(Line,Seperator);
    return clsUser(enMode::UpdateMode,vUserData[0],vUserData[1],vUserData[2],vUserData[3],vUserData[4],vUserData[5],stoi(vUserData[6]));
 }

 static string _ConvertUserObjectToLine(clsUser User , string Seperator = "#//#")
 {
    string UserRecrod = "";

    UserRecrod += User.FirstName + Seperator;
    UserRecrod += User.LastName + Seperator;
    UserRecrod += User.Email + Seperator;
    UserRecrod += User.Phone + Seperator;
    UserRecrod += User.UserName + Seperator;
    UserRecrod += User.Password + Seperator;
    UserRecrod += to_string(User.Permissions);

    return UserRecrod;
 }
 static vector <clsUser> _LoadUsersDataFromFile()
 {
    vector <clsUser> vUsers ;
    fstream MyFile;
    MyFile.open("Users.txt",ios::in) ;

    if (MyFile.is_open())
    {
        string Line ;
        while(getline(MyFile,Line))
        {
            clsUser User = _ConvertLineToUserObject(Line);
            vUsers.push_back(User);
        }
        MyFile.close();
    }
    return vUsers;
 }
 static void _SaveUsersDataToFile(vector <clsUser> vUsers)
 {
    fstream MyFile;
    MyFile.open("Users.txt", ios::out | ios::app);
    string DataLine;
    if (MyFile.is_open()) 
    {
       for(clsUser U : vUsers)
       {
          DataLine = _ConvertUserObjectToLine(U);
          MyFile << DataLine << endl ;
       }
    }
    MyFile.close() ;
 }
 void _Update() 
 {
    vector <clsUser> _vUsers = _LoadUsersDataFromFile();

    for (clsUser U : _vUsers) 
    {
        if (U.UserName == UserName) 
        {
            U = *this ;
            break;
        }
    }
    _SaveUsersDataToFile(_vUsers);
 }
 void _AddNew() 
 {
    _AddDataLineToFile(_ConvertUserObjectToLine(*this)) ;
 }
 void _AddDataLineToFile(string stDataLine)
 {
    fstream MyFile;
    MyFile.open("Users.txt",ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl ;
        MyFile.close();
    }
 }
 static clsUser _GetEmptyUserObject() 
 {
    return clsUser(enMode::EmptyMode,"","","","","","",0);
 }
public :
   enum enPermissions {
     eAll = -1 , pListClients = 1 , pAddNewClient = 2 , pDeleteClient = 4 ,
     pUpdateClients = 8 , pFindClient = 16 , pTransactions = 32 , pManageUsers = 64 
  };
  clsUser(enMode Mode , string FirstName , string LastName , string Email , string Phone , string Username , string Password , int Permissions ) :
  clsPerson (FirstName,LastName,Email,Phone)
  {
    _Mode = Mode ;
    _UserName = Username;
    _Password = Password;
    _Permissions = Permissions ;
  }

  bool IsEmpty() 
  {
    return (_Mode == EmptyMode);
  }
  bool MarkedForDelete()
  {
    return _MarkedForDelete;
  }
  string GetUserName()
  {
    return _UserName;
  }
  void SetUserName(string UserName) 
  {
    _UserName = UserName;
  }
  __declspec(property(get = GetUserName , put = SetUserName)) string UserName ;
  void SetPassword (string Password) 
  {
    _Password = Password ;
  }
  string GetPassword () 
  {
    return _Password ;
  }
  __declspec(property(get = GetPassword , put = SetPassword)) string Password ;
  int GetPermissions ()
  {
    return _Permissions;
  }
  void SetPermissions (int Permissions)
  {
    _Permissions = Permissions ;
  }
  __declspec(property(get = GetPermissions , put = SetPermissions)) int Permissions ;

  static clsUser Find (string UserName )
  {
    fstream MyFile ;
    MyFile.open("Users.txt" , ios::in) ;
    
    if (MyFile.is_open())
    {
        string Line ;
        while(getline(MyFile,Line)) 
        {
            clsUser User = _ConvertLineToUserObject(Line);
            if (User.UserName==UserName) 
            {
                MyFile.close();
                return User;
            }
        }
        MyFile.close();
    }
    return _GetEmptyUserObject() ;
  }
  static clsUser Find (string UserName , string Password)
  {
    fstream MyFile ;
    MyFile.open("Users.txt" , ios::in) ;
    
    if (MyFile.is_open())
    {
        string Line ;
        while(getline(MyFile,Line)) 
        {
            clsUser User = _ConvertLineToUserObject(Line);
            if (User.UserName==UserName && User.Password == Password) 
            {
                MyFile.close();
                return User;
            }
        }
        MyFile.close();
    }
    return _GetEmptyUserObject() ;
  }
  enum enSaveResults {svFaildEmptyObject=0 , svSucceeded = 1 , svFaildUserExists=2};

  enSaveResults Save() 
  {
    switch (_Mode) 
    {
        case enMode::EmptyMode:
        {
            if(IsEmpty()) 
            {
                return enSaveResults::svFaildEmptyObject;
            }
            break;
        }
        case enMode::UpdateMode:
        {
            _Update() ;
            return enSaveResults::svSucceeded;
            break;
        }
        case enMode::AddNewMode:
        {
            if (clsUser::IsUserExist(_UserName)) 
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
              _AddNew();
              _Mode = enMode::UpdateMode;
              return enSaveResults::svSucceeded;
            }
            break;
        }
    }
  }
  static bool IsUserExist(string UserName) 
  {
   clsUser User = clsUser::Find(UserName);
   return (!User.IsEmpty());
  }
  bool Delete() 
  {
    vector <clsUser> _vUsers ;
    _vUsers = _LoadUsersDataFromFile() ;

    for(clsUser& U : _vUsers) 
    {
      if (U.UserName== _UserName ) 
      {
        U._MarkedForDelete = true ;
        break;
      }
    }
    _SaveUsersDataToFile(_vUsers);
    *this = _GetEmptyUserObject();
    return true ;
  }
  static clsUser GetAddNewUser(string UserName)
  {
    return clsUser(enMode::AddNewMode, "","","","",UserName,"",0) ;
  }
  static vector <clsUser> GetUsersList()
  {
    return _LoadUsersDataFromFile();
  }

  bool CheckAccessPermission(enPermissions Permission)
  {
    if(this->Permissions == enPermissions::eAll) 
    {
      return true;
    }
    if((Permission & this->Permissions) == Permission)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
};