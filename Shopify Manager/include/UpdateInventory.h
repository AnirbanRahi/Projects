//
// Created by Anirban-Rahi on 10/25/2024.
//

#ifndef UPDATEINVENTORY_H
#define UPDATEINVENTORY_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <filesystem>
#include "Inventory.h"
using namespace std;

class UpdateInventory
{
public:
    Inventory iv;
    void clearcurrentline();
    int userinput(int lownumber, int highnumber, string s);
    bool updateFile(const string& category, vector<Inventory::ProductInfo>& items);
    void printCategoryitems(vector<Inventory::ProductInfo>& items, string categoryName);
    void updateMenu();
};


#endif // UPDATEINVENTORY_H
