// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <cmath>

void primedivisorfinder(int64_t range, int64_t number, int64_t targetNumber)
{
    int restZero = 0;
    std::vector<int64_t> primes;
    std::vector<int64_t> primesNew;
    for (int64_t rangescan = 1; rangescan <= range; rangescan++)
    {
        int64_t rest = number % rangescan;

        if (rest == 0)
        {
            restZero += 1;
        }

    }
    

    if (restZero == 2)
    {
        primes.push_back(number);
        
    }

    

    for (int64_t number : primes)
    {
        int64_t rest1 = targetNumber % number;
        if (rest1 == 0)
        {
            primesNew.push_back(number);
        }
    }


    for (int64_t PrimesNew1 : primesNew)
    {
        std::cout << PrimesNew1 << "\n";
    }

}

void program()
{
    int64_t numberTarget = 0;
    std::cout << "Insert number here to know it's prime factors: ";
    std::cin >> numberTarget;

    if (numberTarget < 0)
    {
        std::cout << "Invalid number, please try again!";
    }

    for (int64_t number = 0; number <= numberTarget; number++)
    {
        primedivisorfinder(number, number, numberTarget);
    }
}


int main()
{
    program();

    return 0;
}
