//
// Created by Anirban-Rahi on 10/25/2024.
//

#ifndef INVENTORY_H
#define INVENTORY_H


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
#include <unordered_map>
#include <iomanip>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ctime>
#include <chrono>
#include <iomanip>
class Inventory
{
public:
    string folderPath;
    struct ProductInfo
    {
        string name;
        double price;
    };

    vector<string> Categories;
    map<string, vector<ProductInfo>> InventoryCatalogue;
    void loadData();
    void displayInventory();
};

#endif // INVENTORY_H

