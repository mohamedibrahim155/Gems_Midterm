#include "Maze.h"
#include"../GraphicsRender.h"
#include "../Math.h"

using namespace MathUtils;

Maze::Maze()
{
	pathFinding = new PathFinding();
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

	//std::reverse(maze.begin(), maze.end());

	pathFinding->IntializeGrid(maze.size(), maze[0].size());


	pathFinding->GenerateGrid(mazeFile);

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
		if (quad->GetPosition().x == x && quad->GetPosition().y == y)
		{
			return true;
		}
	}

	return false;
}

MazeQuad* Maze::GetPathWayAt(int x, int y)
{
	MazeQuad* temp = listOfQuadsPathWay[0];

	for (MazeQuad* mazeQuad :  listOfQuadsPathWay)
	{
		if (mazeQuad->GetPosition().x == x && mazeQuad->GetPosition().y == y)
		{
			temp = mazeQuad;
			return temp;
		}
	}
	return temp;
}

MazeQuad* Maze::GetWallAt(int x, int y)
{
	MazeQuad* temp = listOfQuadsWalled[0];

	for (MazeQuad* mazeQuad : listOfQuadsWalled)
	{
		if (mazeQuad->GetPosition().x == x && mazeQuad->GetPosition().y == y)
		{
			temp = mazeQuad;
			return temp;
		}
	}
	return temp;
}

MazeQuad* Maze::GetQuadAt(int x, int y)
{
	MazeQuad* temp = listOfQuads[0];

	for (MazeQuad* mazeQuad : listOfQuads)
	{
		if (mazeQuad->GetPosition().x == x && mazeQuad->GetPosition().y == y)
		{
			temp = mazeQuad;
			return temp;
		}
	}
	return temp;
}

 PathFinding* Maze::getPathfinding() const
{
	return pathFinding;
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
				mazeWalled->name = "WALL_" + std::to_string(i) + "_" + std::to_string(j);
				mazeWalled->type = WALL;

				mazeWalled->transform.SetPosition(glm::vec3(-j, -i, 0));
				mazeWalled->transform.SetScale(glm::vec3(0.5f));

				listOfQuadsWalled.push_back(mazeWalled);

				listOfQuads.push_back(mazeWalled);
			}
			else
			{
				MazeQuad* mazePath = new MazeQuad(false);

				mazePath->type = PATHWAY;
				mazePath->name = "WAY_" + std::to_string(i) + "_" + std::to_string(j);

				mazePath->transform.SetPosition(glm::vec3(-j, -i, 0));
				mazePath->transform.SetScale(glm::vec3(0.5f));

				listOfQuadsPathWay.push_back(mazePath);

				listOfQuads.push_back(mazePath);
			}


		}
	}

	return true;
}

//bool Maze::IsTreasureOccupied(int x, int y)
//{
//	for (Treasure* treasure  : listOfTreasures)
//	{
//		if (treasure->GetPosition().x  == x && treasure->GetPosition().y)
//		{
//			return true;
//		}
//	}
//	return false;
//}

//void Maze::GenerateRandomTreasure(int treasureCount)
//{
//
//	int mazeValueJ = maze[0].size() - 1;
//	int mazeValueI = maze.size() - 1;
//
//
//	for (int index = 0; index < treasureCount; index++)
//	{
//		
//		Treasure* treasure = new Treasure();
//		treasure->name = "Treasure_" + std::to_string(index);
//		treasure->SetMaze(this);
//		treasure->transform.SetScale(glm::vec3(0.5f));
//
//
//		int j = Math::GetRandomIntNumber(-mazeValueJ, -1);
//
//		int i = Math::GetRandomIntNumber(-mazeValueI, -1);
//		std::cout << "maze value x" << i << " , " << j << std::endl;
//		do
//		{
//			j = Math::GetRandomIntNumber(-mazeValueJ, -1);
//
//			i = Math::GetRandomIntNumber(-mazeValueI, -1);
//
//		} while (!IsWall(j,i) && !IsTreasureOccupied(j, i));
//
//		treasure->SetPosition(j, i);
//
//		listOfTreasures.push_back(treasure);
//
//	}
//
//	Hunter* firstHunter = new Hunter();
//
//	firstHunter->transform.SetPosition(firstHunter->intialPosition);
//}
