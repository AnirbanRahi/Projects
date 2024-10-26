//
// Created by Anirban-Rahi on 10/25/2024.
//

#ifndef EMPLOYEE_H
#define EMPLOYEE_H
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
#include "Employee.h"
class Employee
{
private:
    struct employee
    {
        string name;
        string role;
        double salary;
    };
    vector<string>roles;
    map<string, vector<employee>> employers;

public:
    void clearcurrentline();
    int userInput(int lownumber, int highnumber, string s);
    void loademployerdata();
    bool updateFile(const string& role);
    void printdata(int a);
    void showemployeedata();
};
#endif // EMPLOYEE_H

