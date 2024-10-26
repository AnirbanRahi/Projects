//
// Created by Anirban-Rahi on 10/25/2024.
//

#include "ProcessOrder.h"
using namespace std;
#include <vector>
#include<iostream>
#include <fstream>
#include <sstream>
#include<filesystem>
#include <limits>
#include <map>
#include <utility>
#include <conio.h>
#include <limits>
#include <map>
#include <utility>
#include <string>
#include <unordered_map>
#include <iomanip>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "ProcessOrder.h"

void ProcessOrder::clearcurrentline()
{
    cout << "\033[F";
    cout << "\r";
    cout << string(100, ' ');
    cout << "\r";
}
string ProcessOrder::DateOrTime(int a)
{
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    tm* now_tm = localtime(&now_c);
    if(a==1)
    {
        stringstream DateStream;
        DateStream << put_time(now_tm, "%d-%m-%Y");
        return DateStream.str();
    }
    else if(a==2)
    {
        stringstream TimeStream;
        TimeStream << put_time(now_tm, "%I.%M.%S %p");
        return TimeStream.str();
    }
}
double ProcessOrder::userinput(double lownumber, double highnumber, string s,bool price)
{
    int isWrong = 0;
    double inputNumber;
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
            cout << "Invalid input. Please Enter A Valid Number" << endl;
            continue;
        }
        if(inputNumber==0)
        {
            return 0.0;
        }
        else if (inputNumber >= lownumber && inputNumber <= highnumber)
        {
            return static_cast<double>(inputNumber);
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            isWrong++;
            if(price)
            {
                cout<<"The amount entered is below the minimum required. Kindly ensure you provide enough money."<<endl;
            }
            else
            {
                cout << "Input Out Of Range." << endl;
            }
        }
    }
}
void ProcessOrder::takeorder()
{
    OrderedItems.clear();
    while (true)
    {

        int cateNo = static_cast<int>(userinput(0.0, static_cast<double>(iv.Categories.size()), "Please Enter Category Number or 0 to Cancel: ",false));
        if (cateNo == 0) break;

        int slNo = static_cast<int>(userinput(0.0, static_cast<double>(iv.InventoryCatalogue[iv.Categories[cateNo - 1]].size()), "Please Enter Item Number or 0 to Cancel: ",false));
        if (slNo == 0) break;

        int quantity = static_cast<int>(userinput(0.0, 20.0, "Please Enter Quantity(1-20) or 0 to Cancel: ",false));
        if (quantity == 0) break;

        if(cateNo > 0 && slNo > 0 && quantity > 0)
        {
            // Check if the item is already in OrderedItems
            bool found = false;
            for(auto& item : OrderedItems[cateNo])
            {
                if(item.first == slNo) // Same item found, update quantity
                {
                    item.second += quantity;
                    found = true;
                    break;
                }
            }
            if(!found) // If item not found, add it
            {
                OrderedItems[cateNo].push_back(make_pair(slNo, quantity));
            }
        }
    }
}
void ProcessOrder::SaveOrder(double &payment,string &Date, string &Time)
{
    if(OrderedItems.size()>0)
    {
        int i = 1;

        string Date = DateOrTime(1);
        string Time =DateOrTime(2);

        double total = 0;

        vector<string> Save;
        Save.push_back("Sl,Category,Item,Price,Quantity,TotalPrice");
        for (auto OI : OrderedItems)
        {
            //OI.first=category serial number
            //OI.second=item serial number + quantity
            string categoryName = iv.Categories[OI.first - 1];
            for (auto items : OI.second)
            {
                int sNo = items.first;
                int quan = items.second;
                auto it = iv.InventoryCatalogue.find(categoryName);
                if (it != iv.InventoryCatalogue.end())
                {
                    ostringstream Os;
                    vector<Inventory::ProductInfo> item = it->second;
                    Os << (to_string(i)) << "," <<
                       categoryName << "," <<
                       item[sNo - 1].name << "," <<
                       fixed << setprecision(2) << item[sNo - 1].price << "," <<
                       quan << "," <<
                       fixed << setprecision(2) << (quan * item[sNo - 1].price);
                    string itemHistory = Os.str();
                    Save.push_back(itemHistory);
                    total = total + (quan * item[sNo - 1].price);
                    i++;
                }
            }
        }
        ostringstream lastLine;
        lastLine << "," << "," << "," << "," << "Total Amount" << "," << fixed << setprecision(2) << total;
        Save.push_back(lastLine.str());
        lastLine.str("");
        lastLine.clear();
        lastLine << "," << "," << "," << "," << "Payment Received" << "," << fixed << setprecision(2) << payment;
        Save.push_back(lastLine.str());
        lastLine.str("");
        lastLine.clear();
        lastLine << "," << "," << "," << "," << "Money Changed" << "," << fixed << setprecision(2) << payment-total<<flush;
        Save.push_back(lastLine.str());

        namespace fs = std::filesystem;
        string DateHistory = "Sale History/" + Date;
        if (!fs::exists(DateHistory))
        {
            fs::create_directories(DateHistory);
        }
        string fileName = Time + ".csv";
        string filePath = DateHistory + "/" + fileName;
        ofstream SaveFile(filePath);
        if (SaveFile.is_open())
        {
            for (auto row : Save)
            {
                SaveFile << row << endl;
            }
        }
        else
        {
            cout << "Unable To Create File\n";
        }
    }
}
void ProcessOrder::showorder()
{
    iv.loadData();
    iv.displayInventory();
    takeorder();
    if(OrderedItems.size()>0)
    {
        int i = 1;

        string Date = DateOrTime(1);
        string Time = DateOrTime(2);

        system("cls");
        cout << "Current date and time: " << Date << "   " << Time << endl;
        double total = 0;
        cout << "You ordered these food" << endl;
        cout << left << setw(5) << "Sl." << setw(25) << "Category" << setw(25) << "Item" << setw(10) << "Price" << setw(10) << "Quantity" << "Total" << endl;
        for (auto OI : OrderedItems)
        {
            string categoryName = iv.Categories[OI.first - 1];
            for (auto items : OI.second)
            {
                int sNo = items.first;
                int quan = items.second;
                auto it = iv.InventoryCatalogue.find(categoryName);
                if (it != iv.InventoryCatalogue.end())
                {
                    vector<Inventory::ProductInfo> item = it->second;
                    cout << left << setw(5) << (to_string(i) + ".") << setw(25) << categoryName
                         << setw(25) << item[sNo - 1].name <<"$"<<setw(9) << item[sNo - 1].price << setw(10) << quan <<"$"<<(quan * item[sNo - 1].price) << endl;
                    total = total + (quan * item[sNo - 1].price);
                    i++;
                }
            }
        }
        cout<<string(90,'-')<<endl;
        cout<<left<<setw(55)<<" "<<setw(20)<<"Total Amount"<<"$"<<fixed<<setprecision(2)<<total<<endl;
        double a,changeMoney;
        a=userinput(total,200000.0,"Please Pay the amount or 0 To Cancel: ",true);
        if(a>=total)
        {
            if(a!=total)
            {
                changeMoney=a-total;
            }
            cout<<left<<setw(55)<<" "<<setw(20)<<"Payment Received"<<"$"<<fixed<<setprecision(2)<<a<<endl;
            cout<<left<<setw(55)<<" "<<setw(20)<<"Money Changed"<<"$"<<fixed<<setprecision(2)<<changeMoney<<endl;
            SaveOrder(a,Date,Time);
        }
    }
}
