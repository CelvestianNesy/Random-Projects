#include <iostream>
#include <vector>


std::vector<std::vector<char>> graphDrawer(int width, int height,char style, std::vector<std::vector<char>> graph = { })
{
	for (int y = 0; y < height; y++) //Generates new empty vectors.
	{
		graph.push_back({style});
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width-1; x++)   //Generates width by pushing char into an empty vectors first. 
		{
			graph[y].push_back({style});  //At graph[y], put our char in. 
		}

	}

	for (int y = graph.size()-1; y >= 0 ; y--)    //Display entire thing. 
	{
		for (int x = 0; x < graph[y].size(); x++)
		{
			std::cout << graph[y][x];
		}

		std::cout << "\n";
	}

	return graph;
}

struct line
{
public:
	int x1 = {};
	int y1 = {};

	int x2 = {};
	int y2 = {};
	
	int derivative()
	{
		int derivative = (y2 - y1) / (x2 - x1);
		return derivative;
	}
	
	int Moffset(int derivative)
	{

		int m = y1 - derivative * (x1);
		return m;
	}

	int deltaX()
	{
		int delta = (x2 - x1);
		return delta;
	}

};


int main()
{

	std::vector<std::vector<char>> graph = graphDrawer(30,10,'.');

	line lineA = { 0,4,1,4};
	
	
	std::cout << lineA.Moffset(lineA.derivative());

	


	return 0;
}


