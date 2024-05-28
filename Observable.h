#pragma once

#include "GameObject.h"

class Observer;

class Observable
{
public:
	enum Event {
		GRID_OBJECT_SPAWNED,
		GRID_OBJECT_DESPAWNED,
		GRID_OBJECT_OUT_OF_BOUNDS
	};

	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

	~Observable();

protected:
	void notifyObservers(const GameObject& object, Event event);

private:
	struct ObserverNode {
		ObserverNode* next;
		Observer* observer;
	};

	ObserverNode* head;
};

