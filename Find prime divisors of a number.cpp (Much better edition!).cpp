#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>

template <typename R>
std::ostream& operator<<(std::ostream& out, const std::vector<R>& vec)
{
	out << "[ ";
	for (R element : vec)
	{
		out << element << " ";
	}
	out << "]";
	return out;
}

template <typename T>
T primeNumberFinder(const T& number)
{
	T rest = 0;
	T zeroRest = 0;
	for (T numberIndex = 1; numberIndex <= number; numberIndex++)
	{
		rest = number % numberIndex;
		if (rest == 0)
		{
			zeroRest += 1;
		}
	}
	if (zeroRest == 2)
	{
		return number;
	}
	else
		return 0;
}

template <typename T>
std::vector<T> primeCollector(T& numberTarget)
{
	std::vector<T> primes = {};

	for (T number = 2; number <= numberTarget; number++)
	{
		T primeNumber = primeNumberFinder(number);
		if (primeNumber != 0)
		{
			primes.push_back(primeNumber);
		}
	}
	return primes;
}

template <typename T>
std::vector<T> primeDivisorFinder(T& numberTarget, const std::vector<T>& primes)
{
	std::vector<T> primesNew = {};
	int rest = -1;

	for (T primeNumber : primes)
	{
		rest = numberTarget % primeNumber;

		if (rest == 0)
		{
			primesNew.push_back(primeNumber);
		}

	}

	return primesNew;

}

void menu()
{
	int64_t numberTarget = -1;

	while (numberTarget < 0)
	{
		std::cout << "Select number to check for prime divisors:";
		std::cin >> numberTarget;
		if (numberTarget < 0) 
		{
			std::cout << "Invalid number. Prime divisors must be positive. \n";
		}
	}
	std::vector<int64_t>primes = primeCollector(numberTarget);
	std::vector<int64_t>newPrimes = primeDivisorFinder(numberTarget, primes);
	std::cout << newPrimes;
}

int main()
{
	menu();
}

