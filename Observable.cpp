#include "Observable.h"
#include "Observer.h"

Observable::Observable()
{

}

Observable::~Observable()
{

}

void Observable::addObserver(Observer& observer)
{
	_listeners.push_back(&observer);
}

void Observable::removeObserver(Observer& observer)
{
	auto elementToDelete = std::find(_listeners.begin(), _listeners.end(), &observer);
	if (elementToDelete != _listeners.end()) {
		_listeners.erase(elementToDelete);
	}
}

void Observable::clearObservers()
{
	_listeners.clear();
}

void Observable::broadcastEvent(const Event event)
{
	for (auto observer : _listeners) {
		observer->onEvent(event);
	}
}
