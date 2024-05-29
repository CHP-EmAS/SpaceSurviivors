#pragma once

#include "Observable.h"

class GameObject;

class Observer {
public:
	virtual void onEvent(const GameObject* object, Observable::Event event) = 0;
};
