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

	void GenerateRandomTreasure(int treasureCount);

private:
	std::vector<std::vector<int>> mazeValue;
	std::vector<std::vector<char>> maze;
	std::vector<Treasure*> listOfTreasures;
	std::vector<Hunter*> listOfHunters;


	bool GenerateMazeValue(std::vector<std::vector<char>>& maze);
	bool GenerateMazeMesh();
	bool IsTreasureOccupied(int x, int y);

};

