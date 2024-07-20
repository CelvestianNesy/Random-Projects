#include <iostream>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> vec)
{
	out << "[ ";
	for (T elements : vec) 
	{
		out << elements << " ";
	}
	out << " ]";
	return out;
}

std::vector<int> properDivisorFinder(std::int64_t number)
{
	std::vector<int> properdiv = {};

	for (int divisor = 1; divisor < number; divisor++)
	{
		int rest = 0;

		if (number % divisor == 0)
		{
			properdiv.push_back(divisor);
		}
	}
	return properdiv;
}

std::vector<int> perfectNumberFinder(int range)
{
	std::vector<int> perfectnum = {};

	for (int number = 1; number < range; number++)
	{
		int sum = 0;
		std::vector<int> divisors = properDivisorFinder(number);
		for (int divisor : divisors)
		{
			sum += divisor;
		}
		if (sum == number)
		{
			perfectnum.push_back(number);
		}
	}
	return perfectnum;
}

int main()
{

	int range = 0;
	std::cout << "Search for perfect numbers: ";
	std::cin >> range;
	std::vector<int> perfectnum = perfectNumberFinder(range);
	std::cout << perfectnum;
}
