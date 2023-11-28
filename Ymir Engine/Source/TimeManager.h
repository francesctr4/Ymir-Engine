#pragma once

#include "Timer.h"

class TimeManager {
public:

    // Static members
	static Timer graphicsTimer;
	static Timer gameTimer;

    static float DeltaTime;
    static int FrameCount;

private:

    // Deleted default constructor to prevent instantiation
    TimeManager() = delete;

    // Deleted copy constructor to prevent copying
    TimeManager(const TimeManager&) = delete;

    // Deleted assignment operator to prevent assignment
    TimeManager& operator=(const TimeManager&) = delete;

};