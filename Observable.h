#pragma once

class Observer;
class GameObject;

class Observable
{
public:
	enum Event {
		GRID_OBJECT_SPAWNED,
		GRID_OBJECT_DESPAWNED,
		GRID_OBJECT_OUT_OF_BOUNDS,

		GAME_STATE_UPDATED
	};

	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

	~Observable();

protected:
	void notifyObservers(const GameObject* object, Event event);

private:
	struct ObserverNode {
		ObserverNode* next;
		Observer* observer;
	};

	ObserverNode* head;
};

