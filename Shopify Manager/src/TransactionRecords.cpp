//
// Created by Anirban-Rahi on 10/25/2024.
//

#include "TransactionRecords.h"
#include "TransactionRecords.h"
#include<algorithm>

void TransactionRecords::clearcurrentline()
{
    cout << "\033[F";
    cout << "\r";
    cout << string(50, ' ');
    cout << "\r";
}

int TransactionRecords::userinput(int lownumber, int highnumber, string s)
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
        else if (inputNumber >= lownumber && inputNumber <= highnumber)
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

void TransactionRecords::loadDates()
{
    Dates.clear();
    folderPath = filesystem::current_path().string();
    replace(folderPath.begin(), folderPath.end(), '\\', '/');
    folderPath = folderPath + "/" + "Sale History" + "/";

    for (const auto& date : filesystem::directory_iterator(folderPath))
    {
        if (date.is_directory())
        {
            Dates.push_back(date.path().filename().string());
        }
    }
}

void TransactionRecords::loadTimeCSV(string DateFolder)
{
    Time.clear();
    string filePath = folderPath + "/" + DateFolder + "/";
    for (auto time : filesystem::directory_iterator(filePath))
    {
        if (time.is_regular_file() && time.path().extension() == ".csv")
        {
            Time.push_back(time.path().stem().string());
        }
    }
}

void TransactionRecords::showData(string DateFolder, string TimeFile)
{
    string filePath = folderPath + "/" + DateFolder + "/" + TimeFile + ".csv";
    cout << left << setw(5) << "Sl." << setw(25) << "Category" << setw(25) << "Item" << setw(10) << "Price" << setw(10)
        << "Quantity" << "Total" << endl;
    cout << string(3, '-') << string(2, ' ') << string(8, '-') << string(17, ' ') << string(4, '-') << string(21, ' ')
        << string(5, '-') << string(5, ' ') << string(8, '-') << string(2, ' ') << string(5, '-') << endl;

    struct soldItems
    {
        int sl;
        string category;
        string item;
        double price;
        int quantity;
        double total;
    };

    struct amount
    {
        string s;
        double p;
    };

    ifstream data(filePath);
    vector<string> Lines;
    string line;
    getline(data, line);

    while (getline(data, line))
    {
        Lines.push_back(line);
    }

    for (int i = 0; i < Lines.size() - 3; i++)
    {
        stringstream row(Lines[i]);
        string column;
        soldItems fd;
        if (getline(row, column, ','))
        {
            fd.sl = stoi(column);
        }
        if (getline(row, column, ','))
        {
            fd.category = column;
        }
        if (getline(row, column, ','))
        {
            fd.item = column;
        }
        if (getline(row, column, ','))
        {
            fd.price = stod(column);
        }
        if (getline(row, column, ','))
        {
            fd.quantity = stoi(column);
        }
        if (getline(row, column, ','))
        {
            fd.total = stod(column);
        }
        cout << left << setw(5) << fd.sl << setw(25) << fd.category << setw(25) << fd.item << setw(10) << fd.price <<
            setw(10) << fd.quantity << "$" << fd.total << endl;
    }

    cout << left << setw(55) << " " << string(26, '-') << endl;

    for (int i = Lines.size() - 3; i < Lines.size(); i++)
    {
        stringstream row(Lines[i]);
        string column;
        amount am;
        for (int j = 1; j <= 4; j++)
        {
            getline(row, column, ',');
        }
        if (getline(row, column, ','))
        {
            am.s = column;
        }
        if (getline(row, column, ','))
        {
            am.p = stod(column);
        }
        cout << left << setw(55) << " " << setw(20) << am.s << "$" << fixed << setprecision(2) << am.p << endl;
    }

    cout << string(81, '-') << endl;
    cout << string(81, '-') << endl;
}

void TransactionRecords::saleMenu()
{
    loadDates();
    while (true)
    {
        system("cls");
        int i = 1;
        for (auto date : Dates)
        {
            cout << i << ": " << date << endl;
            i++;
        }

        int dateSerial = userinput(0, Dates.size(), "Enter Serial Of Date or 0 To Go Back: ");
        if (dateSerial == 0)
        {
            break;
        }
        while (true)
        {
            system("cls");
            string DateFolder = Dates[dateSerial - 1];
            loadTimeCSV(DateFolder);

            for (auto time : Time)
            {
                cout << "Time: " << time << endl;
                showData(DateFolder, time);
            }

            int x = userinput(0, 0, "Press 0 To Go Back: ");
            if (x == 0)
            {
                break;
            }
        }
    }
}
