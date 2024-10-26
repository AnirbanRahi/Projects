//
// Created by Anirban-Rahi on 10/25/2024.
//

#include "Employee.h"
using namespace std;
#include <algorithm>
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

//Clears Current Line
void Employee::clearcurrentline()
{
    cout << "\033[F";
    cout << "\r";
    cout << string(100, ' ');
    cout << "\r";
}

//Takes input within given range
int Employee::userInput(int lownumber, int highnumber, string s)
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
        if (inputNumber >= lownumber && inputNumber <= highnumber)
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

//Load employees data from file
void Employee::loademployerdata()
{
    roles.clear();
    employers.clear();
    string folderPath = filesystem::current_path().string();
    replace(folderPath.begin(), folderPath.end(), '\\', '/');
    string rolespath = folderPath + "/" + "Files" + "/" + "Staff";
    for (auto categoryname : filesystem::directory_iterator(rolespath))
    {
        if (categoryname.is_regular_file() && categoryname.path().extension() == ".csv")
        {
            roles.push_back(categoryname.path().stem().string());
        }
    }
    for (auto role : roles)
    {
        string filePath = folderPath + "/" + "Files" + "/" + "Staff" + "/" + role + ".csv";

        ifstream file(filePath);
        if (!file)
        {
            cerr << "Error opening file" << endl;
        }
        else
        {
            vector<employee> data;
            string line;
            getline(file, line);
            while (getline(file, line))
            {
                stringstream row(line);
                string column;
                employee ey;
                if (getline(row, column, ','))
                {
                    ey.name = column;
                }
                else
                {
                    cerr << "Missing Name data in " << role << " file." << endl;
                    continue;
                }
                if (getline(row, column, ','))
                {
                    ey.role = column;
                }
                else
                {
                    cerr << "Missing Role data in " << role << " file." << endl;
                    continue;
                }
                if (getline(row, column, ','))
                {
                    ey.salary = stod(column);
                }
                else
                {
                    cerr << "Missing Salary data in " << role << " file." << endl;
                    continue;
                }
                data.push_back(ey);
            }
            employers[role] = data;
        }
    }
}

//Update file
bool Employee::updateFile(const string& role)
{
    string folderPath = filesystem::current_path().string();
    replace(folderPath.begin(), folderPath.end(), '\\', '/');
    string filePath = folderPath + "/" + "Files" + "/" + "Staff" + "/" + role + ".csv";
    ofstream file(filePath);
    if (!file)
    {
        cerr << "Error opening file for updating." << endl;
        return false;
    }
    file << "Name,Role,Salary\n";
    for (const auto& emp : employers[role])
    {
        file << emp.name << "," << emp.role << "," << fixed << setprecision(2) << emp.salary << "\n";
    }
    file.close();
    return true;
}

//Prints Employee Data
void Employee::printdata(int a)
{
    system("cls");
    vector<employee>& em = employers[roles[a - 1]];
    cout << left << setw(5) << "Sl." << setw(20) << "Name" << setw(20) << "Role" << "Salary" << endl;
    for (int i = 0; i < em.size(); i++)
    {
        employee ep = em[i];
        cout << left << setw(5) << i + 1 << setw(20) << ep.name << setw(20) << ep.role << ep.salary << endl;
    }
}

