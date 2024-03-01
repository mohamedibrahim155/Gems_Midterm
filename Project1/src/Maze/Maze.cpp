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
			row.push_back(ch);
		}
	}

	if (!row.empty())   // adding last line
	{
		maze.push_back(row);
	}
	inputFile.close();



	//for (const std::vector<char>& row : maze)
	//{
	//	for (char ch : row) 
	//	{
	//		std::cout << ch;

	//		if (IsWall(ch))
	//		{

	//		}
	//	}
	//	std::cout << std::endl;
	//}
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

bool Maze::IsWall(int x, int y)
{
	for (MazeQuad* quad : listOfQuadsWalled)
	{
		if (quad->GetPosition().x == x && quad->GetPosition().y)
		{
			return true;
		}
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
				MazeQuad* mazeWalled = new MazeQuad(true);

				mazeWalled->type = WALL;

				mazeWalled->transform.SetPosition(glm::vec3(-j - 1, -i - 1, 0));
				mazeWalled->transform.SetScale(glm::vec3(0.5f));

				listOfQuadsWalled.push_back(mazeWalled);

				listOfQuads.push_back(mazeWalled);
			}
			else
			{
				MazeQuad* mazePath = new MazeQuad(false);

				mazePath->type = PATHWAY;

				mazePath->transform.SetPosition(glm::vec3(-j - 1, -i - 1, 0));
				mazePath->transform.SetScale(glm::vec3(0.5f));

				listOfQuadsPathWay.push_back(mazePath);

				listOfQuads.push_back(mazePath);
			}


		}
	}

	return true;
}
