#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include<vector>
#include "../DebugModels.h"
#include "MazeQuad.h"
#include"../Maze/Treasure/Treasure.h"
#include "Hunter/Hunter.h"
#include "PathFinding/PathFinding.h"
class Maze
{
public:
	Maze();
	~Maze();

	std::vector<MazeQuad*> listOfQuads;
	std::vector<MazeQuad*> listOfQuadsWalled;
	std::vector<MazeQuad*> listOfQuadsPathWay;


	bool ReadMazeFile(std::string mazeFile);
	bool IsWall(int x, int y);

	//void GenerateRandomTreasure(int treasureCount);

	std::vector<std::vector<char>> maze;

	MazeQuad* GetPathWayAt(int x, int y);
	MazeQuad* GetWallAt(int x, int y);
	MazeQuad* GetQuadAt(int x, int y);

private:
	std::vector<std::vector<int>> mazeValue;
	//std::vector<Treasure*> listOfTreasures;


	bool GenerateMazeValue(std::vector<std::vector<char>>& maze);
	bool GenerateMazeMesh();
	//bool IsTreasureOccupied(int x, int y);
	PathFinding* pathFinding;

};

