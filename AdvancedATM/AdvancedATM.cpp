#include <iostream>
#include <vector>
using namespace std;

struct People
{
    string name;
    string password; //These variable are users' details in this "bank"
    double balance = 0.0; 
};
class ATMACHINE {
private :
    string new_name;
    string new_password;    //These variable will be stored, as in a real ATM it must be stored to make a correct transaction.
    double new_balance = 0;//They are private so no other class can have access to these variables;
    bool loggedIn = false;
    vector<People> people;
public :
    void REGISTER_USERACCOUNT() {
        int restarter = 1; 
        while (restarter != 0) {                 //restarter is used to check if an user with same name has been found. 
            cout << "Please input your name:"; //If it has been found, it is set to 1, which it already is. 
            cin >> new_name;                    //If there has been no instance of an user with same name, restarter = 0, which breaks the loop. 
                                               //I will add unordered_map to improve efficiency of this part of the code later;

            if (people.size() == 0) break;
        
            for (size_t i = 0; i < people.size(); i++) {
                if (people[i].name == new_name) { 
                    cout << "Name already exists, please input another name. ";
                    i = people.size();
                }
                else restarter = 0;
            }

        }

        cout << "Please input your password:"; //Multiple users can use the same password. So no need for a loop.
        cin >> new_password; //I will add requirements later.

        while (new_balance < 100) { 
            cout << "Please input your initial deposit(must be at least 100 USD):";
            cin >> new_balance;
            if (new_balance < 100) cout << "The initial deposit must be at least 100 USD!!!";
        }
        People p; 
        p.name = new_name;
        p.password = new_password;
        p.balance = new_balance;

        people.push_back(p);
        loggedIn = true; //Using this boolean, after new_name, new_password and new_balance are initialized, will tell the rest of the app. that user's credentials and balance is stored..
    }

    void WITHDRAW_BALANCE() {
        int restarter = 1; //Same logic as above.

        if(loggedIn == false){ //As I have mentioned loggedIn is used for checking if credentials and balance are stored already.
            int peopleIndex; //If it is stored already than there is no need for another authorization process.
            while (restarter != 0) {//If it is not, than we ask for login credentials.
                restarter = 1;
                cout << "Your name please:";
                string input_name;
                cin >> input_name;
                for (int i = 0; i < people.size(); i++) {
                    if (people[i].name == input_name) restarter--;
                    peopleIndex = i;
                    break;
                }
            }
            restarter = 1;
            while (restarter != 0) {
                system("cls");
                restarter = 1;
                cout << "Hello " << people[peopleIndex].name << ". Your password please:";
                string input_password;
                cin >> input_password;
                if (people[peopleIndex].password == input_password) restarter--;
                else cout << "Wrong password, try again!";
                cin.get();
            }
            restarter = 1;
            while (restarter != 0) {
                cout << "Your current balance: " << people[peopleIndex].balance << endl;
                cout << "How much money would you like to withdraw?: ";
                double neededWithdrawal;
                cin >> neededWithdrawal;
                if (neededWithdrawal <= people[peopleIndex].balance) {
                    restarter = 0;
                    people[peopleIndex].balance -= neededWithdrawal;
                    cout << neededWithdrawal << " USD has been successfuly withdrawn from your account! Current balance: " << people[peopleIndex].balance << endl;
                }
            }
        }
        else 
        {
            restarter = 1;
            while (restarter != 0) {
                cout << "Your current balance: " << people[people.size()-1].balance << endl;
                cout << "How much money would you like to withdraw?: ";
                double neededWithdrawal;
                cin >> neededWithdrawal;
                if (neededWithdrawal <= people[people.size() - 1].balance) { //Checking if the user has enough balance to withdraw needed amount.
                    restarter = 0;
                    people[people.size() - 1].balance -= neededWithdrawal;
                    cout << neededWithdrawal << " USD has been successfuly withdrawn from your account! Current balance: " << people[people.size() - 1].balance << endl;
                }
            }
        }

    }

    void DEPOSIT_BALANCE() {
        if (loggedIn) { //Again, if user has just registered or logged in, there is no need for asking user credentials, we already have them.
            cout << "Your current balance: " << new_balance << endl;
            cout << "How much would you like to deposit in your bank account?:";
            double new_dep;
            cin >> new_dep;
            people[people.size() - 1].balance += new_dep;
            cout << "Success, your new balance is:" << people[people.size() - 1].balance << endl;
        }
        else 
        {
            int peopleIndex, restarter = 1;//In case the client is not logged in, we ask them to login.
            while (restarter != 0) {//This must be another function. I will add it later, when I add libraries for json.
                restarter = 1;
                cout << "Your name please:";
                string input_name;
                cin >> input_name;
                for (int i = 0; i < people.size(); i++) {
                    if (people[i].name == input_name) restarter--;
                    peopleIndex = i;
                    break;
                }
            }
            restarter = 1;
            while (restarter != 0) {
                restarter = 1;
                cout << "Hello " << people[peopleIndex].name << ". Your password please:";
                string input_password;
                cin >> input_password;
                if (people[peopleIndex].password == input_password) restarter--;
                else cout << "Wrong password, try again!";
                cin.get();
            }
                cout << "Your current balance: " << people[peopleIndex].balance << endl;
                cout << "How much money would you like to withdraw?: ";
                double new_deposit;
                cin >> new_deposit;
                people[peopleIndex].balance += new_deposit;
                cout << "Success! Your new balace is:" << people[peopleIndex].balance;
                cin.get();
                system("cls");
        }
    }
};


int main()
{
    ATMACHINE* atm = new ATMACHINE;
    int dial;
    int restarter = 1;
    while (restarter != 0) {
        cout << "If you want to register an account in our bank, dial 0. If you already have an account, please dial 1:";
        cin >> dial;
        if (dial == 0) { atm->REGISTER_USERACCOUNT(); restarter = 0; }
        else if (dial == 1) { restarter = 0; }
        else cout << "Wrong input! Try again!";
        cin.get();
    };
    restarter = 1;
    while (restarter != 0) {
        cout << "If you want to deposit to your balance, dial 1. If you want to withdraw from your balance, dial 0:";
        cin >> dial;
        if (dial == 0) { atm->WITHDRAW_BALANCE();}
        else if (dial == 1) { atm->DEPOSIT_BALANCE();}
        else cout << "Wrong input!!! Try again!";
        while (restarter != 0 ) {
            cout << "If you want to deposit or withdraw again dial 1. If not, dial 0:";
            cin >> dial;
            if (dial == 1) { restarter = 1; break; }
            else if (dial == 0) { restarter = 0; break; }
            else cout << "Wrong input, try again." << endl;
        }
    }
    delete atm; //As we use keywoard delete, we should have destructor in ATMACHINE class, which will be added if there is a need for it.
}
