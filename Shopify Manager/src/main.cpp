#include <iostream>
#include <windows.h>
#include "Employee.h"
#include "Inventory.h"
#include "Authentication.h"
#include "ProcessOrder.h"
#include "TransactionRecords.h"
#include "UpdateInventory.h"
using namespace std;

void clearcurrentline()
{
    cout << "\033[F";
    cout << "\r";
    cout << string(50, ' ');
    cout << "\r";
}

int userinput(int lownumber, int highnumber, string s)
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

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid  Choice" << endl;
        isWrong++;
    }
}

int main()
{

    Authentication au;
    Inventory iv;
    ProcessOrder po;
    UpdateInventory ui;
    Employee em;
    TransactionRecords tr;
    iv.loadData();
    tr.loadDates();
    bool log = false;

    while (true)
    {
        while(true)
        {
            system("cls");
            cout << string(30, '=') << endl;
            cout << "Welcome to RoxxCart Store" << endl;
            cout << string(30, '=') << endl;
            cout << "1: Login" << endl;
            cout << "2: Change Credentials" << endl;
            cout << "3: Exit" << endl;
            int choice = userinput(1, 3, "Please enter your choice: ");
            if (choice == 1)
            {
                if (au.LoginMenu() == -1)
                {
                    log = true;
                    break;
                }
            }
            if (choice == 2)
            {
                au.changeCredentials();
                continue;
            }
            if (choice == 3)
            {
                return 0;
            }
        }
        while (log)
        {
            system("cls");
            cout << string(30, '=') << endl;
            cout << "Welcome to RoxxCart Store" << endl;
            cout << string(30, '=') << endl;
            cout << "1: Process Order" << endl;
            cout << "2: Update Inventory" << endl;
            cout << "3: Display and Update Employee Data" << endl;
            cout << "4: See Transaction Records" << endl;
            cout << "5: Change Login Credentials" << endl;
            cout << "6: Logout" << endl;
            cout << "7: Quit Program" << endl;
            int a = userinput(1, 7, "Please enter your choice: ");
            if (a == 7)
            {
                return 0;
            }
            if (a == 6)
            {
                log = false;
            }
            else if (a == 1)
            {
                while (true)
                {
                    iv.displayInventory();
                    po.showorder();
                    int b;
                    cout << string(20, '=') << endl;
                    cout << "1: Process Order Again" << endl;
                    cout << "2: Return To Menu" << endl;
                    cout << "3: Quit Program" << endl;
                    cout << "Please Enter Your Choice: ";
                    cin >> b;
                    if (b == 2)
                    {
                        break;
                    }
                    if (b == 3)
                    {
                        return 0;
                    }

                    iv.loadData();
                }
            }
            else if (a == 2)
            {
                ui.updateMenu();
            }
            else if (a == 3)
            {
                em.showemployeedata();
            }
            else if (a == 4)
            {
                tr.saleMenu();
            }
            else if (a == 5)
            {
                system("cls");
                if (au.changeCredentials())
                {
                    log = false;
                }
            }
        }
    }
}
