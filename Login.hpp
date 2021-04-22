#ifndef _LOGIN_HPP
#define _LOGIN_HPP

#include "Account.hpp"
#include <vector>


class Login
{
private:
    Account a;
    std::string firstName, lastName, email, password, phoneNumber, accountNumber;

public:
    Login();
    Login(std::string emailInput, std::string passwordInput);

    void printInfo();
    std::string returnAccountNumber();
};


Login::Login()
{
    email = "";
    password = "";
    phoneNumber = "";
}

Login::Login(std::string emailInput, std::string passwordInput) : a(emailInput, passwordInput)
{
    std::ifstream ifs("accounts.txt");
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

    for (int i = 0; i < s.size(); i++)
    {
        if ((s[i] == "Email:" && s[i + 1] != emailInput) || (s[i] == "Password:" && s[i + 1] != passwordInput))
        {
            std::cout << "\nAccount not found in database.";
            exit(0);
        }
    }

    email = std::move(emailInput);
    password = std::move(passwordInput);

    //use variables to capture entire name input from txt file
    bool firstNameTemp = false;
    bool lastNameTemp = false;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == "*")
        {
            firstNameTemp = false;
            lastNameTemp = false;
        }

        if (i > 0)
        {
            if (firstNameTemp)
                firstName += s[i] + " ";

            if (s[i - 1] == "First" && s[i] == "name:")
                firstNameTemp = true;

            if (lastNameTemp)
                lastName += s[i] + " ";

            if (s[i - 1] == "Last" && s[i] == "name:")
                lastNameTemp = true;

            if (s[i - 1] == "Phone" && s[i] == "number:")
                phoneNumber += s[i + 1] + " ";

            if (s[i - 1] == "Account" && s[i] == "number:")
                accountNumber += s[i + 1];
        }
    }
    a.setName(firstName, lastName);
    a.setPhoneNumber(phoneNumber);
    a.setAccountNumber(accountNumber);
}

void Login::printInfo()
{
    std::cout << a;
}

std::string Login::returnAccountNumber()
{
    return a.getAccountNumber();
}

#endif