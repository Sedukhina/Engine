#pragma once

#include <functional>

// This class and this class inheritors methods can be invoked by input
class CInputComponent
{
public:
	CInputComponent() {};
	~CInputComponent() {};

	// Used for decltype only, does nothing
	void Action() {};
	float Axis() {};
private:

};


typedef std::function<void()> InputActionFunction;
typedef std::function<float()> InputAxisFunction;
//typedef std::_Mem_fn<void(__cdecl CInputComponent:: *)(void)> InputActionFunction;
//typedef decltype(std::mem_fn(&CInputComponent::Action)) InputActionFunction;
//typedef decltype(std::mem_fn(&CInputComponent::Axis)) InputAxisFunction;

/*
CInputComponent IC;
typedef decltype(std::bind(&CInputComponent::Action, IC)) InputActionFunction;
typedef decltype(std::bind(&CInputComponent::Axis, IC)) InputAxisFunction;*/
