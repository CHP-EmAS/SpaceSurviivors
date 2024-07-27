#pragma once

#include <unordered_map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Event.h"
#include "Collider.h"
#include "Component.h"
#include "GameState.h"

enum ObjectType {
	O_Player,
	O_Bullet,
	O_Asteroid,
	O_Explosion,
	O_Experience,
	O_None
};

enum ObjectLayer {
	L_Collision,
	L_Effect
};

class GameObject : public std::enable_shared_from_this<GameObject>, public sf::Transformable, public sf::Drawable
{
public:
	const ObjectType type;

	GameObject(ObjectType type);
	virtual ~GameObject() = default;

	virtual void initializeComponents() = 0;

	virtual void update(sf::Time deltaTime, GameState& state) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
	virtual void interact(const Event event);

	void spaw(sf::Vector2f spawnPosition, ObjectLayer layer);
	void despawn();
	bool isEnabled() const;

	template<typename T>
	void registerComponent(std::unique_ptr<T> component) {
		components[typeid(T)] = std::move(component);
	}

	template<typename T>
	void removeComponent() {
		components.erase(typeid(T));
	}

	template<typename T>
	T* getComponent() const {
		auto it = components.find(typeid(T));
		if (it != components.end()) {
			return dynamic_cast<T*>(it->second.get());
		}
		return nullptr;
	}

	template<typename T>
	bool hasComponent() const {
		return components.contains(typeid(T));
	}

protected:
	bool enabled;

private:
	std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
};


