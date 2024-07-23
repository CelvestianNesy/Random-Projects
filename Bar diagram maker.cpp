#include <iostream>
#include <vector>
#include <cmath>


struct Bar
{
public:

	int barposition = {};
	int height = {};
	int thickness = 1;
};

struct Graph
{
public:
	
	int height = {};
	int width = {};
	char style = '.';

	std::vector<std::vector<char>> graphConstructor()
	{
		std::vector<std::vector<char>> graph; //Create empty 2D vector.

		for (int index = 0; index < height; index++)  
		{
			graph.push_back({}); //Add inner vectors. 

			for (int indexinner = 0; indexinner < width; indexinner++)
			{
				graph[index].push_back(style); //Add the characters our inner  vectors are going to contain.

			}
		}
		return graph;
	}
};

void display(int height, int width, auto& graph)
{
	for (int y = height-1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			std::cout << graph[y][x];  //Displays vector
		}
		std::cout << "\n";
	}

}

std::vector<std::vector<char>> graphModifier(Bar bar, std::vector<std::vector<char>>& graph)
{
	for (int ypos = 0; ypos < bar.height; ypos++) //loop responsible for drawing out our bars.
	{
		graph[ypos][bar.barposition] = 'x';
		
		for (int thickness = 0; thickness < bar.thickness; thickness++)
		{
			graph[ypos][bar.barposition+thickness] = 'x';    //add additional thickness.
		}
	}
	return graph;
}

int main()
{
	int height = 20;
	int width = 100;
	Graph gtemplate = { height,width,' '}; //placeholder for a graph with the dimensions height * width. It'll be soon be filled in by .graphConstructor()

	std::vector<std::vector<char>> graph = gtemplate.graphConstructor(); //We store our actual graph in here.
	Bar bar1 = { 0,4,3 };  // (Formula: 2x = y) (y thickness, x increment) for y spacing.
	Bar bar2 = { 6,8,3 };
	Bar bar3 = { 12,6,3 };
	Bar bar4 = { 18,4,3 };
	Bar bar5 = { 24,10,3 };
	Bar bar6 = { 30,19,3 };
	Bar bar7 = { 36,1,3};

	std::vector<Bar> bars = {bar1,bar2,bar3,bar4,bar5,bar6,bar7};

	for (const auto& bar : bars)
	{
		graph = graphModifier(bar, graph); //Updates our graph.
	}

	display(height, width, graph);
}

