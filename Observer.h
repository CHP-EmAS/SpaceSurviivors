#pragma once

#include "Observable.h"
#include "Event.h"

class Observer {
public:
	virtual void onEvent(const Event event) = 0;
};
