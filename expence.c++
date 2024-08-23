#include <bits/stdc++.h>

using namespace std;

struct Expense
{
    string clientName;
    string companyName;
    string clientPosition;
    string productName;
    string category;
    double weight; // in kg for non-liquid, in liters for liquid
    double amount;
    double perItemPrice;
    string date;
    double deliveryCharge;
    double totalPrice;
};

class ExpenseTracker
{
private:
    vector<Expense> expenses;
    string fileName;

public:
    ExpenseTracker(const string &fileName) : fileName(fileName)
    {
        loadExpenses();
    }

    void displayMenu()
    {
        cout << "Expense Tracker Menu\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Exit\n";
    }

    void addExpense()
    {
        Expense expense;
        cout << "Enter client name: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, expense.clientName);//read a line of text from a stream

        cout << "Enter company name: ";
        getline(cin, expense.companyName);

        cout << "Enter client position: ";
        getline(cin, expense.clientPosition);

        cout << "Enter product name: ";
        getline(cin, expense.productName);

        cout << "Enter category (liquid or non-liquid): ";
        cin >> expense.category;

        cout << "Enter weight: ";
        cin >> expense.weight;

        if (expense.category == "liquid")
        {
            // Convert the weight to liters
            expense.weight = expense.weight;
        }

        cout << "Enter amount of product: ";
        cin >> expense.amount;

        cout << "Enter per item price: ";
        cin >> expense.perItemPrice;

        // Calculate total price
        expense.totalPrice = expense.amount * expense.perItemPrice;

        // Add delivery charge
        expense.deliveryCharge = 110.0;

        // Calculate final price
        expense.totalPrice += expense.deliveryCharge;

        // Get the current date
        time_t now = time(0);
        tm *ltm = localtime(&now);
        stringstream dateStream;
        dateStream << 1900 + ltm->tm_year << '-';
        dateStream << 1 + ltm->tm_mon << '-';
        dateStream << ltm->tm_mday;
        expense.date = dateStream.str();

        expenses.push_back(expense);
        saveExpenses();
        cout << "Expense added successfully.\n";
    }

    void viewExpenses()
    {
        if (expenses.empty())
        {
            cout << "No expenses to display.\n";
            return;
        }

        cout << "Expense List\n";
        cout << setw(15) << "Client Name" << setw(15) << "Company Name" << setw(15) << "Client Position"
             << setw(15) << "Product Name" << setw(15) << "Category" << setw(15) << "Weight"
             << setw(15) << "Amount" << setw(15) << "Per Item Price" << setw(15) << "Total Price"
             << setw(15) << "Delivery Charge" << setw(15) << "Date\n";
        cout << setfill('-') << setw(135) << "\n"
             << setfill(' ');

        for (const auto &expense : expenses)
        {
            cout << setw(15) << expense.clientName << setw(15) << expense.companyName << setw(15) << expense.clientPosition
                 << setw(15) << expense.productName << setw(15) << expense.category << setw(15) << expense.weight
                 << setw(15) << expense.amount << setw(15) << expense.perItemPrice << setw(15) << expense.totalPrice
                 << setw(15) << expense.deliveryCharge << setw(15) << expense.date << "\n";
        }
    }

    void saveExpenses()
    {
        ofstream file(fileName);

        if (!file)
        {
            cerr << "Error opening file for writing.\n";
            return;
        }

        for (const auto &expense : expenses)
        {
            file << expense.clientName << ',' << expense.companyName << ',' << expense.clientPosition << ','
                 << expense.productName << ',' << expense.category << ',' << expense.weight << ','
                 << expense.amount << ',' << expense.perItemPrice << ',' << expense.totalPrice << ','
                 << expense.deliveryCharge << ',' << expense.date << '\n';
        }

        file.close();
    }

    void loadExpenses()
    {
        ifstream file(fileName);

        if (!file)
        {
            cerr << "File does not exist. Creating a new file.\n";
            return;
        }

        expenses.clear();

        while (!file.eof())
        {
            Expense expense;
            getline(file, expense.clientName, ',');
            if (file.eof())
                break;
            getline(file, expense.companyName, ',');
            getline(file, expense.clientPosition, ',');
            getline(file, expense.productName, ',');
            getline(file, expense.category, ',');
            file >> expense.weight;
            file.ignore(); // Ignore the comma
            file >> expense.amount;
            file.ignore(); // Ignore the comma
            file >> expense.perItemPrice;
            file.ignore(); // Ignore the comma
            file >> expense.totalPrice;
            file.ignore(); // Ignore the comma
            file >> expense.deliveryCharge;
            file.ignore(); // Ignore the comma
            getline(file, expense.date);
            expenses.push_back(expense);
        }

        file.close();
    }

    void run()
    {
        int choice;

        do
        {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                cout << "Exiting Expense Tracker.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }

        } while (choice != 3);
    }
};

int main()
{
    ExpenseTracker tracker("expenses.txt");
    tracker.run();

    return 0;
}
