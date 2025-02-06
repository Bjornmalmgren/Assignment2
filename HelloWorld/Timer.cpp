#include "Timer.h"
void Timer::startTimer() {
	clock = std::chrono::system_clock::now();
}
void Timer::stopTimer() {
	auto sClock = std::chrono::system_clock::now();
	time = std::chrono::duration_cast<std::chrono::microseconds>(sClock - clock).count();
}