//Main Menu that update the data
void Employee::showemployeedata()
{
    loademployerdata();
    bool home = false;
    while (true)
    {
        system("cls");
        for (int i = 0; i < roles.size(); i++)
        {
            cout << i + 1 << "." << roles[i] << endl;
        }
        cout << endl;
        cout << "1: Enter New Staff Category" << endl;
        cout << "2: Delete Entire Category" << endl;
        cout << "3: Update Current Staff Category" << endl;
        int initialChoice = userInput(0, 3, "Please Choose or Press 0 to Go Back: ");
        if (initialChoice == 0)
        {
            break;
        }
        if (initialChoice == 1)
        {
            while (true)
            {
                system("cls");
                for (int i = 0; i < roles.size(); i++)
                {
                    cout << i + 1 << ". " << roles[i] << endl;
                }
                cout<<string(46,'-')<<endl;
                cout<<string(46,'-')<<endl;
                cout << "1: Create New Category" << endl<<endl;
                int createCategoryChoice = userInput(0, 1, "Please Enter Your Choice or Press 0 To Go Back: ");
                if (createCategoryChoice == 0)
                {
                    break;
                }
                while (true)
                {
                    string newCategory;
                    cout << "Please Enter New Category Name or Press 0 To Go Back: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                    getline(cin, newCategory);
                    if (newCategory == "0")
                    {
                        break;
                    }
                    if (find(roles.begin(), roles.end(), newCategory) != roles.end())
                    {
                        cout << "Category already exists!" << endl;
                        continue;
                    }
                    roles.push_back(newCategory);

                    string folderPath = filesystem::current_path().string();
                    replace(folderPath.begin(), folderPath.end(), '\\', '/');
                    string newCategoryFilePath = folderPath + "/" + "Files" + "/" + "Staff" + "/" + newCategory +
                        ".csv";
                    ofstream saveFile(newCategoryFilePath);
                    if (saveFile)
                    {
                        saveFile << "Name,Role,Salary\n";
                        saveFile.close();
                        cout << "***** " << newCategory << " Created Successfully *****" << endl;
                        cout << "To Add Items Go To Update Menu" << endl;
                        loademployerdata();
                        int x = userInput(0, 0, "Please press 0 to Go Back: ");
                        if (x == 0)
                        {
                            break;
                        }
                    }
                }
            }
        }
        else if (initialChoice == 2)
        {
            while (true)
            {
                system("cls");
                for (int i = 0; i < roles.size(); i++)
                {
                    cout << i + 1 << ". " << roles[i] << endl;
                }
                cout<<string(46,'-')<<endl;
                cout<<string(46,'-')<<endl;
                int deleteCategory = userInput(0, roles.size(), "Please enter Category No or Press 0 To Go Back : ");
                if (deleteCategory == 0)
                {
                    break;
                }
                string tempCategory=roles[deleteCategory-1];
                string folderpath = filesystem::current_path().string();
                replace(folderpath.begin(), folderpath.end(), '\\', '/');
                folderpath = folderpath + "/" + "Files" + "/" + "Staff" + "/" + roles[deleteCategory-1] +
                    ".csv";
                if (filesystem::exists(folderpath))
                {
                    filesystem::remove(folderpath);
                    cout << "***** " << tempCategory << " Deleted Successfully*****" << endl;
                    loademployerdata();
                }
                else
                {
                    cerr << "File Not Found" << endl;
                }
                cout<<string(46,'-')<<endl;
                cout<<string(46,'-')<<endl;
                cout << "0: Go Back" << endl;
                cout << "1: Delete Again" << endl;
                int e = userInput(0, 1, "Please enter your choice: ");
                if (e == 0)
                {
                    break;
                }
            }
        }
        else if (initialChoice == 3)
        {
            while (true)
            {
                system("cls");
                for (int i = 0; i < roles.size(); i++)
                {
                    cout << i + 1 << "." << roles[i] << endl;
                }
                int a = userInput(0, roles.size(), "Please enter Category No or Press 0 To Go Back : ");
                if (a == 0)
                {
                    break;
                }
                while (true)
                {
                    printdata(a);
                    cout<<string(46,'-')<<endl;
                    cout<<string(46,'-')<<endl;
                    cout << "1: Add" << endl;
                    cout << "2: Update" << endl;
                    cout << "3: Delete" << endl;
                    cout << "4: Return to Menu" << endl;
                    cout << "5: Close Program" << endl;
                    int b = userInput(0, 5, "Please enter your choice or Press 0 To Go Back: ");
                    if(b==0)
                    {
                        break;
                    }
                    if (b == 1)
                    {
                        while (true)
                        {
                            printdata(a);
                            employee newstaff;
                            cout << "Please Enter Name or Press 0 To Go Back: ";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            getline(cin, newstaff.name);
                            if (newstaff.name == "0")
                            {
                                break;
                            }
                            cout << "Please Enter Role: ";
                            getline(cin, newstaff.role);
                            if (newstaff.role == "0")
                            {
                                break;
                            }
                            cout << "Please Enter Salary: ";
                            cin >> newstaff.salary;
                            if (newstaff.salary == 0.0)
                            {
                                break;
                            }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            employers[roles[a - 1]].push_back(newstaff);
                            if (updateFile(roles[a - 1]))
                            {
                                cout << newstaff.name << " has been appointed as" << newstaff.role <<
                                    "with a salary of & " <<
                                    fixed << setprecision(2) << newstaff.salary << endl;
                            }
                            cout<<string(46,'-')<<endl;
                            cout<<string(46,'-')<<endl;
                            cout << "0: Go Back:" << endl;
                            cout << "1: Add Again:" << endl;
                            int c = userInput(0, 1, "Please enter your choice: ");
                            if (c == 0)
                            {
                                break;
                            }
                        }
                    }
                    if (b == 2)
                    {
                        for (int t = 1; t <= 6; t++)
                        {
                            clearcurrentline();
                        }
                        while (true)
                        {
                            printdata(a);
                            int persontoupdate = userInput(1, employers[roles[a - 1]].size(),
                                                           "Enter the Serial number to update or Press 0 To Go Back: ");
                            if (persontoupdate == 0)
                            {
                                break;
                            }
                            while (true)
                            {
                                printdata(a);
                                cout<<string(46,'-')<<endl;
                                cout<<string(46,'-')<<endl;
                                cout << "Updating Data for Serial No: " << persontoupdate << endl;
                                cout << "1: Update Name" << endl;
                                cout << "2: Update Role" << endl;
                                cout << "3: Update Salary" << endl;
                                int updatestaff = userInput(0, 3, "Please enter your choice or Press 0 To Go Back: ");
                                if (updatestaff == 0)
                                {
                                    break;
                                }
                                if (updatestaff == 1)
                                {
                                    string newName;
                                    cout << "Enter new Name or Press 0 To Go Back: ";
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    getline(cin, newName);
                                    if (newName == "0")
                                    {
                                        continue;
                                    }
                                    employers[roles[a - 1]][persontoupdate - 1].name = newName;
                                    updateFile(roles[a - 1]);
                                }
                                else if (updatestaff == 2)
                                {
                                    string newRole;
                                    cout << "Enter new Role of Press 0 To Go Back: ";
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    getline(cin, newRole);
                                    if (newRole == "0")
                                    {
                                        continue;
                                    }
                                    employers[roles[a - 1]][persontoupdate - 1].role = newRole;
                                    updateFile(roles[a - 1]);
                                }
                                else if (updatestaff == 3)
                                {
                                    double newSalary;
                                    cout << "Enter new Salary or Press 0 To Go Back: ";
                                    cin >> newSalary;
                                    if (newSalary == 0.0)
                                    {
                                        continue;
                                    }
                                    employers[roles[a - 1]][persontoupdate - 1].salary = newSalary;
                                    updateFile(roles[a - 1]);
                                }
                            }
                            for (int i = 1; i <= 5; i++)
                            {
                                clearcurrentline();
                            }
                            cout<<string(46,'-')<<endl;
                            cout<<string(46,'-')<<endl;
                            cout << "0: Go Back" << endl;
                            cout << "1: Update Another Data" << endl;
                            int d = userInput(0, 1, "Please enter your choice: ");
                            if (d == 0)
                            {
                                break;
                            }
                        }
                    }
                    if (b == 3)
                    {
                        while (true)
                        {
                            printdata(a);
                            int deletestaff = userInput(0, employers[roles[a - 1]].size(),
                                                        "Enter the Serial number to remove of Press 0 To Go Back: ");
                            if (deletestaff == 0)
                            {
                                break;
                            }
                            employers[roles[a - 1]].erase(employers[roles[a - 1]].begin() + (deletestaff - 1));
                            if (updateFile(roles[a - 1]))
                            {
                                cout << "Staff Successfully Removed" << endl;
                            }
                            cout<<string(46,'-')<<endl;
                            cout<<string(46,'-')<<endl;
                            cout << "0: Go Back" << endl;
                            cout << "1: Delete Again" << endl;
                            int e = userInput(0, 1, "Please enter your choice: ");
                            if (e == 0)
                            {
                                break;
                            }
                        }
                    }
                    if (b == 4)
                    {
                        home = true;
                        break;
                    }
                    if (b == 5)
                    {
                        exit(0);
                    }
                }
            }
        }
        if (home)
        {
            break;
        }
    }
}
