//
// Created by Anirban-Rahi on 10/25/2024.
//

#include "Authentication.h"
using namespace std;
#include <vector>
#include<iostream>
#include <fstream>
#include <conio.h>
#include <sstream>
#include<filesystem>
#include <limits>
#include <map>
#include <utility>
#include <string>
#include <iomanip>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ctime>
#include <chrono>
#include<algorithm>
#include <limits>


using namespace std;

//Clears The Current Line
void Authentication::clearcurrentline()
{
    cout << "\033[F";
    cout << "\r";
    cout << string(100, ' ');
    cout << "\r";
}

//Takes Input within Given Range
int Authentication::userinput(int lownumber, int highnumber, string s)
{
    int isWrong = 0;
    int inputNumber;
    while (true)
    {
        cout << s;
        cin >> inputNumber;
        clearcurrentline();
        if (isWrong)
        {
            clearcurrentline();
        }
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        if (inputNumber == 0)
        {
            return 0;
        }
        else if (inputNumber >= lownumber && inputNumber <= highnumber)
        {
            return inputNumber;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid  Choice" << endl;
            isWrong++;
        }
    }
}

//Loads Credential Data from file
void Authentication::loadData()
{
    string line, email, password;
    ifstream LoginInfo("Files/Login.csv");
    if (LoginInfo.is_open())
    {
        getline(LoginInfo, line);
        if (getline(LoginInfo, line))
        {
            stringstream info(line);
            getline(info, email, ',');
            getline(info, password);
        }
    }
    else
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    Email = email;
    Password = password;
}

//Login Menu
int Authentication::LoginMenu()
{
    loadData();
    system("cls");
    while (true)
    {
        string InputEmail, InputPassword;
        cout << left << setw(17) << "Enter Email of Press 0 To Go Back: ";
        cin >> InputEmail;
        if (InputEmail == "0")
        {
            return 0;
        }
        cout << left << setw(17) << "Enter Password or Press 0 To Go Back: ";
        cin >> InputPassword;
        if (InputPassword == "0")
        {
            break;
        }
        system("cls");
        if (InputEmail == Email && InputPassword == Password)
        {
            return -1;
        }
        else
        {
            cout << "Invalid Email or Password\n";
        }
    }
}

//Verifies Admin Email & Password
string Authentication::Verification(string a, string s)
{
    string input;
    int isWrong = 0;
    while (true)
    {
        cout << s;
        cin >> input;
        clearcurrentline();
        if (isWrong)
        {
            clearcurrentline();
        }
        if (input == "0")
        {
            return "0";
        }
        else if (input == a)
        {
            return input;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Your Given Data Is Incorrect" << endl;
            isWrong++;
        }
    }
}

//Changes Emails & Passwords
bool Authentication::changeCredentials()
{
    loadData();
    bool anythingChanged = false;
    ifstream LoginInfo("Files/Login.csv");
    string line, adminEmail, adminPassword;
    getline(LoginInfo, line);
    getline(LoginInfo, line);
    if (getline(LoginInfo, line))
    {
        stringstream info(line);
        getline(info, adminEmail, ',');
        getline(info, adminPassword);
    }
    while (true)
    {
        system("cls");
        cout << "1: Change Manager Email" << endl;
        cout << "2: Change Manager Password" << endl;
        cout << "3: Change Admin Email" << endl;
        cout << "4: Change Admin Password" << endl;

        int a = userinput(0, 4, "Please Enter Choice or Press 0 to Go Back: ");

        if (a == 0)
        {
            return anythingChanged;
        }
        if (a == 1)
        {
            string vadminEmail = Verification(adminEmail, "Please Enter Admin Email or Press 0 To Cancel: ");
            if (vadminEmail == "0")
            {
                continue;
            }
            string vadminPassword = Verification(adminPassword, "Please Enter Admin Password or Press 0 To Cancel: ");
            if (vadminPassword == "0")
            {
                continue;
            }
            cout << "Enter new Email Or Press 0 To Cancel: ";
            string newEmail;
            cin >> newEmail;
            if (newEmail == "0")
            {
                continue;
            }
            if (!newEmail.empty())
            {
                Email = newEmail;
                cout << "Email updated successfully!" << endl;
                anythingChanged = true;
            }
            else
            {
                cout << "Invalid Email. Please try again." << endl;
            }
        }
        else if (a == 2)
        {
            string vadminEmail = Verification(adminEmail, "Please Enter Admin Email or Press 0 To Cancel: ");
            if (vadminEmail == "0")
            {
                continue;
            }
            string vadminPassword = Verification(adminPassword, "Please Enter Admin Password or Press 0 To Cancel: ");
            if (vadminPassword == "0")
            {
                continue;
            }
            cout << "Enter new Password Or Press 0 To Cancel: ";
            string newPassword;
            cin >> newPassword;
            if (newPassword == "0")
            {
                continue;
            }
            if (!newPassword.empty())
            {
                Password = newPassword;
                cout << "Password updated successfully!" << endl;
                anythingChanged = true;
            }
            else
            {
                cout << "Invalid Password. Please try again." << endl;
            }
        }
        else if (a == 3)
        {
            string vadminEmail = Verification(adminEmail, "Please Enter Previous Admin Email or Press 0 To Cancel: ");
            if (vadminEmail == "0")
            {
                continue;
            }
            string vadminPassword = Verification(adminPassword,
                                                 "Please Enter Previous Admin Password or Press 0 To Cancel: ");
            if (vadminPassword == "0")
            {
                continue;
            }
            cout << "Enter new Email Or Press 0 To Cancel: ";
            string newAdminEmail;
            cin >> newAdminEmail;
            if (newAdminEmail == "0")
            {
                continue;
            }
            if (!newAdminEmail.empty())
            {
                adminEmail = newAdminEmail;
                cout << "Email updated successfully!" << endl;
                anythingChanged = true;
            }
            else
            {
                cout << "Invalid Email. Please try again." << endl;
            }
        }
        else if (a == 4)
        {
            string vadminEmail = Verification(adminEmail, "Please Enter Previous Admin Email or Press 0 To Cancel: ");
            if (vadminEmail == "0")
            {
                continue;
            }
            string vadminPassword = Verification(adminPassword,
                                                 "Please Enter Previous Admin Password or Press 0 To Cancel: ");
            if (vadminPassword == "0")
            {
                continue;
            }
            cout << "Enter new Password Or Press 0 To Cancel: ";
            string newAdminPassword;
            cin >> newAdminPassword;
            if (newAdminPassword == "0")
            {
                continue;
            }
            if (!newAdminPassword.empty())
            {
                adminPassword = newAdminPassword;
                cout << "Password updated successfully!" << endl;
                anythingChanged = true;
            }
            else
            {
                cout << "Invalid Password. Please try again." << endl;
            }
        }
        if (anythingChanged)
        {
            ofstream LoginInfo("Files/Login.csv", ios::trunc);
            if (LoginInfo.is_open())
            {
                LoginInfo << "Email,Password\n";
                LoginInfo << Email << "," << Password << "\n";
                LoginInfo << adminEmail << "," << adminPassword << "\n";
                LoginInfo.close();
                cout << "You Have To Login Again To Access Data" << endl;
            }
            else
            {
                cerr << "Error saving changes!" << endl;
            }
            int goBack = userinput(0, 0, "Press 0 To Go Back: ");
        }
    }
}
