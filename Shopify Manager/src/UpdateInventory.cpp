//
// Created by Anirban-Rahi on 10/25/2024.
//

#include "UpdateInventory.h"
#include "UpdateInventory.h"

void UpdateInventory::clearcurrentline()
{
    cout << "\033[F";
    cout << "\r";
    cout << string(100, ' ');
    cout << "\r";
}

int UpdateInventory::userinput(int lownumber, int highnumber, string s)
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
            cout << "Invalid input. Please Enter A Valid Number" << endl;
            isWrong++;
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
        isWrong++;
        cout << "Input Out Of Range." << endl;
    }
}

bool UpdateInventory::updateFile(const string& category, vector<Inventory::ProductInfo>& items)
{
    string filePath = iv.folderPath + "/" + "Files" + "/" + "Inventory" + "/" + category + ".csv";
    ofstream file(filePath);
    if (!file)
    {
        cerr << "Error opening file for updating." << endl;
        return false;
    }
    file << "Serial,Name,Price\n";
    for (const auto& item : items)
    {
        file << item.name << "," << fixed << setprecision(2) << item.price << "\n";
    }
    file.close();
    return true;
}

void UpdateInventory::printCategoryitems(vector<Inventory::ProductInfo>& items, string categoryName)
{
    system("cls");
    cout << categoryName << ":" << endl;
    int i = 1;
    for (auto item : items)
    {
        cout << left << setw(5) << i << setw(18) << item.name << "$" << setw(16) << item.price << endl;
        i++;
    }
}

