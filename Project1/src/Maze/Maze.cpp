#include "Maze.h"
#include"../GraphicsRender.h"
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
			if (ch=='X')
			{

			}
			else if(ch == '.')
			{

			}
			row.push_back(ch);
		}
	}

	inputFile.close();


	for (size_t i = 0; i < maze.size(); i++)
	{
		for (int j =0 ;  j< maze[i].size(); j++)
		{
			std::cout << ch;

			
		}
	}
	/*for (const std::vector<char>& row : maze)
	{
		for (char ch : row) 
		{
			std::cout << ch;

			if (IsWall(ch))
			{

			}
		}
		std::cout << std::endl;
	}*/
	GenerateMazeValue(maze);
	if (!GenerateMazeMesh())
	{
		return false;
	}
	return true;
}

bool Maze::GenerateMazeValue(std::vector<std::vector<char>> &maze)
{
	

	for (int i = 0; i < maze.size(); i++)
	{
		

		std::vector<int> columns;
		int value = 0;   // 0 - wall, 1- path

		for (int j = 0; j < maze[i].size(); j++)
		{
			
			if (maze[i][j] == 'X')
			{
				value = 1;
			}
			/*else if(maze[i][j] == '.')
			{
				value = 0;
			}*/

			columns.push_back(value);
		}


		mazeValue.push_back(columns);
	}

	return true;
}

bool Maze::IsWall(char& value)
{
	if (value == 'X')
	{
		return true;
	}
	return false;
}

bool Maze::GenerateMazeMesh()
{


	for (int i = 0; i < maze.size(); i++)
	{
		for (int j = 0; j < maze[i].size(); j++)
		{
			if (maze[i][j] == 'X')
			{
				Model* cube = new Model(*DebugModels::GetInstance().defaultQuad, true);

				cube->transform.SetPosition(glm::vec3(-j, -i, 0));
				cube->transform.SetScale(glm::vec3(0.5f));

				GraphicsRender::GetInstance().AddModelAndShader(cube, GraphicsRender::GetInstance().solidColorShader);
			}
		}
	}

	return true;
}
