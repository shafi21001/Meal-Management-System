#include <iostream>
#include <string>
#include <map>

using namespace std;

struct Member
{
    string name;
    double balance;
    int meals_consumed;
};

map<string, Member> members;

void add_member()
{
    string name;
    double balance;
    cout << "Enter member name: ";
    cin >> name;
    cout << "Enter initial balance: ";
    cin >> balance;
    members[name] = {name, balance, 0};
    cout << "Member added successfully!\n";
}

void add_money()
{
    string name;
    double amount;
    cout << "Enter member name: ";
    cin >> name;
    cout << "Enter amount to add: ";
    cin >> amount;
    members[name].balance += amount;
    cout << "Amount added successfully!\n";
}

void deduct_money()
{
    string name;
    double amount;
    cout << "Enter member name: ";
    cin >> name;
    cout << "Enter amount to deduct: ";
    cin >> amount;
    members[name].balance -= amount;
    cout << "Amount deducted successfully!\n";
}

void add_meals()
{
    string name;
    int meals;
    cout << "Enter member name: ";
    cin >> name;
    cout << "Enter number of meals to add: ";
    cin >> meals;
    members[name].meals_consumed += meals;
    cout << "Meals added successfully!\n";
}

void edit_meals()
{
    string name;
    int meals;
    cout << "Enter member name: ";
    cin >> name;
    cout << "Enter new number of meals: ";
    cin >> meals;
    members[name].meals_consumed = meals;
    cout << "Meals updated successfully!\n";
}

void view_history()
{
    string name;
    cout << "Enter member name: ";
    cin >> name;
    cout << "Name: " << members[name].name << endl;
    cout << "Balance: " << members[name].balance << endl;
    cout << "Meals consumed: " << members[name].meals_consumed << endl;
}

int main()
{
    int choice;
    do
    {
        cout << "----Meal Management System----\n";
        cout << "1. Add Member\n";
        cout << "2. Add Money\n";
        cout << "3. Deduct Money\n";
        cout << "4. Add Meals Consumed\n";
        cout << "5. Edit Meals Consumed\n";
        cout << "6. View Member History\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            add_member();
            break;
        case 2:
            add_money();
            break;
        case 3:
            deduct_money();
            break;
        case 4:
            add_meals();
            break;
        case 5:
            edit_meals();
            break;
        case 6:
            view_history();
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    }
    while (choice != 7);

    return 0;
}
