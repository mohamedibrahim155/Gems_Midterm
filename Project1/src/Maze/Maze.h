#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include<vector>
#include "../DebugModels.h"
#include "MazeQuad.h"



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

private:
	std::vector<std::vector<int>> mazeValue;
	std::vector<std::vector<char>> maze;

	bool GenerateMazeValue(std::vector<std::vector<char>>& maze);
	bool GenerateMazeMesh();
};

