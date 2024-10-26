//
// Created by Anirban-Rahi on 10/25/2024.
//

#ifndef TRANSACTIONRECORDS_H
#define TRANSACTIONRECORDS_H

#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <limits>

using namespace std;

class TransactionRecords
{
public:
    map<string, vector<string>> History;
    vector<string> Dates;
    vector<string> Time;
    string folderPath;

    void clearcurrentline();
    int userinput(int lownumber, int highnumber, string s);
    void loadDates();
    void loadTimeCSV(string DateFolder);
    void showData(string DateFolder, string TimeFile);
    void saleMenu();
};

#endif // TRANSACTIONRECORDS_H

