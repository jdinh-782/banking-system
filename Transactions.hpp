#ifndef _TRANSACTIONS_HPP
#define _TRANSACTIONS_HPP

#include <vector>


class Transactions
{
private:
    std::vector<std::string> s;

public:
    Transactions();

    void transactDeposit(double deposit);
    void transactWithdrawal(double withdrawal);
    void saveTransactions(const std::string& accountNumber);
};

Transactions::Transactions()
{
    s.reserve(100);
}

void Transactions::transactDeposit(double deposit)
{
    std::string text = "\nYou made a DEPOSIT of " + std::to_string(deposit);
    s.push_back(text);
}

void Transactions::transactWithdrawal(double withdrawal)
{
    std::string text = "\nYou made a WITHDRAWAL of " + std::to_string(withdrawal);
    s.push_back(text);
}

void Transactions::saveTransactions(const std::string& accountNumber)
{
    std::ofstream ofs("transactions.txt");

    ofs << "Account number: " << accountNumber << std::endl;
    for (const auto& item : s)
    {
        ofs << item;
    }
    ofs.close();
}

#endif