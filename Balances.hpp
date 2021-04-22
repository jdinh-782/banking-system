#ifndef _BALANCES_HPP
#define _BALANCES_HPP

#include "Account.hpp"
#include <iomanip>
#include <utility>


class Balances
{
private:
    Account a;
    double balance, withdrawal, deposit;
    std::string accountNumber;

public:
    Balances();
    explicit Balances(std::string accountNumberInput);

    bool successfulDeposit = false;
    bool successfulWithdrawal = false;

    void getBalance();
    void depositBalance();
    void withdrawBalance();
    void saveBalanceToFile();

    double getWithdrawalAmount() const;
    double getDepositAmount() const;

    std::string getAccountNumber();

    friend std::ostream& operator << (std::ostream& outs, const Balances& b);
};

Balances::Balances()
{
    balance = 0.00;
    withdrawal = 0.00;
    deposit = 0.00;
    accountNumber = a.getAccountNumber();

    std::ofstream ofs("balances.txt");
    ofs << " ";
    ofs.close();
}

Balances::Balances(std::string accountNumberInput)
{
    balance = 0.00;
    withdrawal = 0.00;
    deposit = 0.00;
    accountNumber = std::move(accountNumberInput);
}

void Balances::getBalance()
{
    std::ifstream ifs("balances.txt");
    if (ifs.fail())
    {
        std::cout << "\nDatabase not found!";
        exit(0);
    }

    std::string text;
    std::vector<std::string> s;
    while (ifs >> text)
    {
        s.push_back(text);
    }
    ifs.close();

    accountNumber = s[2];
    balance = std::stof(s[6]);
}

void Balances::depositBalance()
{
    std::cout << "\nEnter deposit amount: ";
    std::cin >> deposit;

    if (deposit >= 10000)
    {
        std::cout << "Deposit exceeds maximum amount of $10,000.";
        successfulDeposit = false;
        return;
    }
    else if (deposit < 0)
    {
        std::cout << "Deposit cannot be negative.";
        successfulDeposit = false;
        return;
    }
    balance += deposit;
    successfulDeposit = true;
}

void Balances::withdrawBalance()
{
    std::cout << "\nEnter withdrawal amount (whole integers only): ";
    std::cin >> withdrawal;

    if (withdrawal != static_cast<int>(withdrawal))
    {
        std::cout << "Withdrawal must be whole integers.";
        successfulWithdrawal = false;
        return;
    }
    if (withdrawal > balance)
    {
        std::cout << "Withdrawal exceeds balance.";
        successfulWithdrawal = false;
        return;
    }
    if (withdrawal < 0)
    {
        std::cout << "Withdrawal cannot be negative.";
        successfulWithdrawal = false;
        return;
    }
    balance -= withdrawal;
    successfulWithdrawal = true;
}

void Balances::saveBalanceToFile()
{
    std::ofstream ofs("balances.txt");

    ofs << std::fixed << std::showpoint << std::setprecision(2);
    ofs << "Account number: " << accountNumber << " *\nBalance ($): " << balance;
    ofs.close();
}

double Balances::getWithdrawalAmount() const
{
    return withdrawal;
}

double Balances::getDepositAmount() const
{
    return deposit;
}

std::string Balances::getAccountNumber()
{
    return accountNumber;
}

std::ostream& operator << (std::ostream &outs, const Balances& b)
{
    outs << std::fixed << std::showpoint << std::setprecision(2);
    outs << "\nYour total account balance is $" << b.balance << " (" << b.accountNumber << ").";
    return outs;
}




#endif