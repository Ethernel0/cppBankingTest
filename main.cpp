#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>

class bankAccount{
public:
    void showMenu();
    void create_account();
    void account_information();
    void modify();
                                    // Declaring Class methods
    void deposit(double&);
    void withdraw(double&);

    double return_balance();
    int return_account_number();


private:
    int accountID;                                          // Account ID
    double account_balance{0};                              // Account Balance
    std::string  account_first_name, account_last_name;     // Account Holder Name
    unsigned int account_pin;                               // Account PIN
    bool account_created{false};                            // Account Created
};


void bankAccount::showMenu(){
    int user_choice;
    double deposit_amount, withdraw_amount;

    std::cout << "\nWelcome to the bank account system" << std::endl;
    std::cout << "1. Create account" << std::endl;
    std::cout << "2. Show account" << std::endl;
    std::cout << "3. Modify account" << std::endl;
    std::cout << "4. Deposit" << std::endl;
    std::cout << "5. Withdraw" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> user_choice;

    switch (user_choice){
        case 1:
        {
            create_account();
            break;
        }
        case 2:
        {
            if (account_created){
                account_information();
            }
            else{
                std::cout << "You need to create an account first" << std::endl;
                showMenu();
            }
            break;
        }
        case 3:
        {
            if (account_created){
                modify();
            }
            else{
                std::cout << "You need to create an account first" << std::endl;
                showMenu();
            }
            break;
        }
        case 4:
        {
            if (account_created)
            {
                std::cout << "Enter the amount you want to deposit: ";
                std::cin >> deposit_amount;
                deposit(deposit_amount);
            }
            else
            {
                std::cout << "You need to create an account first" << std::endl;
                showMenu();
            }
        }
        case 5:
        {
            if (account_created)
            {
                std::cout << "Enter the amount you want to withraw: ";
                std::cin >> withdraw_amount;
                withdraw(withdraw_amount);
            }
            else
            {
                std::cout << "You need to create an account first" << std::endl;
                showMenu();
            }
        }
    }
}
void bankAccount::create_account ()
{

    bankAccount acc;
    std::ofstream out_file;
    out_file.open("account.dat", std::ios::binary | std::ios::app);

    std::cout << "  ********** ACCOUNT CREATION ********** \n";

    srand(time(NULL));
    accountID = rand() % 100000;
    std::cout << "Your account ID is: " << accountID << "\n";

    std::cout << "Enter your first name: ";
    std::cin >> account_first_name;

    std::cout << "Enter your last name: ";
    std::cin >> account_last_name;

    std::cout << "Enter your pin: ";
    std::cin >> account_pin;

    std::cout << "Your account was successfully created!\n";
    account_created = true;

    out_file.write(reinterpret_cast<const char *>(&acc), sizeof(bankAccount));
    out_file.close();

    Sleep(2000);
    showMenu();
}
void bankAccount::account_information ()
{
    std::cout << "  ********** BALANCE ********** \n";
    std::cout << "Account ID: " << bankAccount::return_account_number() << "\n";
    std::cout << "Account holder name: " << account_first_name << " " << account_last_name << "\n";
    std::cout << "Account account_balance: " << bankAccount::return_balance() << "\n";
    Sleep(2000);
    showMenu();
}
void bankAccount::modify ()
{
    int user_choice{0};
    std::cout << "  ********** MODIFY ACCOUNT ********** \n";
    std::cout << "Account ID: " << accountID << "\n";
    std::cout << "Current first name: " << account_first_name << "\n";
    std::cout << "Current last name: " << account_last_name << "\n";
    std::cout << "Current pin: " << account_pin << "\n";
    std::cout << "  *** *** *** *** \n";
    std::cout << "1. First name \n";
    std::cout << "2. Last name \n";
    std::cout << "3. Pin \n";
    std::cout << "4. Exit \n";
    std::cin >> user_choice;

    switch (user_choice)
    {
        case 1:
            std::cout << "Enter new first name: ";
            std::cin >> account_first_name;
            std::cout << "New first name: " << account_first_name << "\n";
            Sleep(2000);
            showMenu();
            break;
        case 2:
            std::cout << "Enter new last name: ";
            std::cin >> account_last_name;
            std::cout << "New Last name: " << account_last_name << "\n";
            Sleep(2000);
            showMenu();
            break;
        case 3:
            std::cout << "Enter new pin: ";
            std::cin >> account_pin;
            std::cout << "New pin: " << account_pin << "\n";
            Sleep(2000);
            showMenu();
            break;
        case 4:
            showMenu();
    }
}
void bankAccount::deposit (double &amount)
{
    account_balance += amount;
    std::cout << "Deposit successful! \n";
    std::cout << "New account_balance: " << account_balance << "\n";
    Sleep(2000);
    showMenu();
}
void bankAccount::withdraw (double &withdraw_amount)
{
    account_balance -= withdraw_amount;
    std::cout << "Withdraw successful! \n";
    std::cout << "New account_balance: " << account_balance << "\n";
    Sleep(4000);
    showMenu();
}
double bankAccount::return_balance ()
{
    return account_balance;
}
int bankAccount::return_account_number ()
{
    return accountID;
}

