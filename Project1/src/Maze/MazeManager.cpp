#include "MazeManager.h"
#include "../Math.h"

using namespace MathUtils;

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
	int mazeValueJ = maze->maze[0].size() - 1;
	int mazeValueI = maze->maze.size() - 1;


	for (int index = 0; index < treasureCount; index++)
	{

		Treasure* treasure = new Treasure();
		treasure->name = "Treasure_" + std::to_string(index);
		treasure->SetMaze(maze);
		treasure->transform.SetScale(glm::vec3(0.5f));


		int j = Math::GetRandomIntNumber(-mazeValueJ, -1);

		int i = Math::GetRandomIntNumber(-mazeValueI, -1);
		std::cout << "maze value x" << i << " , " << j << std::endl;
		do
		{
			j = Math::GetRandomIntNumber(-mazeValueJ, -1);

			i = Math::GetRandomIntNumber(-mazeValueI, -1);

		} while (!maze->IsWall(j, i) && !IsTreasureOccupied(j, i));

		treasure->SetPosition(j, i);

		listOfTreasures.push_back(treasure);

	}
}

Hunter* MazeManager::CreateHunter(int x, int y)
{

	if (!maze->IsWall(x,y))
	{

		Hunter* hunter = new Hunter();

		hunter->SetMaze(maze);

		hunter->MovePosition(x, y);

		listOfHunters.push_back(hunter);

		return hunter;

	}

	return nullptr;
}


glm::vec3 MazeManager::GetARandomMovePosition(glm::vec3& hunterPosition)
{
	glm::vec3 hunterPos = hunterPosition;

	int randomDir = GetRandomDirection(hunterPos);

	while (randomDir < 0) //  if direction -1 , finding again new dir
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

int MazeManager::GetRandomDirection(glm::vec3 position)
{
	int randomDir = Math::GetRandomIntNumber(0, 3);

	

	Direction type = (Direction)randomDir;

	switch (type)
	{
	case Direction::UP:

		if (!maze->IsWall(position.x, position.y + 1))
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
	for (Treasure* treasure : listOfTreasures)
	{
		if (treasure->GetPosition().x == x && treasure->GetPosition().y)
		{
			return true;
		}
	}
	return false;
}
