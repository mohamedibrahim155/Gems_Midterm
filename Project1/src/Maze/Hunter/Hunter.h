#pragma once
#include"../../model.h"


class MazeManager;

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
    MazeManager* mazeController;


    void SetTreasureTarget(int x, int y);
    void SetTreasureTarget();

    void MovePosition(int x, int y);
    void MovePosition(glm::vec3 position);
    void Intitialize();

    void DrawProperties()override;
    void SceneDraw()override;

    void Start() override;


    void Update(float deltaTime) override;
    void Render()override;
    void OnDestroy()override;

    void UpdateHunterPosition(float deltaTime);


private:

    glm::vec3 targetPosition;


    float timer = 0;
    float interval = 0.1f;

    std::vector<glm::vec3 > positions;

    int iteration = 0;

    bool isReached = false;
    bool isStartinvoked = false;

    int treasureCollected = 0;
};

