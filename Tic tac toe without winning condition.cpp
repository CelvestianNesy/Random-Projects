#include <iostream>
#include <vector>
void boardrawer(std::vector<char> row1, std::vector<char> row2, std::vector<char> row3)
{
	std::vector<std::vector<char>> grid{ row1,row2,row3 };
	for (std::vector<char> rows : grid)
	{
		for (char element : rows)
		{
			std::cout << element;
		}
		std::cout << "\n";
	}
}

int errorchecker(int colum,std::vector<int>takencolums)
{
	for (int element : takencolums)
	{
		int error = 1;
		if (colum == element)
		{
			std::cout << "Error! Position already taken, cheater! \n";
			return error;
		}
	}
}

int inputvalidation(int colum, int row)
{
	int error = 1;
	if (colum > 3 or colum < 0)
	{
		std::cout << "Invalid!\n";
		return error;
	}
	if (row > 3 or row < 0)
	{
		std::cout << "Invalid!\n";
		return error;
	}
	else
	{
		return 0;
	}

}

int main()
{
	std::cout << "Welcome to tic tac toe, player 1 starts with(x) and player 2 is (o).\n";
	int turn = 1;
	bool running = true;
	std::vector<char> row1{ '-', '-' ,'-' };
	std::vector<char> row2{ '-', '-' ,'-' };
	std::vector<char> row3{ '-', '-' ,'-' };
	std::vector<int>takencolums1;
	std::vector<int>takencolums2;
	std::vector<int>takencolums3;
	while (running)
	{
		boardrawer(row1, row2, row3);
		int error = 0;
		int row = 0;
		int colum = 0;
		std::cout << "Player " << turn << "'s turn:\n";
		std::cout << "Insert x in row(1-3): ";
		std::cin >> row;
		std::cout << "Insert x in colum(1-3): ";
		std::cin >> colum;
		error = inputvalidation(colum, row);
		if (error == 1)
		{
			continue;
		}
		colum -= 1;
		switch (row)
		{
		case 1:
			error = errorchecker(colum, takencolums3);
			if (error == 1)
			{
				continue;
			}
			row3[colum] = (turn == 1) ? 'x' : 'o';
			takencolums3.push_back(colum);
			break;
		case 2:
			error = errorchecker(colum, takencolums2);
			if (error == 1)
			{
				continue;
			}
			row2[colum] = (turn == 1) ? 'x' : 'o';
			takencolums2.push_back(colum);
			break;
		case 3:
			error = errorchecker(colum, takencolums1);
			if (error == 1)
			{
				continue;
			}
			row1[colum] = (turn == 1) ? 'x' : 'o';
			takencolums1.push_back(colum);
			break;
		}
		if (turn == 2)
		{
			turn = 1;
			continue;
		}
		turn = turn + 1;
	}
}
