#include "Hunter.h"
#include "../../GraphicsRender.h"
#include "../../DebugModels.h"
#include "../MazeManager.h"
Hunter::Hunter()
{
	//mazeManager = &MazeManager::GetInstance();

	name = "Hunter";

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

void Hunter::MovePosition(glm::vec3 position)
{
	transform.SetPosition(position);
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
	MovePosition(intialPosition.x, intialPosition.y);
}

void Hunter::Update(float deltaTime)
{
//	if (timer >= interval)
	{
	//	timer = 0;

		glm::vec3 randomPosition = MazeManager::GetInstance().GetARandomMovePosition(transform.position);

		MovePosition(randomPosition);
	}
	//else
	//{
	//	timer += deltaTime;
	//}
}

void Hunter::Render()
{
	Model::Render();

	DrawSolidColor(glm::vec4(0, 1, 0, 1));
}

void Hunter::OnDestroy()
{
}

void Hunter::UpdateHunterPosition(float deltaTime)
{
	if (mazeController)
	{
		glm::vec3 randomPosition = mazeController->GetARandomMovePosition(transform.position);

		MovePosition(randomPosition);
	}
	
}
