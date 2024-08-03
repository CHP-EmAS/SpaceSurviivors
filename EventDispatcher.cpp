#include "EventDispatcher.h"

std::unordered_map<EventType, std::vector<EventDispatcher::HandlerEntry>> EventDispatcher::handlers;
EventHandlerID EventDispatcher::nextHandlerID = 0;

EventHandlerID EventDispatcher::registerHandler(EventType type, std::function<void(const EventInfo&)> handler)
{
    EventHandlerID id = nextHandlerID++;
    handlers[type].push_back({ id, handler });
    return id;
}

void EventDispatcher::unregisterHandler(EventType type, EventHandlerID id)
{
    if (handlers.find(type) != handlers.end()) {
        auto& handlerList = handlers[type];
        handlerList.erase(std::remove_if(handlerList.begin(), handlerList.end(),
            [id](const HandlerEntry& entry) { return entry.id == id; }),
            handlerList.end());
    }
}

void EventDispatcher::dispatch(const Event& event)
{
    if (handlers.find(event.type) != handlers.end()) {
        for (const auto& entry : handlers[event.type]) {
            entry.handler(event.info);
        }
    }
}