void UpdateInventory::updateMenu()
{
    iv.loadData();
    while (true)
    {
        system("cls");
        bool updateMenu = false;
        cout << "1. Add, Delete or Update Items in Category" << endl;
        cout << "2. Delete Entire Category" << endl;
        cout << "3. Add New Category" << endl;
        cout << "4. Close Program" << endl;
        int user = userinput(0, 4, "Please Enter Your Choice or Press 0 To Go Back: ");
        if (user == 0)
        {
            break;
        }
        if (user == 4)
        {
            exit(0);
        }
        if (user == 1)
        {
            while (true)
            {
                iv.displayInventory();
                cout<<string(46,'-')<<endl;
                cout<<string(46,'-')<<endl;
                int userCategory = userinput(0, iv.Categories.size(), "Please Enter Category No or 0 To Go Back: ");
                if (userCategory == 0)
                {
                    break;
                }
                while (true)
                {
                    printCategoryitems(iv.InventoryCatalogue[iv.Categories[userCategory - 1]],
                                       iv.Categories[userCategory - 1]);
                    cout<<string(46,'-')<<endl;
                    cout<<string(46,'-')<<endl;
                    cout << "1: Add Item" << endl;
                    cout << "2: Delete Item" << endl;
                    cout << "3: Update Item" << endl;
                    cout << "4: Go To Update Menu" << endl;
                    int userchoice = userinput(0, 4, "Please Enter Your Choice or Press 0 To Go Back: ");
                    if (userchoice == 0)
                    {
                        break;
                    }
                    if (userchoice == 4)
                    {
                        updateMenu = true;
                        break;
                    }
                    if (userchoice == 1)
                    {
                        while (true)
                        {
                            printCategoryitems(iv.InventoryCatalogue[iv.Categories[userCategory - 1]],
                                               iv.Categories[userCategory - 1]);
                            cout<<string(46,'-')<<endl;
                            cout<<string(46,'-')<<endl;
                            Inventory::ProductInfo pi;
                            cout << "Please  Enter Item Name or Press 0 To Go Back: ";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            getline(cin, pi.name);
                            if (pi.name == "0")
                            {
                                break;
                            }
                            cout << "Please Enter Price of Press 0 To Go Back: ";
                            cin >> pi.price;
                            if (pi.price == 0.0)
                            {
                                break;
                            }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            iv.InventoryCatalogue[iv.Categories[userCategory - 1]].push_back(pi);
                            if (updateFile(iv.Categories[userCategory - 1],
                                           iv.InventoryCatalogue[iv.Categories[userCategory - 1]]))
                            {
                                cout << "*****" << pi.name << " has been added with a price of $" << fixed <<
                                    setprecision(2) << pi.price << "*****" << endl;
                            }
                            cout<<string(46,'-')<<endl;
                            cout<<string(46,'-')<<endl;
                            cout << "0: Go Back:" << endl;
                            cout<<"1: Add Again"<<endl;
                            int c = userinput(0, 1, "Please enter your choice: ");
                            if (c == 0)
                            {
                                break;
                            }
                        }
                    }
                    else if (userchoice == 2)
                    {
                        while (true)
                        {
                            printCategoryitems(iv.InventoryCatalogue[iv.Categories[userCategory - 1]],
                                               iv.Categories[userCategory - 1]);
                            int deletestaff = userinput(
                                0, iv.InventoryCatalogue[iv.Categories[userCategory - 1]].size(),
                                "Enter the Serial number you want to remove or 0 to Go Back: ");
                            if (deletestaff == 0)
                            {
                                break;
                            }
                            string tempItem = iv.InventoryCatalogue[iv.Categories[userCategory - 1]][deletestaff - 1].
                                name;
                            iv.InventoryCatalogue[iv.Categories[userCategory - 1]].erase(
                                iv.InventoryCatalogue[iv.Categories[userCategory - 1]].begin() + (deletestaff - 1));
                            if (updateFile(iv.Categories[userCategory - 1],
                                           iv.InventoryCatalogue[iv.Categories[userCategory - 1]]))
                            {
                                cout << "*****" << tempItem << " Successfully Removed*****" << endl;
                            }
                            cout<<string(46,'-')<<endl;
                            cout<<string(46,'-')<<endl;
                            cout << "0: Go Back" << endl;
                            cout << "1: Delete Again" << endl;
                            int e = userinput(0, 1, "Please enter your choice: ");
                            if (e == 0)
                            {
                                break;
                            }
                        }
                    }
                    else if (userchoice == 3)
                    {
                        printCategoryitems(iv.InventoryCatalogue[iv.Categories[userCategory - 1]],
                                           iv.Categories[userCategory - 1]);
                        int itemtoupdate = userinput(0, iv.InventoryCatalogue[iv.Categories[userCategory - 1]].size(),
                                                     "Enter the Serial number you want to update or Press 0 To Go Back: ");
                        if (itemtoupdate == 0)
                        {
                            continue;
                        }
                        while (true)
                        {
                            printCategoryitems(iv.InventoryCatalogue[iv.Categories[userCategory - 1]],
                                               iv.Categories[userCategory - 1]);
                            cout<<string(46,'-')<<endl;
                            cout<<string(46,'-')<<endl;
                            cout << "Updating Data for Serial No: " << itemtoupdate << endl;
                            cout << "1: Update Name" << endl;
                            cout << "2: Update Price" << endl;
                            int updateitem = userinput(1, 2, "Please enter your choice or Press 0 To Go Back: ");
                            if (updateitem == 0)
                            {
                                break;
                            }
                            if (updateitem == 1)
                            {
                                string newName;
                                cout << "Enter new Name or Press 0 To Go Back: ";
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                getline(cin, newName);
                                if (newName == "0")
                                {
                                    continue;
                                }
                                iv.InventoryCatalogue[iv.Categories[userCategory - 1]][itemtoupdate - 1].name = newName;
                                updateFile(iv.Categories[userCategory - 1],
                                           iv.InventoryCatalogue[iv.Categories[userCategory - 1]]);
                            }
                            else if (updateitem == 2)
                            {
                                double newPrice;
                                cout << "Enter new Price or Press 0 To Go Back: ";
                                cin >> newPrice;
                                if (newPrice == 0)
                                {
                                    continue;
                                }
                                iv.InventoryCatalogue[iv.Categories[userCategory - 1]][itemtoupdate - 1].price =
                                    newPrice;
                                updateFile(iv.Categories[userCategory - 1],
                                           iv.InventoryCatalogue[iv.Categories[userCategory - 1]]);
                            }
                        }
                    }
                }
                if (updateMenu)
                {
                    break;
                }
            }
        }
        else if (user == 2)
        {
            while (true)
            {
                iv.displayInventory();
                cout<<string(46,'-')<<endl;
                cout<<string(46,'-')<<endl;
                int categorytodelete = userinput(0, iv.Categories.size(),
                                                 "Enter the Category number You want to delete or Press 0 To Go Back: ");
                if (categorytodelete == 0)
                {
                    break;
                }
                string folderpath = filesystem::current_path().string();
                replace(folderpath.begin(), folderpath.end(), '\\', '/');
                string tempCategory = iv.Categories[categorytodelete - 1];
                string filetodelete = folderpath + "/" + "Files" + "/" + "Inventory" + "/" + iv.Categories[
                    categorytodelete -
                    1] + ".csv";
                //cout<<filetodelete<<endl;
                if (filesystem::exists(filetodelete))
                {
                    filesystem::remove(filetodelete);
                    cout << "*****" << tempCategory << " Deleted Successfully*****" << endl;
                    iv.loadData();
                }
                else
                {
                    cerr << "File Not Found" << endl;
                }
                cout<<string(46,'-')<<endl;
                cout<<string(46,'-')<<endl;
                cout << "0: Go Back" << endl;
                cout << "1: Delete Again" << endl;
                int e = userinput(0, 1, "Please enter your choice: ");
                if (e == 0)
                {
                    break;
                }
            }
        }
        else if (user == 3)
        {
            while (true)
            {
                system("cls");
                cout << "Categories" << endl;
                for (int i = 0; i < iv.Categories.size(); i++)
                {
                    cout << i + 1 << "." << iv.Categories[i] << endl;
                }
                cout<<string(46,'-')<<endl;
                cout<<string(46,'-')<<endl;
                cout << "1: Create New Category" << endl;
                int createCategoryChoice = userinput(0, 1, "Please Enter Your Choice or Press 0 To Go Back: ");
                if (createCategoryChoice == 0)
                {
                    break;
                }
                while (true)
                {
                    for (int x = 1; x <= 1; x++)
                    {
                        clearcurrentline();
                    }
                    string newCategory;
                    cout << "Please Enter New Category Name or Press 0 To Go Back: ";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                    getline(cin, newCategory);
                    if (newCategory == "0")
                    {
                        break;
                    }
                    if (find(iv.Categories.begin(), iv.Categories.end(), newCategory) != iv.Categories.end())
                    {
                        cout << "Category already exists!" << endl;
                        continue;
                    }
                    iv.Categories.push_back(newCategory);
                    string newCategoryFilePath = iv.folderPath + "/" + "Files" + "/" + "Inventory" + "/" + newCategory +
                        ".csv";
                    ofstream saveFile(newCategoryFilePath);
                    if (saveFile)
                    {
                        saveFile << "Serial,Name,Price\n";
                        saveFile.close();
                        cout << "***** " << newCategory << " Created Successfully *****" << endl;
                        cout << "To Add Items Go To Update Menu" << endl;
                        iv.loadData();
                        int x = userinput(1, 1, "Please press 1 to Go Back: ");
                        if (x == 1)
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
}
