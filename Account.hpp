#ifndef _ACCOUNT_HPP
#define _ACCOUNT_HPP

#include <iostream>


class Account
{
private:
    std::string firstName, secondName, phoneNumber, email, password;

public:
    Account();

    void setName();
    void setPhoneNumber();
    void setEmail();
    void setPassword();

    static void excess();

    std::string checkEmail();

    std::string checkPhoneNumber();
    bool recursiveCheckPhoneNumber(int index);

    friend std::ostream& operator << (std::ostream& outs, const Account& a);
};


Account::Account()
= default;

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
    std::getline(std::cin, secondName);
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

std::ostream& operator << (std::ostream&outs, const Account& a)
{
    outs << "\nFirst name: " << a.firstName << "\nLast name: " << a.secondName << "\nPhone number: "
              << a.phoneNumber << "\nEmail: " << a.email << "\nPassword: " << a.password;

    return outs;
}


#endif