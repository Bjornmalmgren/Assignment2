#include "Timer.h"
void Timer::startTimer() {
	clock = std::chrono::system_clock::now();
}
void Timer::stopTimerMicro() {
	auto sClock = std::chrono::system_clock::now();
	time = std::chrono::duration_cast<std::chrono::microseconds>(sClock - clock).count();
}

void Timer::stopTimerNano() {
	auto sClock = std::chrono::system_clock::now();
	time = std::chrono::duration_cast<std::chrono::nanoseconds>(sClock - clock).count();
}
