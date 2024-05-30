#pragma once

#include "Observable.h"

class GameObject;

class Observer {
public:
	virtual void onEvent(const Observable::Event event, const Observable::EventInfo info) = 0;
};
