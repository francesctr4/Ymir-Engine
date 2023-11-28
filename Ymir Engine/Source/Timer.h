#ifndef __TIMER_H__
#define __TIMER_H__

#include "Globals.h"
#include "External/SDL/include/SDL.h"

// Enumeration for timer states
enum class TimerState
{
	STOPPED,
	RUNNING,
	PAUSED
};

class Timer
{
public:

	// Constructor
	Timer();

	void Start();
	void Resume();
	void Pause();
	void Stop();

	void StepFrame(float dt);
	void SetTimeScale(float scale);

	float ReadMS();
	float ReadSec();

	TimerState GetState() const;

private:

	TimerState currentState; 

	float started_at;
	float stopped_at;

	float timeScale;

};

#endif //__TIMER_H__