#include "MazeManager.h"
#include "../Math.h"

using namespace MathUtils;

MazeManager::MazeManager()
{
}

MazeManager::~MazeManager()
{
}

MazeManager& MazeManager::GetInstance()
{
    static MazeManager instance;

    return instance;
}

void MazeManager::SetMaze(Maze* maze)
{
	this->maze = maze;
}

void MazeManager::GenerateTreasures(int treasureCount)
{
	int mazeValueJ = (maze->maze[0].size() - 1) * -1;
	int mazeValueI = (maze->maze.size() - 1) * -1;


	for (int index = 0; index < treasureCount; index++)
	{

		Treasure* treasure = new Treasure();
		treasure->name = "Treasure_" + std::to_string(index);
		treasure->SetMaze(maze);
		treasure->transform.SetScale(glm::vec3(0.5f));

		int min = mazeValueJ;
		int max = -1;

	//	int randomNumber = min + std::rand() % (max - min + 1);
		int j = Math::GetRandomIntNumber(mazeValueJ, -1);
		//int j = randomNumber;
		min = mazeValueI;

	//	randomNumber = min + std::rand() % (max - min + 1);
		int i = Math::GetRandomIntNumber(mazeValueI, -1);
		//int i = randomNumber;

		std::cout << "maze value x" << i << " , " << j << std::endl;
		do
		{
			j = Math::GetRandomIntNumber(mazeValueJ, -1);

			//randomNumber = mazeValueJ + std::rand() % (max - mazeValueJ + 1);

			//j = randomNumber;


			i = Math::GetRandomIntNumber(mazeValueI, -1);

			//randomNumber = mazeValueI + std::rand() % (max - mazeValueI + 1);

			//i = randomNumber;

		} while (  !IsTreasureOccupied(j, i) && maze->IsWall(j, i));

		treasure->SetPosition(j, i);

		listOfTreasures.push_back(treasure);

	}
}

//Hunter* MazeManager::CreateHunter(int x, int y)
//{
//
//	if (!maze->IsWall(x,y))
//	{
//
//		Hunter* hunter = new Hunter();
//
//		hunter->SetMaze(maze);
//
//		hunter->MovePosition(x, y);
//
//		listOfHunters.push_back(hunter);
//
//		return hunter;
//
//	}
//
//	return nullptr;
//}


glm::vec3 MazeManager::GetARandomMovePosition(glm::vec3& hunterPosition)
{
	glm::vec3 hunterPos = hunterPosition;

	int randomDir = GetRandomDirection(hunterPos);

	while (randomDir == -1)
	{
		randomDir = GetRandomDirection(hunterPos);
	}
	

	Direction type = (Direction)randomDir;

	switch (type)
	{
	case Direction::UP:

		
		return maze->GetPathWayAt(hunterPos.x, hunterPos.y + 1)->GetPosition();
		break;
	case Direction::DOWN:

	

		return maze->GetPathWayAt(hunterPos.x, hunterPos.y - 1)->GetPosition();
		break;
	case Direction::LEFT:

		
		return maze->GetPathWayAt(hunterPos.x+1, hunterPos.y)->GetPosition();
		break;
	case Direction::RIGHT:


		return maze->GetPathWayAt(hunterPos.x-1, hunterPos.y)->GetPosition();
		break;
	default:
		break;
	}


	//return glm::vec3(0);
}

std::vector<glm::vec3>  MazeManager::GetPoints(glm::vec3& hunterPosition, glm::vec3& endPosition)
{
	glm::vec2 hunterpos = glm::vec2(hunterPosition.y, hunterPosition.x) * -1.0f;

	glm::vec2 end = glm::vec2(endPosition.y, endPosition.x) * -1.0f;

	std::pair<int, std::vector<glm::vec2>> mazePoints = maze->getPathfinding()->PathPoints(hunterpos, end);

	std::vector<glm::vec3> positionToTravel;

	for (size_t i = 0; i < mazePoints.second.size(); i++)
	{
		positionToTravel.push_back(glm::vec3(-mazePoints.second[i].y, -mazePoints.second[i].x, 0));
	}

	return positionToTravel;
}

glm::vec3 MazeManager::GetRandomTreasure()
{
	int random = Math::GetRandomIntNumber(0, listOfTreasures.size() - 1);
	/*int randomNumber = 0 + std::rand() % (listOfTreasures.size() - 0 + 1);*/

	return listOfTreasures[random]->GetPosition();
}

int MazeManager::GetRandomDirection(glm::vec3 position)
{
	//int randomDir = Math::GetRandomIntNumber(0, 3);
	int randomDir = rand() % 4;

	

	Direction type = (Direction)randomDir;

	switch (type)
	{
	case Direction::UP:

		if (!maze->IsWall(position.x, position.y + 1) )
		{
			return randomDir;
		}

		break;
	case Direction::DOWN:
		if (!maze->IsWall(position.x, position.y - 1))
		{
			return randomDir;
		}
		break;
	case Direction::LEFT:

		if (!maze->IsWall(position.x+1, position.y))
		{
			return randomDir;
		}

		break;
	case Direction::RIGHT:
		if (!maze->IsWall(position.x - 1, position.y))
		{
			return randomDir;
		}
		break;
	}



	return -1;
}

bool MazeManager::IsTreasureOccupied(int x, int y)
{
	if (listOfTreasures.size()==0)
	{
		return true;
	}
	for (Treasure* treasure : listOfTreasures)
	{
		if (treasure->GetPosition().x == x && treasure->GetPosition().y == y)
		{
			return true;
		}
	}
	return false;
}

void MazeManager::RemoveCollectedTreasure(int x, int y)
{
	Treasure* removeValue = nullptr;
	for (Treasure* treasure : listOfTreasures)
	{
		if (treasure->GetPosition().x == x && treasure->GetPosition().y == y)
		{
			removeValue = treasure;
			removeValue->isVisible = false;
		}
	}

	if (removeValue)
	{
		listOfTreasures.erase(std::remove(listOfTreasures.begin(), listOfTreasures.end(), removeValue), listOfTreasures.end());
	}
}

