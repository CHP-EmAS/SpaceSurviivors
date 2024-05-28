#pragma once

#include "GameObject.h"
#include "Observable.h"

class Observer {
public:
	virtual void onEvent(const GameObject& object, Observable::Event event) = 0;
};
