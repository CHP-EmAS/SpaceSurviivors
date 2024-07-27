#pragma once

#include <vector>
#include "Event.h"

class Observer;

class Observable
{
public:
	Observable();

	void addObserver(Observer& observer);
	void removeObserver(Observer& observer);

	void clearObservers();

	~Observable();

protected:
	void broadcastEvent(const Event event);

private:
	std::vector<Observer*> _listeners;
};

