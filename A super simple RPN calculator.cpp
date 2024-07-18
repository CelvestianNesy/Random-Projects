#include <iostream>
#include <string>
#include <vector>
std::vector<char> inputpanel()
{
	std::vector<char> characters = {};
	std::string input = "";
	std::getline(std::cin, input);
	for (int index = 0; index < input.length(); index++)
	{
		characters.push_back(input.at(index));
	}
	return characters;
}

bool errorchecker(std::vector<char>& characters)
{
	int lparanthesis = 0;
	int rparanthesis = 0;
	for (char character : characters)
	{
		switch (character)
		{
		case '(':
			lparanthesis += 1;
			break;
		case ')':
			rparanthesis += 1;
			break;
		case '*':
		case '/':
		case '+':
		case '-':
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			break;
		default:
			return false;
		}

	}
	int sum = lparanthesis + rparanthesis;
	if (sum % 2 != 0)
	{
		return false;
	}
	return true;
}

int chartoint(char integerchar)
{
	int integer = integerchar - '0';
	return integer;
}

auto operation(char operatorChar, std::vector<double>& operands)
{
	double result = 0;
	int counter = 0;
	for (int operand : operands)
	{
		counter += 1;
		if (counter == 1)
		{
			result = operand;
		}
		else
		{
			switch (operatorChar)
			{
			case '+':
				result += operand;
				break;
			case '-':
				result -= operand;
				break;
			case '*':
				result *= operand;
				break;
			case '/':
				result /= operand;
				break;

			default:
				break;
			}
		}
	}
	std::cout << result;
}


void operationsection(std::vector<char>& characters)
{
	std::vector<double> operands = {};

	for (char char1 : characters)
	{
		switch (char1)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			break;
		default:
			operands.push_back(chartoint(char1));
		}
	}
	for (char char1 : characters)
	{
		switch (char1)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			operation(char1, operands);
			break;
		default:
			break;
		}
	}
}



int main()
{
	std::cout << "Welcome to the RPN calculator!" << "\n";
	while(true)
	{
		std::cout << "Insert:  ___\b\b\b";
		std::vector<char> characters = inputpanel();
		bool valid = errorchecker(characters);
		if (valid == false)
		{
			std::cout << "Syntax error!";
			break;
		}
		operationsection(characters);
		std::cout << "\n";
	}
}#include <iostream>
#include <string>
#include <vector>
std::vector<char> inputpanel()
{
	std::vector<char> characters = {};
	std::string input = "";
	std::getline(std::cin, input);
	for (int index = 0; index < input.length(); index++)
	{
		characters.push_back(input.at(index));
	}
	return characters;
}

bool errorchecker(std::vector<char>& characters)
{
	int lparanthesis = 0;
	int rparanthesis = 0;
	for (char character : characters)
	{
		switch (character)
		{
		case '(':
			lparanthesis += 1;
			break;
		case ')':
			rparanthesis += 1;
			break;
		case '*':
		case '/':
		case '+':
		case '-':
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			break;
		default:
			return false;
		}

	}
	int sum = lparanthesis + rparanthesis;
	if (sum % 2 != 0)
	{
		return false;
	}
	return true;
}

int chartoint(char integerchar)
{
	int integer = integerchar - '0';
	return integer;
}

auto operation(char operatorChar, std::vector<double>& operands)
{
	double result = 0;
	int counter = 0;
	for (int operand : operands)
	{
		counter += 1;
		if (counter == 1)
		{
			result = operand;
		}
		else
		{
			switch (operatorChar)
			{
			case '+':
				result += operand;
				break;
			case '-':
				result -= operand;
				break;
			case '*':
				result *= operand;
				break;
			case '/':
				result /= operand;
				break;

			default:
				break;
			}
		}
	}
	std::cout << result;
}


void operationsection(std::vector<char>& characters)
{
	std::vector<double> operands = {};

	for (char char1 : characters)
	{
		switch (char1)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			break;
		default:
			operands.push_back(chartoint(char1));
		}
	}
	for (char char1 : characters)
	{
		switch (char1)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			operation(char1, operands);
			break;
		default:
			break;
		}
	}
}



int main()
{
	std::cout << "Welcome to the RPN calculator!" << "\n";
	while(true)
	{
		std::cout << "Insert:  ___\b\b\b";
		std::vector<char> characters = inputpanel();
		bool valid = errorchecker(characters);
		if (valid == false)
		{
			std::cout << "Syntax error!";
			break;
		}
		operationsection(characters);
		std::cout << "\n";
	}
}
