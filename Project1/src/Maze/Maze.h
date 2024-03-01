#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include<vector>
#include "../DebugModels.h"



class Maze
{
public:
	Maze();
	~Maze();




	std::vector<std::vector<int>> mazeValue;

	std::vector<std::vector<char>> maze;


	bool ReadMazeFile(std::string mazeFile);
	bool GenerateMazeValue(std::vector<std::vector<char>>& maze);

	bool IsWall(char& value);

	bool GenerateMazeMesh();




    // Read characters one by one and store them in the vector
   

private:

};

