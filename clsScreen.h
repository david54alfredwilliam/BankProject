#pragma once 
#include <iostream>

using namespace std ;
class clsScreen 
{
protected :
   static void _DrawScreenHeader ( string Title, string SubTitle="")
   {
     cout << "\t\t\t\t\t___________________________________________";
     cout << "\n\n\t\t\t\t\t  " << Title;
     if (SubTitle != "") 
     {
        cout << "\n\t\t\t\t\t  " << SubTitle ;
     }
     cout << "\n_____________________________________________________\n\n";
   }
   static bool CheckAccessRights(clsUser::enPermissions  Permission)
   {
      if(!CurrentUser.CheckAccessPermission(Permission)) 
      {
         cout << "\t\t\t\t\t___________________________________";
         cout << "\n\n\t\t\t\t\t   Access Denied! Contact Your Admin.";
         cout << "\n\t\t\t\t\t________________________________________\n\n";
         return false;
      }
      else
      {
         return true;
      }
   }
};