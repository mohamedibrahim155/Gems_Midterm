#pragma once
#include <Windows.h>
//#include "../MazeManager.h"


class Hunter;
class MazeManager;

class HunterThread
{
public:

    Hunter* hunterObject = nullptr;
    MazeManager* mazeController = nullptr;
    bool* playMode =nullptr;
    double desiredUpdateTime = 1.0f / 60.0f;
    bool isThreadActive = false;
    bool isActive = true;
    DWORD ThreadId = 0;
    DWORD sleepTime;
    HANDLE threadHandle = 0;
    CRITICAL_SECTION cs;
};