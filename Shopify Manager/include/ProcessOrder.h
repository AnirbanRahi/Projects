//
// Created by Anirban-Rahi on 10/25/2024.
//

#ifndef PROCESSORDER_H
#define PROCESSORDER_H

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
#include "ProcessOrder.h"
#include "Inventory.h"
class ProcessOrder
{
public:
    Inventory iv;
    void clearcurrentline();
    double userinput(double lownumber,double highnumber,string s,bool price);
    void takeorder();
    void showorder();
    string DateOrTime(int a);
    void SaveOrder(double &payment,string &Date, string &Time);

private:
    map<int, vector<pair<int, int>>> OrderedItems;
};

#endif // PROCESSORDER_H

