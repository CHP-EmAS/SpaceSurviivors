#pragma once

#include <memory>
#include <variant>

class GameObject;

struct GameObjectWrapper {
	std::shared_ptr<GameObject> ref;
};

struct IntUpdate {
	const int value;
};

struct FloatUpdate {
	const float value;
};

class Event {
public:
	enum Type {
		PlayerCollision,
		AsteroidCollision,
		BulletCollision,

		GRID_OBJECT_SPAWNED,
		GRID_OBJECT_DESPAWNED,
		GRID_OBJECT_OUT_OF_BOUNDS,

		SCORE_UPDATED,
		EXPERIENCE_UPDATED,
		MAX_EXPERIENCE_UPDATED,
		LEVEL_UPDATED,
		HEALTH_UPDATED,
		MAX_HEALTH_UPDATED,

		GAME_OVER
	};


	Event(Type eventType) : type(eventType), info(IntUpdate(0)) {}
	Event(Type eventType, int value) : type(eventType), info(IntUpdate(value)) {}
	Event(Type eventType, float value) : type(eventType), info(FloatUpdate(value)) {}
	Event(Type eventType, std::shared_ptr<GameObject> value) : type(eventType), info(GameObjectWrapper{ value }) {}

	const Type type;

	const std::variant<
		IntUpdate,
		FloatUpdate,
		GameObjectWrapper
	> info;
};



