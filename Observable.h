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

		SCORE_UPDATED,
		EXPERIENCE_UPDATED,
		MAX_EXPERIENCE_UPDATED,
		LEVEL_UPDATED,
	};

	struct EventInfo {
		GameObject* object = nullptr;
		int value = 0;
	};

	void addObserver(Observer* observer);
	void removeObserver(Observer* observer);

	~Observable();

protected:
	void notifyObservers(const Event event, const EventInfo info);

private:
	struct ObserverNode {
		ObserverNode* next;
		Observer* observer;
	};

	ObserverNode* head;
};

