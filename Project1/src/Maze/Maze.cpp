#include "Maze.h"

Maze::Maze()
{
}

Maze::~Maze()
{
}

bool Maze::ReadMazeFile(std::string mazeFile)
{
	std::ifstream inputFile(mazeFile);
	if (!inputFile.is_open()) {
		std::cerr << "Error opening the file." << std::endl;
		return false;
	}


	char ch;
	std::vector<char> row;

	while (inputFile.get(ch)) 
	{
		if (ch == '\n') 
		{
		
			maze.push_back(row);
			
			row.clear();
		}
		else 
		{
			
			row.push_back(ch);
		}
	}

	inputFile.close();

	/*for (const auto& row : maze)
	{
		for (char ch : row) 
		{
			std::cout << ch;
		}
		std::cout << std::endl;
	}*/
	GenerateMazeValue(maze);

	return true;
}

bool Maze::GenerateMazeValue(std::vector<std::vector<char>> &maze)
{
	

	for (int i = 0; i < maze.size(); i++)
	{
		

		std::vector<int> columns;

		for (int j = 0; j < maze[i].size(); j++)
		{
			int value = 0;   // 0 - wall, 1- path
			
			if (maze[i][j] == 'X')
			{
				value = 0;
			}
			else if(maze[i][j] == '.')
			{
				value = 1;
			}

			columns.push_back(value);
		}


		mazeValue.push_back(columns);
	}

	return true;
}
