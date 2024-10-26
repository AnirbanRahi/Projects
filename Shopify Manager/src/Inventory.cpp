//
// Created by Anirban-Rahi on 10/25/2024.
//

#include "Inventory.h"
using namespace std;
#include <algorithm>
#include <vector>
#include<iostream>
#include <fstream>
#include <conio.h>
#include <sstream>
#include<filesystem>
#include<algorithm>
#include <limits>
#include <map>
#include <utility>
#include <string>
#include <iomanip>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ctime>
#include <chrono>
void Inventory::loadData()
{
    Categories.clear();
    InventoryCatalogue.clear();
    folderPath=filesystem::current_path().string();
    replace(folderPath.begin(),folderPath.end(),'\\','/');
    cout<<folderPath<<endl;
    string categoriespath=folderPath+"/"+"Files"+"/"+"Inventory";

    for (auto categoryname : filesystem::directory_iterator(categoriespath))
    {
        if (categoryname.is_regular_file() && categoryname.path().extension() == ".csv")
        {
            Categories.push_back(categoryname.path().stem().string());
        }
    }

    for (auto category : Categories)
    {
        string filePath = folderPath +"/"+"Files"+"/"+"Inventory"+"/"+category + ".csv";
        //cout<<filePath<<endl;
        ifstream file(filePath);
        if (!file)
        {
            cerr << "Error opening "<<category<<" file" << endl;
        }
        else
        {
            vector<ProductInfo>data;
            string line;
            getline(file, line);
            while (getline(file, line))
            {
                stringstream row(line);
                string column;
                ProductInfo pi;
                if (getline(row, column, ','))
                {
                    pi.name = column;
                }
                if (getline(row, column, ','))
                {
                    pi.price = stod(column);
                }
                data.push_back(pi);
            }
            InventoryCatalogue[category] = data;
        }
    }
}
void Inventory::displayInventory()
{
    system("cls");
    cout<<string(108,'-')<<endl;
    cout<<left<<setw(43)<<" ";
    cout << "The RoxxCart Store"<<endl;
    cout<<string(108,'-')<<endl;

    int totalCategories = Categories.size();
    int column = 3;

    for (int i = 0; i < totalCategories; i += column)
    {
        int currentTotalColumn=min(column,totalCategories-i);
        /// Category headers
        for(int j=1; j<=currentTotalColumn; j++)
        {
            int categoryDone=i+j;
            cout << left << setw(40) <<((categoryDone<=totalCategories+1)?("Category-"+to_string(categoryDone)+":"+Categories[categoryDone-1]):"");
        }
        cout<<endl;
        /// Table headers
        for(int j=1; j<=currentTotalColumn; j++)
        {
            cout << left << setw(5) << "Sl." << setw(18) << "Name" << setw(17) << "Price";
        }
        cout<<endl;
        vector<string> currentCategories(currentTotalColumn);
        int maxRows = -1;
        for(int j=0; j<currentTotalColumn; j++)
        {
            int totalRows=((i + j < totalCategories)?(InventoryCatalogue.at(Categories[i + j]).size()):0);
            currentCategories[j] = Categories[i+j];
            maxRows = max(maxRows, static_cast<int>(InventoryCatalogue[currentCategories[j]].size()));
            maxRows = max(maxRows, totalRows);
        }
        for(int row=0; row<maxRows; row++)
        {
            for(int j=0; j<currentTotalColumn; j++)
            {
                vector<ProductInfo>&productInfo=InventoryCatalogue[currentCategories[j]];
                if(row<productInfo.size())
                {
                    cout << left << setw(5) << row+1<< setw(18)
                         <<  productInfo[row].name << "$" << setw(16) << productInfo[row].price;
                }
                else
                {
                    cout <<left<< setw(40) << " ";
                }
            }
            cout<<endl;
        }
        cout << endl<<endl;
    }
}
