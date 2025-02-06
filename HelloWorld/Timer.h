#pragma once
#include <chrono>
class Timer
{

public:
	std::chrono::system_clock::time_point clock;
	long long time;
	void startTimer();
	void stopTimer();
};

