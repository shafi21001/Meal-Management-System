#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

struct Member
{
    string name;
    double deposit;
    int meals;
};

class MessManager
{
private:
    map<string, Member> members;
    double total_bazar;
    const string db_file = "mess_data.csv";
    const string expense_file = "bazar_data.txt";

    // Standard input clearing to avoid infinite loops on bad input
    void clear_input()
    {
        cin.clear();
        cin.ignore(10000, '\n');
    }

    double get_amount(const string &prompt)
    {
        double val;
        cout << prompt;
        while (!(cin >> val) || val < 0)
        {
            cout << "Invalid. Enter a positive number: ";
            clear_input();
        }
        clear_input();
        return val;
    }

    void load_data()
    {
        ifstream file(db_file);
        if (file.is_open())
        {
            string line, name, dep_str, meal_str;
            while (getline(file, line))
            {
                stringstream ss(line);
                if (getline(ss, name, ',') && getline(ss, dep_str, ',') && getline(ss, meal_str, ','))
                {
                    members[name] = {name, stod(dep_str), stoi(meal_str)};
                }
            }
            file.close();
        }

        ifstream e_file(expense_file);
        if (e_file.is_open())
        {
            e_file >> total_bazar;
            e_file.close();
        }
        else
        {
            total_bazar = 0.0;
        }
    }

    void save_data()
    {
        ofstream file(db_file);
        if (file.is_open())
        {
            for (const auto &[key, m] : members)
            {
                file << m.name << "," << m.deposit << "," << m.meals << "\n";
            }
            file.close();
        }

        ofstream e_file(expense_file);
        if (e_file.is_open())
        {
            e_file << total_bazar;
            e_file.close();
        }
    }

public:
    MessManager()
    {
        load_data();
    }

    ~MessManager()
    {
        save_data();
    }

    void add_member()
    {
        string name;
        cout << "Enter member name: ";
        getline(cin, name);

        if (members.count(name))
        {
            cout << "Error: Member already exists.\n";
            return;
        }

        double initial_dep = get_amount("Initial deposit: ");
        members[name] = {name, initial_dep, 0};
        cout << "Added " << name << " successfully.\n";
        save_data();
    }

    void add_deposit()
    {
        string name;
        cout << "Enter member name: ";
        getline(cin, name);

        if (!members.count(name))
        {
            cout << "Error: Member not found.\n";
            return;
        }

        double amount = get_amount("Amount to add: ");
        members[name].deposit += amount;
        cout << "Updated! New deposit for " << name << ": " << members[name].deposit << " Tk\n";
        save_data();
    }

    void correct_deposit()
    {
        string name;
        cout << "Enter member name: ";
        getline(cin, name);

        if (!members.count(name))
        {
            cout << "Error: Member not found.\n";
            return;
        }

        double amount = get_amount("Enter the corrected total deposit: ");
        members[name].deposit = amount;
        cout << "Corrected! New deposit for " << name << ": " << members[name].deposit << " Tk\n";
        save_data();
    }

    void add_meals()
    {
        string name;
        cout << "Enter member name: ";
        getline(cin, name);

        if (!members.count(name))
        {
            cout << "Error: Member not found.\n";
            return;
        }

        int count = (int)get_amount("Meals to add: ");
        members[name].meals += count;
        cout << "Updated! Total meals for " << name << ": " << members[name].meals << "\n";
        save_data();
    }

    void correct_meals()
    {
        string name;
        cout << "Enter member name: ";
        getline(cin, name);

        if (!members.count(name))
        {
            cout << "Error: Member not found.\n";
            return;
        }

        int count = (int)get_amount("Enter corrected total meals: ");
        members[name].meals = count;
        cout << "Corrected! Total meals for " << name << ": " << members[name].meals << "\n";
        save_data();
    }

    void add_bazar()
    {
        cout << "Current Total Bazar: " << total_bazar << " Tk\n";
        double amount = get_amount("Bazar amount to add: ");
        total_bazar += amount;
        cout << "Updated! New Total Bazar: " << total_bazar << " Tk\n";
        save_data();
    }

    void correct_bazar()
    {
        cout << "Current Total Bazar: " << total_bazar << " Tk\n";
        double amount = get_amount("Enter corrected total bazar expense: ");
        total_bazar = amount;
        cout << "Corrected! New Total Bazar: " << total_bazar << " Tk\n";
        save_data();
    }

    void generate_report()
    {
        if (members.empty())
        {
            cout << "No members in the database.\n";
            return;
        }

        int total_meals = 0;
        for (const auto &p : members)
        {
            total_meals += p.second.meals;
        }

        double meal_rate = (total_meals > 0) ? (total_bazar / total_meals) : 0.0;

        cout << "\n--------------------------------------------------------------\n";
        cout << "                      MONTHLY MESS REPORT                     \n";
        cout << "--------------------------------------------------------------\n";
        cout << "Total Bazar: " << fixed << setprecision(2) << total_bazar << " Tk\n";
        cout << "Total Meals: " << total_meals << "\n";
        cout << "Meal Rate:   " << meal_rate << " Tk/meal\n";
        cout << "--------------------------------------------------------------\n";

        cout << left << setw(15) << "Name"
             << setw(10) << "Meals"
             << setw(15) << "Deposit"
             << setw(15) << "Meal Cost"
             << "Status" << "\n";
        cout << string(62, '-') << "\n";

        for (const auto &p : members)
        {
            double cost = p.second.meals * meal_rate;
            double balance = p.second.deposit - cost;

            cout << left << setw(15) << p.second.name
                 << setw(10) << p.second.meals
                 << setw(15) << p.second.deposit
                 << setw(15) << cost;

            if (balance < 0)
            {
                cout << "Pay " << abs(balance) << " Tk";
            }
            else
            {
                cout << "Receive " << balance << " Tk";
            }
            cout << "\n";
        }
        cout << "--------------------------------------------------------------\n\n";
    }
};

void print_menu()
{
    cout << "\n=== Meal Management System ===\n";
    cout << "1. Add Member\n";
    cout << "2. Add Deposit\n";
    cout << "3. Correct Deposit\n";
    cout << "4. Add Meals\n";
    cout << "5. Correct Meals\n";
    cout << "6. Add Bazar Expense\n";
    cout << "7. Correct Bazar Expense\n";
    cout << "8. View Full Report\n";
    cout << "0. Save & Exit\n";
    cout << "Choice: ";
}

int main()
{
    MessManager mess;
    string input;
    int choice;

    while (true)
    {
        print_menu();
        getline(cin, input);

        try
        {
            choice = stoi(input);
        }
        catch (...)
        {
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            mess.add_member();
            break;
        case 2:
            mess.add_deposit();
            break;
        case 3:
            mess.correct_deposit();
            break;
        case 4:
            mess.add_meals();
            break;
        case 5:
            mess.correct_meals();
            break;
        case 6:
            mess.add_bazar();
            break;
        case 7:
            mess.correct_bazar();
            break;
        case 8:
            mess.generate_report();
            break;
        case 0:
            cout << "Saved data successfully. Exiting...\n";
            return 0;
        default:
            cout << "Invalid command.\n";
        }
    }
    return 0;
}
