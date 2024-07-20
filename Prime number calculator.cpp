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

std::vector<int> primenumberGen(std::int64_t range)
{
	std::vector<int> primes;
	for (std::int64_t number = 1; number <= range; number++)
	{
		int rest = 0;
		int restzero = 0;


		for (int divisor = 1; divisor <= number; divisor++)
		{
			
			rest = number % divisor;
		
			if (rest == 0)
			{
				restzero += 1;
			}
		}
		if (restzero == 2)
		{
			primes.push_back(number);
		}
	}

	return primes;
}



int main()
{
	int range = 0;
	std::cout << "Insert maximum value to search for prime numbers: "; 
	std::cin >> range;
	std::cout << "\n";
	std::vector<int> r = primenumberGen(range);
	std::cout << r;
	
	
	
}
