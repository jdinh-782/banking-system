#include "Account.hpp"
#include "Login.hpp"
#include "Balances.hpp"
#include "Transactions.hpp"


int invalidIntInput(int num1, int num2, int correctInput)
{
    while (std::cin.fail() || correctInput < num1 || correctInput > num2)
    {
        std::cout << "Invalid input! Enter again: ";
        std::cin.clear();
        Account::excess();
        std::cin >> correctInput;
    }
    return correctInput;
}


int main()
{
    int choice;
    std::string accountNumber;
    Account a;

    std::cout << "Do you have an account with us?\n"
                 "[1] Yes\n"
                 "[2] No\n"
                 "[3] Exit Program\n"
                 "Enter choice: ";
    std::cin >> choice;
    choice = invalidIntInput(1, 3, choice);

    if (choice == 1)
    {
        std::string email, password;

        std::cout << "\nEnter email address: ";
        std::cin >> email;

        std::cout << "Enter password: ";
        std::cin >> password;

        Login l(email, password);
        l.printInfo();

        accountNumber = l.returnAccountNumber();
    }
    else if (choice == 2)
    {
        a.setName();
        a.setPhoneNumber();
        a.setEmail();
        a.setPassword();
        a.setAccountNumber();
        a.saveToFile();
        accountNumber = a.getAccountNumber();

        std::cout << a;
    }
    else if (choice == 3)
    {
        std::cout << "\nHave a wonderful day!";
        exit(0);
    }

    Balances b(accountNumber);
    b.getBalance();
    b.saveBalanceToFile();

    Transactions t;

    do
    {
        std::cout << "\n\nWhat would you like to do today?\n"
                     "[1] Deposit\n"
                     "[2] Withdrawal\n"
                     "[3] Check Account Balance\n"
                     "[4] Exit Program\n"
                     "Enter choice: ";
        std::cin >> choice;
        choice = invalidIntInput(1, 4, choice);

        if (choice == 1)
        {
            b.depositBalance();

            if (b.successfulDeposit)
                t.transactDeposit(b.getDepositAmount());
        }
        else if (choice == 2)
        {
            b.withdrawBalance();

            if (b.successfulWithdrawal)
                t.transactWithdrawal(b.getWithdrawalAmount());
        }
        else if (choice == 3)
        {
            std::cout << b;
        }
        else if (choice == 4)
        {
            b.saveBalanceToFile();
            t.saveTransactions(b.getAccountNumber());
            break;
        }
        b.saveBalanceToFile();
    } while (true);

    std::cout << "\nHave a wonderful day!";

    return 0;
}
