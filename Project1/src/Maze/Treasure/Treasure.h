#pragma once
#include "../../model.h"


class Maze;

enum eState
{
    NOTPICKED =0,
    PICKED =1,

};

class Treasure : public Model
{
public:
	Treasure();

    eState state;

    glm::vec3 GetPosition();

	void SetMaze(Maze* maze);
    void SetPosition(int x, int y);
    void DrawProperties()override;
    void SceneDraw()override;

    void Start() override;
    void Update(float deltaTime) override;
    void Render()override;
    void OnDestroy()override;

private:

	Maze* maze;

    glm::vec4 treasureColor =  glm::vec4(1.0f,0,0,1);

};

