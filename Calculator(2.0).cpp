#include <iostream>
#include <vector>
#include <string>

template <typename T>
double calc(char chr, T val1,T val2)
{
    
    switch(chr)
    {
        case '+':
        return val1+val2;
        case '-':
        return val1-val2;
        case '*':
        return val1*val2;
        case '/':
        return val1/static_cast<double>(val2);
        case '%':
        return val1%val2;
        
    }
     
}

long int iexp(int base,int power)
{
    long int result = base;
   if (power == 0)
    {
        result = 1;
        return result;
    }
    
    for (int exp = 0 ; exp < power-1 ; exp++)
    {
        result *= base;
    }
    return result;
}

auto inputhandler()
{
     
    std::vector<char> input; 
    std::string unf = ""; 
    std::cout << "Calculate: ";
    std::getline(std::cin >> std::ws,unf);
    
    for (const char character : unf)
    {
        if (character != ' ')
        {
        input.push_back(character);
        }
    }
   return input;
    
}

bool errorchecker(std::vector<char> input)
{
    int opcount = 0;
for (char character : input)
    {
        switch(character)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        opcount += 1;
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
        std::cout << "Invalid operator";
        std::cout << "\n";
        return false;
        }
    }
    if (opcount > 1 or opcount == 0)
    {
        std::cout << "This calculator supports one operator per     calculation.\n\n";
        return false;
    }
    
    return true;
}

template<typename T>
void calculator(std::vector<T> input)
{ 
    int result1 = 0;
    int result2 = 0;
    int sum = 0;
    int chrdigit = 0;
    int number = 0;
    int anchor = 0;
    int anchor2 = 0;
    long int counter = 0;
    
    for (char chr : input)
    {
        switch (chr)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        anchor = counter; // operator loc
        anchor2 = counter-1; // bef op
        break;
        default:
        break;
        }
        counter += 1;
    }
    
    for (int index = anchor2; index >= 0; index--)
    {
       result1 += (input[index]-'0') * iexp(10,(anchor2-index));
       
    }
    
    for (int index = anchor+1; index < input.size(); index++)
    {
       result2 += (input[index]-'0') * iexp(10, (input.size())-index-1);
    }
    
    double result = calc(input[anchor],result1,result2);
    
    std::cout << "Result: ";
    std::cout << result;
    std::cout << "\n"; 
}


int main()
{
    while (true)
    {
       auto cleaninput = inputhandler();
       bool noerror = errorchecker(cleaninput);
        
       if (noerror == false)
        {
           continue; 
        }
        
        calculator(cleaninput);
    }
     return 0;
}
    
