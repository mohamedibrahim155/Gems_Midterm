#include "Hunter.h"
#include "../../GraphicsRender.h"
#include "../../DebugModels.h"
#include"../Maze.h"
Hunter::Hunter()
{
	LoadModel(*DebugModels::GetInstance().defaultQuad);
	meshes[0]->meshMaterial->unLitMaterial()->SetBaseColor(glm::vec4(1, 0, 0, 1));

	//GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().solidColorShader);


	transform.SetScale(glm::vec3(0.5f));

}

glm::vec3 Hunter::GetPosition()
{
	return transform.position;
}

glm::vec3 Hunter::GetTargetPosition()
{
	return targetPosition;
}

void Hunter::SetTreasureTarget(int x, int y)
{
	targetPosition = glm::vec3(x, y, 0);
}

void Hunter::MovePosition(int x, int y)
{
	//if (maze->IsWall(x, y)) return;

	transform.SetPosition(glm::vec3((float)x, (float)y, 0));
}

void Hunter::SetMaze(Maze* maze)
{
	this->maze = maze;
}



void Hunter::DrawProperties()
{
	Model::DrawProperties();
}

void Hunter::SceneDraw()
{
	Model::SceneDraw();
}

void Hunter::Start()
{
}

void Hunter::Update(float deltaTime)
{
}

void Hunter::Render()
{
	Model::Render();

	DrawSolidColor(glm::vec4(0, 1, 0, 1));
}

void Hunter::OnDestroy()
{
}
