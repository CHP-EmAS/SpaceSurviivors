#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "Event.h"

using EventHandlerID = size_t;

class EventDispatcher
{
public:
    static EventHandlerID registerHandler(EventType type, std::function<void(const EventInfo&)> handler);
    static void unregisterHandler(EventType type, EventHandlerID id);

    static void dispatch(const Event& event);

private:
    struct HandlerEntry {
        EventHandlerID id;
        std::function<void(const EventInfo&)> handler;
    };

    static std::unordered_map<EventType, std::vector<HandlerEntry>> handlers;
    static EventHandlerID nextHandlerID;
};

