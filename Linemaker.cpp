#include <iostream>
#include <vector>
#include <cmath>

std::vector<std::vector<char>> graphDrawer(int width, int height,char style, std::vector<std::vector<char>> graph = { })
{
	for (int y = 0; y < height; y++) //Generates new empty vectors.
	{
		graph.push_back({});
	}
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)   //Generates width by pushing char into an empty vector first. 
		{
			graph[y].push_back({style});  //At graph[y], put our char in. 
		}

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
	
	int slope()
	{
		int slope = 0;
		slope = (y2 - y1) / (x2 - x1);
		
			
		
		return slope;
	}
	
	int Moffset(int slope)
	{

		int m = y1 - slope * (x1);  //Basically, where the function cuts the y axis.
		return m;
	}

};
void display(std::vector<std::vector<char>>& graph)
{
	for (int y = graph.size() - 1; y >= 0; y--)    //Display entire thing. 
	{
		for (int x = 0; x < graph[y].size(); x++)
		{
			std::cout << graph[y][x];
		}

		std::cout << "\n";
	}

}
void lineDrawer(std::vector<std::vector<char>>& graph, line& lineA)
{
	std::vector<int> xValues = {};
	std::vector<int> yValues = {};

	double functionY = 0;
	if (lineA.slope() >= 0)
	{
		for (int x = lineA.x1; x <= lineA.x2; x++)  //Generates a vector of y positions.
		{
			functionY = lineA.slope() * x + lineA.Moffset(lineA.slope());
			functionY = std::ceil(functionY);
			graph[functionY][x] = '*';
		}
	}

	if (lineA.slope() < 0)
	{
		for (int x = lineA.x1; x >= lineA.x2; x--)  //Generates a vector of y positions.
		{
			functionY = lineA.slope() * x + lineA.Moffset(lineA.slope());
			functionY = std::ceil(functionY);
			graph[functionY][x] = '*';
		}

	}
}

int main()
{
	std::vector<std::vector<char>> graphvec = graphDrawer(50,20,'.');
	line lineA = { 2,2,18,2};
	line lineB = { 2,2,10,12 };
	line lineC = { 18,2,10,12 };
	lineDrawer(graphvec, lineA); 
	lineDrawer(graphvec, lineB); 
	lineDrawer(graphvec, lineC);
	
	
	display(graphvec);

	return 0;
}


