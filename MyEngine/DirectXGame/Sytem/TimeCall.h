#pragma once
#include <functional>

class TimeCall
{
public:

	TimeCall(std::function<void(void)> func, uint32_t time);
	~TimeCall();

	void Update();

	bool IsFinished() { return isFinished_; }

private:

	//
	std::function<void(void)> func_;

	//
	uint32_t time_;

	//
	bool isFinished_ = false;

};

