#pragma once
#include <Windows.h>
#include "../Physics/PhysicsEngine.h"
#include "ThreadManager.h"
#include "../EntityManager/EntityManager.h"
#include "../ImGui/PanelManager.h"
#include "../Maze/MazeManager.h"
#include "../Maze/Hunter/Hunter.h"

struct ApplicationThread // SoftBody Struct Infor
{
	PhysicsEngine* physicsEngine;
    ThreadManager* manager;
    EntityManager* entityManager;
    PanelManager* panelmanager;


    double desiredUpdateTime = 0.0;  
    bool isThreadActive = false;	
    bool isActive = true;
    DWORD sleepTime;	

    DWORD ThreadId = 0;
    HANDLE threadHandle = 0;
    CRITICAL_SECTION cs;

};


struct HunterThread
{
    Hunter* hunterObject;
    MazeManager* mazeController;
    double desiredUpdateTime = 1.0f/60.0f;
    bool isThreadActive = false;
    bool isActive = true;
    DWORD ThreadId = 0;
    DWORD sleepTime;
    HANDLE threadHandle = 0;
    CRITICAL_SECTION cs;
};