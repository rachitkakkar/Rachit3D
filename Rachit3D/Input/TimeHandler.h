#pragma once
/* TIMEHANDLER CLASS: A UTILITY TO CALCULATE THE DELTATIME */

class TimeHandler
{
private:
	float m_CurrentFrameTime;
	float m_LastFrameTime;

public:
	TimeHandler();
	~TimeHandler();

	float GetDeltaTime();
};