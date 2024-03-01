#pragma once
#include "ThreadStruct.h"

extern ApplicationThread* applicationThreadExtern = new ApplicationThread();
extern HunterThread* hunterThreadExtern = new HunterThread();

DWORD WINAPI UpdateApplicationThread(LPVOID lpParameter)
{

	ApplicationThread* threadPointer = (ApplicationThread*)lpParameter;

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



			
				//threadPointer->manager->Update(deltaTime);
				threadPointer->entityManager->Update(deltaTime);
				threadPointer->physicsEngine->Update(deltaTime);


				

			Sleep(threadPointer->sleepTime);
		}

	}


	return 0;

}

void InitializeApplicationThread(float time)
{
	
	applicationThreadExtern->desiredUpdateTime = time;
	applicationThreadExtern->physicsEngine = &PhysicsEngine::GetInstance();
	applicationThreadExtern->manager = &ThreadManager::Getinstance();
	applicationThreadExtern->entityManager = &EntityManager::GetInstance();
	applicationThreadExtern->panelmanager = &PanelManager::GetInstance();
	applicationThreadExtern->isActive = true;
	applicationThreadExtern->sleepTime = 1;

	applicationThreadExtern->threadHandle = CreateThread(
		NULL,						
		0,							
		UpdateApplicationThread,		
		(void*)applicationThreadExtern,			
		0,						
		&applicationThreadExtern->ThreadId);		

	// SoftBody Thread
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
				threadPointer->hunterObject->UpdateHunterPosition(threadPointer->desiredUpdateTime);

			}


			Sleep(0);
		}

	}


	return 0;

}

void IntializeHunterThread(float time)
{
	hunterThreadExtern->mazeController = &MazeManager::GetInstance();
	hunterThreadExtern->hunterObject = new Hunter();
	hunterThreadExtern->isActive = true;
	hunterThreadExtern->sleepTime = 1;
	hunterThreadExtern->ThreadId = 5;


	hunterThreadExtern->threadHandle = CreateThread(0, NULL, UpdateHunterThread,
		(void*)hunterThreadExtern, 0, &hunterThreadExtern->ThreadId);


}