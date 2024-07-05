#include <cstdint>
#include <iostream>

namespace mathFunctions
{
	long double iexp(std::int64_t base, std::int64_t exponentiation)
	{
		std::int64_t localExponent = (exponentiation < 0) ? ( -1*exponentiation ): exponentiation;
		
		std::int64_t expint = (exponentiation == 0)?1:base;
		long double expfloat = (exponentiation < 0) ? (1/static_cast<long double>(base)) : 1;


		long double localBase = (exponentiation < 0) ? expfloat : expint; 
		long double product = localBase;
		
		for (int64_t iteration = 1; iteration < localExponent; iteration++)
		{

			product *= localBase;

		}
		


		return product;

	}
}






int main()
{
	long double product = mathFunctions::iexp(2, -3);

	std::cout << product;

	return 0;
}
