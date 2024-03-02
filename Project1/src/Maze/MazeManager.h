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
	void RemoveCollectedTreasure(int x, int y);
	

	//Hunter* CreateHunter(int x, int y);
	glm::vec3 GetARandomMovePosition(glm::vec3& hunterPosition);
	std::vector<glm::vec3> GetPoints(glm::vec3& hunterPosition, glm::vec3& endPosition);

	glm::vec3 GetRandomTreasure();

	int GetRandomDirection(glm::vec3 position);

	void SetMaze(Maze* maze);
	void GenerateTreasures(int treasureCount);
	int treasureCount = 250;

private:

	Maze* maze;
};

