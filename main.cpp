#include "Account.hpp"


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

    std::cout << "Do you have an account with us?\n"
                 "[1] Yes\n"
                 "[2] No\n"
                 "Enter choice: ";
    std::cin >> choice;
    choice = invalidIntInput(1, 2, choice);

    if (choice == 2)
    {
        Account a;
        a.setName();
        a.setPhoneNumber();
        a.setEmail();
        a.setPassword();

        std::cout << a;
    }


    return 0;
}
