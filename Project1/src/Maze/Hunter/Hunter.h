#pragma once
#include"../../model.h"
#include "../MazeManager.h"



enum  eHunterState
{
    SEARCHING = 0,
    TOOK = 1,
    FLEE = 2, 
};
class Hunter : public Model
{
public:
	Hunter();

    eHunterState state = SEARCHING;

    glm::vec3 intialPosition = glm::vec3(-11, -146, 0);

    glm::vec3 GetPosition();
    glm::vec3 GetTargetPosition();


    void SetTreasureTarget(int x, int y);

    void MovePosition(int x, int y);
    void MovePosition(glm::vec3 position);
    
    void DrawProperties()override;
    void SceneDraw()override;

    void Start() override;
    void Update(float deltaTime) override;
    void Render()override;
    void OnDestroy()override;

private:

    glm::vec3 targetPosition;


    float timer = 0;
    float interval = 2;

  //  MazeManager* mazeManager = nullptr;


};

