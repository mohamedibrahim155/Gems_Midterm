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

	transform.SetPosition(intialPosition);
	transform.SetScale(glm::vec3(0.5f));

}

Hunter::~Hunter()
{
	threadInfo->isThreadActive = false;
	threadInfo->isActive = false;
	WaitForSingleObject(threadInfo->threadHandle, INFINITE);
	CloseHandle(threadInfo->threadHandle);
	DeleteCriticalSection(&threadInfo->cs);
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

void Hunter::SetTreasureTarget()
{
	targetPosition =MazeManager::GetInstance().GetRandomTreasure();
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

void Hunter::Intitialize()
{
	if (MazeManager::GetInstance().treasureCount == 0)
	{

		state = FLEE;
		positions.clear();
		return;
	}

	//SetTreasureTarget();

	//positions = MazeManager::GetInstance().GetPoints(transform.position, targetPosition);

	

	do
	{
		SetTreasureTarget();
		positions = MazeManager::GetInstance().GetPoints(transform.position, targetPosition);

	} while (positions.size() == 0);
}




void Hunter::DrawProperties()
{
	Model::DrawProperties();

	ImGui::SetNextItemWidth(80);
	ImGui::InputText("Treasure collected", &name[0], 256);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80);
	ImGui::DragInt("###Treasurecollected", &treasureCollected);
}

void Hunter::SceneDraw()
{
	Model::SceneDraw();
}

void Hunter::Start()
{
	MovePosition(intialPosition.x, intialPosition.y);

	Intitialize();
}

void Hunter::Update(float deltaTime)
{
	if (timer >= interval)
	{
		timer = 0;

		//glm::vec3 randomPosition = MazeManager::GetInstance().GetARandomMovePosition(transform.position);

		if (!isReached)
		{
		
			if (positions.size()!=0 && iteration<positions.size())
			{
				MovePosition(positions[iteration]);

			}
			else
			{
				isReached = true;

				state = TOOK;
			}
			iteration++;

			
		}

	}
	else
	{
		timer += deltaTime;
	}
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
		//glm::vec3 randomPosition = mazeController->GetARandomMovePosition(transform.position);

		if (!isStartInvoked)
		{
			Intitialize();
			isStartInvoked = true;
		}
		//MovePosition(randomPosition);

		if (timer >= interval)
		{
			timer = 0;

			//glm::vec3 randomPosition = MazeManager::GetInstance().GetARandomMovePosition(transform.position);

			if (!isReached)
			{

				if (positions.size() != 0 && iteration < positions.size())
				{
					MovePosition(positions[iteration]);

				}
				else
				{
					isReached = true;

					state = TOOK;

					if (MazeManager::GetInstance().IsTreasureOccupied(transform.position.x, transform.position.y))
					{
						treasureCollected += 1;

						//MazeManager::GetInstance().RemoveCollectedTreasure(transform.position.x, transform.position.y);
						//MazeManager::GetInstance().treasureCount--;
						std::cout <<"Hunter Id: "<<id << " Teasurecollected : " << treasureCollected << std::endl;

					
					}


					isStartInvoked = false;
					isReached = false;
					iteration = 0;
				}
				iteration++;


			}

			
			if (MazeManager::GetInstance().IsTreasureOccupied(transform.position.x, transform.position.y))

			{

				MazeManager::GetInstance().RemoveCollectedTreasure(transform.position.x, transform.position.y);
				MazeManager::GetInstance().treasureCount--;

				treasureCollected++;
				std::cout << "Hunter Id: " << id << " Teasurecollected : " << treasureCollected << std::endl;

			}
		}
		else
		{
			timer += deltaTime;
		}
	}
	
}




DWORD WINAPI UpdateHunterThread(LPVOID lpParameter)
{
	HunterThread* threadPointer = (HunterThread*)lpParameter;

	threadPointer->hunterObject->mazeController = threadPointer->mazeController;

	double lastFrameTime = glfwGetTime();
	double timeStep = 0.0;
	DWORD sleepTime_ms = 1;

	InitializeCriticalSection(&threadPointer->cs);

	while (threadPointer->isActive)
	{
		if (threadPointer->isThreadActive)
		{
			double currentTime = glfwGetTime();
			double deltaTime = currentTime - lastFrameTime;
			lastFrameTime = currentTime;

			timeStep += deltaTime;

			if (timeStep>= threadPointer->desiredUpdateTime)
			{
				timeStep = 0;
				if (*(threadPointer->playMode) == true)
				{
					threadPointer->hunterObject->UpdateHunterPosition(threadPointer->desiredUpdateTime);

				}

			}


			//Sleep(threadPointer->sleepTime);
			
		}

		Sleep(threadPointer->sleepTime);

	}


	return 0;

}

void Hunter::InitializeThread()
{
	threadInfo = new HunterThread();

	threadInfo->mazeController = &MazeManager::GetInstance();
	threadInfo->hunterObject = this;
	threadInfo->isActive = true;
	threadInfo->sleepTime = 1;
	threadInfo->ThreadId = 0;


	threadInfo->threadHandle = CreateThread(0, NULL, UpdateHunterThread,
		(void*)threadInfo, 0, &threadInfo->ThreadId);

}