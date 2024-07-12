#include <iostream>
#include <vector>
#include <cmath>
#include <array>

std::array< std::array<char, 40>, 10> boardconstructor(int64_t height, int64_t width, std::array< std::array<char, 40>, 10> multiarray, int tool)
{
	
	for (int index = 0; index < height; index++)
	{
		if (tool == 1)
		{
			for (int indexinner = 0; indexinner < width; indexinner++)
			{
				multiarray[index][indexinner] = '-';
			}
		}
		else if (tool == 2) //debugging
		{
			for (int indexinner = 0; indexinner < width; indexinner++)
			{
				std::cout << multiarray[index][indexinner];
			}
			std::cout << "\n";
		}
	}

	return multiarray;
}


void boardrawer(std::array< std::array<char, 40>, 10> multiarray)
{
	for (int index = 9; index >= 0; index--)
	{
		for (int indexinner = 0; indexinner < 40; indexinner++)
		{
			std::cout << multiarray[index][indexinner];
		}
		std::cout << "\n";
	}
}


int main()
{
	std::array< std::array<char, 40>, 10> multiarray = {};
	multiarray = boardconstructor(10, 40, multiarray,1);
	int valid = 0;
	int validcontrolsum = 0;


	while (true)
	{
		system("cls");
		boardrawer(multiarray);
		if (valid == 1)
		{
			validcontrolsum = 1;
		}

		int horizontalaxis = -1;
		int verticalaxis = -1;
		

		while ((horizontalaxis < 0 or horizontalaxis >= 40) or (verticalaxis < 0 or verticalaxis > 10) )
		{
			
			horizontalaxis = 0;
			verticalaxis = 0;
			std::cout << "\n";

			std::cout << "Place your marker.";
			std::cout << "\n(Select index y value from 1-10): ";
			std::cin >> verticalaxis;
			std::cout << "\n(Select index x value from 1-40): ";
			std::cin >> horizontalaxis;
			
			horizontalaxis -= 1;
			verticalaxis -= 1;

			if ((horizontalaxis < 0 or horizontalaxis > 40) or (verticalaxis < 0 or verticalaxis > 10))
			{
				std::cout << "Invalid, try again.\n";
				
				
			}
			else
			{
				valid = 1;
			}
		}
		
		if (validcontrolsum == 1)
		{
			multiarray = boardconstructor(10, 40, multiarray, 1);
		}
		if (valid == 1)
		{
			multiarray[verticalaxis][horizontalaxis] = 'X';
			
		}
	}
}


