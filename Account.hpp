#ifndef _ACCOUNT_HPP
#define _ACCOUNT_HPP

#include <iostream>
#include <utility>
#include <fstream>
#include <ctime>


class Account
{
private:
    std::string firstName, lastName, phoneNumber, email, password, accountNumber;

public:
    Account();
    Account(std::string emailInput, std::string passwordInput);

    void setName();
    void setName(std::string loginFirstName, std::string loginLastName); //set name from login
    void setPhoneNumber();
    void setPhoneNumber(std::string phoneNumberInput);
    void setEmail();
    void setPassword();
    void setAccountNumber();
    void setAccountNumber(std::string accountNumberInput);
    void saveToFile();

    static void excess();

    std::string checkEmail();
    std::string checkPhoneNumber();
    std::string getAccountNumber();

    bool recursiveCheckPhoneNumber(int index);

    friend std::ostream& operator << (std::ostream& outs, const Account& a);
};


Account::Account()
= default;

Account::Account(std::string emailInput, std::string passwordInput)
{
    email = std::move(emailInput);
    password = std::move(passwordInput);
}

void Account::excess()
{
    char c;

    do
    {
        std::cin.get(c);
    } while (c != '\n');
}

void Account::setName()
{
    std::cin.ignore();
    std::cout << "\nEnter first name: ";
    std::getline(std::cin, firstName);

    std::cout << "\nEnter last name: ";
    std::getline(std::cin, lastName);
}

void Account::setPhoneNumber()
{
    std::cout << "\nEnter a phone number to be associated with this account (###-###-####): ";
    std::getline(std::cin, phoneNumber);
    phoneNumber = checkPhoneNumber();
}

std::string Account::checkPhoneNumber()
{
    //check if phone number size/format is valid (###-###-####)
    do
    {
        if (recursiveCheckPhoneNumber(0))
            break;

        std::cout << "The inputted phone number is not valid! Enter again: ";
        std::cin.clear();
        excess();
        std::cin >> phoneNumber;
    } while (true);

    return phoneNumber;
}

bool Account::recursiveCheckPhoneNumber(int index)
{
    if (phoneNumber.size() != 12)
        return false;

    if (index == phoneNumber.size())
        return true;

    //check if at index 3 and 7 that the character is a '-'
    if (index == 3 || index == 7)
    {
        if (phoneNumber[index] == 45)
        {
            return recursiveCheckPhoneNumber(index + 1);
        }
        return false;
    }

    //check if character is a valid integer
    if ((phoneNumber[index] > 47 && phoneNumber[index] < 58))
        return recursiveCheckPhoneNumber(index + 1);

    return false;
}

void Account::setEmail()
{
    std::cout << "\nEnter an email address: ";
    std::cin >> email;
    checkEmail();
}

std::string Account::checkEmail()
{
    do
    {
        std::string s;
        //supported emails are @gmail, @yahoo
        if (email.size() >= 11 && (email.find(' ') == std::string::npos))
        {
            for (unsigned int i = email.size() - 10; i < email.size(); i++)
            {
                s += email[i];
            }
            if (s == "@gmail.com" || s == "@yahoo.com")
                break;
        }

        std::cout << "The inputted email address is not valid! Enter again: ";
        std::cin.clear();
        Account::excess();
        std::cin >> email;
    } while (true);

    return email;
}

void Account::setPassword()
{
    std::cout << "\nEnter a password: ";
    std::cin >> password;
}

void Account::setAccountNumber()
{
    srand(time(nullptr));
    int num;

    for (int i = 0; i < 10; i++)
    {
        num = 1 + rand() % 9;
        accountNumber += std::to_string(num);
    }
}

void Account::saveToFile()
{
    std::ofstream ofs("accounts.txt");

    ofs << "First name: " << firstName << " *\nLast name: " << lastName << " *\nPhone number: "
        << phoneNumber << " *\nEmail: " << email << " *\nPassword: " << password << " *\nAccount number: "
        << accountNumber;
    ofs.close();
}

std::ostream& operator << (std::ostream&outs, const Account& a)
{
    outs << "\nFirst name: " << a.firstName << "\nLast name: " << a.lastName << "\nPhone number: "
         << a.phoneNumber << "\nEmail: " << a.email << "\nPassword: " << a.password << "\nAccount number: "
         << a.accountNumber;

    return outs;
}

void Account::setName(std::string loginFirstName, std::string loginLastName)
{
    firstName = std::move(loginFirstName);
    lastName = std::move(loginLastName);
}

void Account::setPhoneNumber(std::string phoneNumberInput)
{
    phoneNumber = std::move(phoneNumberInput);
}

void Account::setAccountNumber(std::string accountNumberInput)
{
    accountNumber = std::move(accountNumberInput);
}

std::string Account::getAccountNumber()
{
    return accountNumber;
}


#endif