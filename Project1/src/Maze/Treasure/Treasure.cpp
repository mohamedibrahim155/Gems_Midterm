#include "Treasure.h"
#include "../../DebugModels.h"
#include "../../GraphicsRender.h"
#include "../Maze.h"
Treasure::Treasure()
{
	LoadModel(*DebugModels::GetInstance().defaultQuad);
	GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().stencilShader);
	
	//meshes[0]->meshMaterial->unLitMaterial()->SetBaseColor(glm::vec4(1, 1, 0, 1));

}

glm::vec3 Treasure::GetPosition()
{
	return transform.position;
}

void Treasure::SetMaze(Maze* maze)
{
	this->maze = maze;
}

void Treasure::SetPosition(int x, int y)
{
	transform.SetPosition(glm::vec3((float)x, (float)y, 0));
}

void Treasure::DrawProperties()
{
	Model::DrawProperties();
}

void Treasure::SceneDraw()
{
	Model::SceneDraw();
}

void Treasure::Start()
{
}

void Treasure::Update(float deltaTime)
{
}

void Treasure::Render()
{
}

void Treasure::OnDestroy()
{
}
