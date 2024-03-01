#include "MazeQuad.h"
#include "../DebugModels.h"
#include"../GraphicsRender.h"
//MazeQuad::MazeQuad(bool isWall)
//{
//    
//    LoadModel(*DebugModels::GetInstance().defaultQuad, true);
//
//    if (!isWall)
//    {
//        isVisible = false;
//    }
//
//}

MazeQuad::MazeQuad( bool isWall)
{
    LoadModel(*DebugModels::GetInstance().defaultQuad, true);

    GraphicsRender::GetInstance().AddModelAndShader(this, 
        GraphicsRender::GetInstance().solidColorShader);
    
    if (!isWall)
    {
        isVisible = false;
    }
}

MazeQuad::~MazeQuad()
{
}

glm::vec3 MazeQuad::GetPosition()
{
    return transform.position;
}

void MazeQuad::DrawProperties()
{
    Model::DrawProperties();
}

void MazeQuad::SceneDraw()
{
    Model::SceneDraw();
}

void MazeQuad::Start()
{
}

void MazeQuad::Update(float deltaTime)
{
}

void MazeQuad::Render()
{
}

void MazeQuad::OnDestroy()
{
}
