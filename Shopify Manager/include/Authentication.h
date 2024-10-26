#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H


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
#include "Authentication.h"

class Authentication
{
public:
    string Email;
    string Password;
    void loadData();
    string Verification(string a,string s);
    int LoginMenu();
    int userinput(int lownumber, int highnumber, string s);
    bool changeCredentials();
    void clearcurrentline();

protected:

private:
};

#endif // AUTHENTICATION_H
