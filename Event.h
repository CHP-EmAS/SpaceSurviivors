#pragma once

#include <memory>
#include <variant>

class GameObject;

enum class EventType {
	PLAYER_COLLISION,
	ASTEROID_COLLISION,
	BULLET_COLLISION,

	OBJECT_SPAWNED,
	OBJECT_DESPAWNED,

	SCORE_UPDATED,
	EXPERIENCE_UPDATED,
	MAX_EXPERIENCE_UPDATED,
	LEVEL_UPDATED,
	HEALTH_UPDATED,
	MAX_HEALTH_UPDATED,

	GAME_OVER
};

struct GameObjectEventInfo {
	std::shared_ptr<GameObject>& ref;
};

struct IntegerEventInfo {
	const int value;
};

struct FloatEventInfo {
	const float value;
};

using EventInfo = std::variant<
	IntegerEventInfo,
	FloatEventInfo,
	GameObjectEventInfo
>;

struct Event {
	EventType type;
	EventInfo info;

	Event(EventType type, EventInfo info)					: type(type), info(info) {}
	Event(EventType type)									: type(type), info(IntegerEventInfo(0)) {}
	Event(EventType type, int value)						: type(type), info(IntegerEventInfo(value)) {}
	Event(EventType type, float value)						: type(type), info(FloatEventInfo(value)) {}
	Event(EventType type, std::shared_ptr<GameObject>& ref)	: type(type), info(GameObjectEventInfo(ref)) {}
};



