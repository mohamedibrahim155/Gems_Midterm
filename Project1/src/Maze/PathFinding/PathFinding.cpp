#include "PathFinding.h"
#include <fstream>
#include <algorithm>

PathFinding::PathFinding()
{
}

void PathFinding::IntializeGrid(int row, int column)
{
	this->row = row;
	this->column = column;
}

void PathFinding::GenerateGrid(std::string& mazeFilename)
{
    grid.clear();

    // Open the file
    std::ifstream file(mazeFilename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << std::endl;
    }

    std::vector<int> row;
    char c;
    while (file.get(c))
    {
        if (c == 'X') {
            row.push_back(1);  // 1 for 'X'

            //std::cout << "0";
        }
        else if (c == '.') {
            row.push_back(0);  // 0 for empty space
            //std::cout << "1";
        }
        else if (c == '\n') {
            // Start a new row in the grid when a newline character is encountered
            //std::cout << std::endl;
            grid.push_back(row);
            row.clear();
        }
    }

    if (!row.empty())   // adding last line
    {
        grid.push_back(row);
    }

    std::vector<std::vector<int>> newGrid = grid;

    for (int i = 2; i < grid.size() - 2; i++)
    {
        for (int j = 2; j < grid[i].size() - 2; j++)
        {
            if (grid[i][j] == 0)
            {
                newGrid[i][j - 1] = 0;
                newGrid[i][j + 1] = 0;

                newGrid[i - 1][j] = 0;
                newGrid[i + 1][j] = 0;

                newGrid[i][j - 2] = 0;
                newGrid[i][j + 2] = 0;

                newGrid[i - 2][j] = 0;
                newGrid[i + 2][j] = 0;

            }
            //std::cout << newGrid[i][j];
        }
        //std::cout << std::endl;

    }

  //  grid = newGrid;

    // Close the file
    file.close();

   // std::reverse(grid.begin(), grid.end());


    for (const std::vector<int>& row : grid)
    {
    	for (int ch : row)
    	{
            if (ch == 1)
            {
                std::cout << "X";
            }
            else
            {
                std::cout << ".";
            }
    		
    	}
    	std::cout << std::endl;
    }
}

bool PathFinding::isValid(int x, int y, std::vector<std::vector<int>>& grid, std::vector<std::vector<bool>>& visited)
{
    return (x >= 0 && x < row && y >= 0 && y < column && grid[x][y] == 0 && !visited[x][y]);
}

std::pair<int, std::vector<glm::vec2>> PathFinding::PathPoints(glm::vec2& start, glm::vec2& end)
{
    std::vector<std::vector<bool>> visited(row, std::vector<bool>(column, false));
    std::queue<std::pair<glm::vec2, std::vector<glm::vec2>>> q;

    /*float temp = start.x;
    start.x = start.y;
    start.y = temp;

    temp = end.x;
    end.x = end.y;
    end.y = temp;*/

    q.push({ start, {start} });


    //visited.push_back( { true,{start.x,start.y} } )
    visited[start.x][start.y] = true;

    int dx[] = { -1, 0, 1, 0 };
    int dy[] = { 0, 1, 0, -1 };

    while (!q.empty()) {
        glm::vec2 curr = q.front().first;
        std::vector<glm::vec2> path = q.front().second;
        q.pop();

        if (curr.x == end.x && curr.y == end.y)
        {
            /* for (int i = 0; i < path.size(); i++)
             {
                 float temp = path[i].x;
                 path[i].x = path[i].y;
                 path[i].y = temp;
             }*/


            return { path.size(), path };
        }

        for (int i = 0; i < 4; ++i) {
            int newX = curr.x + dx[i];
            int newY = curr.y + dy[i];

            if (isValid(newX, newY, grid, visited)) {
                visited[newX][newY] = true;
                std::vector<glm::vec2> newPath = path;
                newPath.push_back({ newX, newY });
                q.push({ {newX, newY}, newPath });
            }
        }
    }
    return { -1, {} };
}




