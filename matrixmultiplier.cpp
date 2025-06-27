
#include<iostream>
#include<vector>

#include<format>


struct matrix
{
public:
	std::int64_t dim_m; //Rows
	std::int64_t dim_n; //Columns
	std::vector<std::vector<long double>> matrix;

};


void dataPacker(matrix& inputMatrix)
{
	
	long double numberInput;
	

	for (int rowNr = 0; rowNr < inputMatrix.dim_m; rowNr++)
	{
		std::cout << std::format("\n\nRow {}: \n\n", rowNr+1);

		inputMatrix.matrix.push_back({ });

		for (int colNr = 0; colNr < inputMatrix.dim_n; colNr++)
		{
		

			
			std::cin >> numberInput;

			
			inputMatrix.matrix[rowNr].push_back(numberInput);
			
			
		}
	}

}

matrix matrixMultiplier(matrix& A, matrix& B)
{

	long double dotproduct = 0;
	int colNr = 0;
	matrix F;

	for (int rowNr = 0; rowNr < A.dim_m; rowNr++) //Pre initialize vector
	{
		F.matrix.push_back({ });
	}

	
	for (int i = 0; i < A.dim_m; ++i) 
	{
		for (int j = 0; j < B.dim_n; ++j)
		{
			dotproduct = 0;

			for (int k = 0; k < A.dim_n; ++k)
			{
				dotproduct += A.matrix[i][k] * B.matrix[k][j];
			}

			F.matrix[i].push_back(dotproduct);
		}

	}
		

	F.dim_m = A.dim_m;
	F.dim_n = B.dim_n;

	return F;

}


void display(matrix& input)
{

	std::cout << "\n\n";

	
	for (int j = 0; j < input.dim_m; ++j)
	{
		std::cout << "[";

		for (int k = 0; k < input.dim_n; ++k)
		{
			std::cout << " " << input.matrix[j][k] << " ";
		}
		std::cout << "]\n";

	}

}

int main()
{
	matrix A;
	std::string error;
	matrix B;

	bool waitingForUserInput = true;
	while (waitingForUserInput)
	{
		std::cout << "Input matrix A dimensions:  mxn \n ";
		//Input validation and input section. Ask user for dimension data.
		if (std::cin >> A.dim_m && std::cin >> A.dim_n)
		{
		}
		else
		{
			std::cout << "Error! Requires integer numbers. \n ";
			return 0;
		}

		if (A.dim_m < 0 || A.dim_n < 0)
		{
			std::cout << "Negative dimensions do not exist.  \n";
			std::cin.clear();
			continue;

		}

		std::cout << "Input matrix B dimensions: mxn \n ";
		if (std::cin >> B.dim_m && std::cin >> B.dim_n)
		{
		}
		else
		{
			std::cout << "Error! Requires integer numbers. \n ";
			return 0;
		}
		if (A.dim_m != B.dim_n)
		{
			std::cout << "Error, the amount of rows of the first matrix must be equal to the amount of columns on the second matrix. Please try again. \n ";
			continue;
		}

		if (B.dim_m < 0 || B.dim_n < 0)
		{
			std::cout << "Negative dimensions do not exist.  \n";
			std::cin.clear();
			continue;
		}
		else
		{
			std::cout << " \n";
			break;
		}
		//Section end

		


	}

	A.matrix = {};
	B.matrix = {};
	matrix F;

	std::vector<matrix> operands = { A,B };
	int iteration = 0;
	for (matrix& matrixSel : operands) //Ask user 2 times for each matrice, what elements to put in?
	{
		iteration += 1;
		std::cout << std::format("Input matrix {}'s row elements: \n", iteration);
		dataPacker(matrixSel);
		if (iteration == 2) //When the user has input all elements, the program will begin to calculate the matrices.
		{
			break;
		}
	}
	std::cout << "\n-------------------------";

	F = matrixMultiplier(operands[0],operands[1]); //Do matrix multiplication
	//Display results afterwards.
	std::cout << "\n";
	display(operands[0]);
	std::cout << " \n";
	std::cout << "times ";
	display(operands[1]);
	std::cout << " \n";
	std::cout << "Result:";
	display(F);

	return 0;



}
