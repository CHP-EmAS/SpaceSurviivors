#include "Observable.h"
#include "Observer.h"

void Observable::addObserver(Observer* observer)
{
	ObserverNode* newNode = new ObserverNode();
	newNode->observer = observer;
	newNode->next = head;
	head = newNode;
}

void Observable::removeObserver(Observer* observer)
{
	if (head == nullptr)
		return;

	if (head->observer == observer) {
		ObserverNode* toDelete = head;
		head = head->next;
		delete toDelete;
		return;
	}

	ObserverNode* cursor = head;
	while (cursor->next != nullptr) {
		if (cursor->next->observer == observer) {
			ObserverNode* toDelete = cursor->next;
			cursor->next = cursor->next->next;
			delete toDelete;
			return;
		}
		cursor = cursor->next;
	}
}

void Observable::notifyObservers(const GameObject& object, Event event)
{
	ObserverNode* cursor = head;
	while (cursor != nullptr) {
		cursor->observer->onEvent(object, event);
		cursor = cursor->next;
	}
}

Observable::~Observable()
{
	while (head != nullptr) {
		ObserverNode* toDelete = head;
		head = head->next;
		delete toDelete;
	}
}