#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include<vector>

enum PathType
{
	WALL = 0,  //X
	PATHWAY = 1,  //.
	EMPTY = 2      // EXIT OR ENTERANCE
};

struct MazeNode
{
	MazeNode() {};
	//int id;
	int row;
	int column;
	PathType pathType;
};

class Maze
{
public:
	Maze();
	~Maze();




	std::vector<std::vector<int>> mazeValue;

	std::vector<std::vector<char>> maze;

	std::vector<MazeNode*> nodeList;

	bool ReadMazeFile(std::string mazeFile);
	bool GenerateMazeValue(std::vector<std::vector<char>>& maze);




    // Read characters one by one and store them in the vector
   

private:

};

