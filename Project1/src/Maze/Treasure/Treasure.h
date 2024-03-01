#pragma once
#include "../../model.h"
#include "../Maze.h"
class Treasure : public Model
{
public:
	Treasure();

	void SetMaze(Maze* maze);

     void DrawProperties()override;
     void SceneDraw()override;

     void Start() override;
     void Update(float deltaTime) override;
     void Render()override;
     void OnDestroy()override;

private:

	Maze* maze;

};

