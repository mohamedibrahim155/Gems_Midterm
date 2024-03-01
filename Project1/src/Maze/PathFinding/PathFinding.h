#pragma once
#include <queue>
#include <vector>
#include <unordered_map>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <string>




class PathFinding
{
public:

	PathFinding();

	void IntializeGrid(int row, int column);
	void GenerateGrid(std::string& mazeFilename);

	bool isValid(int x, int y, std::vector<std::vector<int>>& grid, std::vector<std::vector<bool>>& visited);

	std::pair<int, std::vector<glm::vec2>> PathPoints(glm::vec2& start, glm::vec2& end);
private:

	int row;
	int column;
	std::vector<std::vector<int>> grid;
};