void write_account();
void display_account_details(int);
void modify_account(int);
void delete_account(int);
void display_all_accounts();
void id_deposit_withdraw(int accID, double &deposit_amount, double &withdraw_amount);

int main ()
{
    bankAccount bank;
    bank.showMenu();
}

void write_account()
{
    bankAccount acc;
    std::ofstream out_file;
    out_file.open("account.dat", std::ios::binary | std::ios::app);
    acc.create_account();

    out_file.write(reinterpret_cast<const char *>(&acc), sizeof(bankAccount));
    out_file.close();
}

void display_account_details(int n)
{
    bankAccount acc;
    bool flag{false};

    std::ifstream inFile;
    inFile.open("account.dat", std::ios::binary);

    if (!inFile)
    {
        std::cout << "Unable to open/find Data file";
        return;
    }
    std::cout << "\n Balance Details\n";

    while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(bankAccount)))
    {
        if(acc.return_account_number()==n)
        {
            acc.account_information();
            flag = true;
        }
    }
    inFile.close();
    if(flag==false){std::cout << "\n Account number does not exist";}
}

void modify_account(int n)
{
    bool found{false};
    bankAccount acc;
    std::fstream  File;
    File.open("account.dat", std::ios::binary | std::ios::in | std::ios::out);

    if (!File)
    {
        std::cout << "Unable to open/find Data file";
        return;
    }
    while(!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *> (&acc), sizeof (bankAccount));
        if (acc.return_account_number()==n)
        {
            acc.account_information();
            std::cout << "\n\n Enter new Details of account" << std::endl;
            acc.modify();
            int pos=(-1)*static_cast<int>(sizeof (bankAccount));
            File.seekp(pos, std::ios::cur);
            File.write(reinterpret_cast<char *> (&acc), sizeof (bankAccount));
            std::cout << "\n\n Record updated";
            found = true;
        }
    }
    File.close();
    if (found==false){std::cout << "\n\n record not found";}
}

void delete_account(int n)
{
    bankAccount acc;
    std::ifstream inFile;
    std::ofstream outFile;
    inFile.open("account.dat", std::ios::binary);

    if (!inFile)
    {
        std::cout << "Unable to open the file";
        return;
    }
    outFile.open("Temp.dat", std::ios::binary);
    inFile.seekg(0, std::ios::beg);

    while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(bankAccount)))
    {
            if(acc.return_account_number()!=n)
            {
                outFile.write(reinterpret_cast<char*> (&acc), sizeof (bankAccount));
            }

    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    std::cout << "Record Deleted";
}

void display_all()
{
    bankAccount acc;
    std::ifstream inFile;
    inFile.open("account.dat",std::ios::binary);
    if(!inFile)
    {
        std::cout<<"File could not be open !! Press any Key...";
        return;
    }
    while(inFile.read(reinterpret_cast<char *> (&acc), sizeof(bankAccount)))
    {
    }
    inFile.close();
}