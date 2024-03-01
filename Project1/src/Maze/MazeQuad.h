#pragma once
#include "../model.h"

enum eType
{
    WALL = 0,
    PATHWAY = 1
};

class MazeQuad :  public Model
{

public:

    MazeQuad(bool isWall);
    ~MazeQuad();

	glm::vec3 GetPosition();

    eType type;

     void DrawProperties()override;
     void SceneDraw()override;

     void Start() override;
     void Update(float deltaTime) override;
     void Render()override;
     void OnDestroy()override;
};

