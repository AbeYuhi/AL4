#include "TimeCall.h"

TimeCall::TimeCall(std::function<void(void)> func, uint32_t time) {
	func_ = func;
	time_ = time;
}

TimeCall::~TimeCall(){}

void TimeCall::Update() {

	if (isFinished_) {
		return;
	}

	time_--;
	if (time_ <= 0) {
		isFinished_ = true;
		func_();
	}

}