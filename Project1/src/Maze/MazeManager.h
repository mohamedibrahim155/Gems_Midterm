#pragma once
#include "../Maze/Maze.h"
#include "../Maze/MazeQuad.h"
#include "Treasure/Treasure.h"

enum class Direction
{
	UP =0,
	DOWN=1,
	LEFT=2,
	RIGHT=3,
};
class MazeManager
{
public:
	MazeManager();
	~MazeManager();

	static MazeManager& GetInstance();

	std::vector<Treasure*> listOfTreasures;
	//std::vector<Hunter*> listOfHunters;

	bool IsTreasureOccupied(int x, int y);

	

	//Hunter* CreateHunter(int x, int y);
	glm::vec3 GetARandomMovePosition(glm::vec3& hunterPosition);

	int GetRandomDirection(glm::vec3 position);

	void SetMaze(Maze* maze);
	void GenerateTreasures(int treasureCount);

private:

	Maze* maze;
};

