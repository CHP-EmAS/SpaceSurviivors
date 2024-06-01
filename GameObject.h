#pragma once

#include <SFML/Graphics.hpp>

#include "Collider.h"
#include "Controller.h"
#include "GameState.h"

class SpatialPartitionGrid;

class GameObject : public sf::Transformable, public sf::Drawable
{
	friend class SpatialPartitionGrid;

public:
	enum ObjectType {
		O_Player,
		O_Bullet,
		O_Asteroid,
		O_Explosion,
		O_None
	};

	enum Interaction {
		BulletCollision,
		AsteroidCollision,
		PlayerCollision
	};

	GameObject(ObjectType type);

	virtual void update(sf::Time deltaTime, GameState& state);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void interact(Interaction action, GameObject& interactor);

	//Spatial Partition Grid
	virtual void spawOnGrid(SpatialPartitionGrid* grid, sf::Vector2f position);
	virtual void markForDespawn();

	void setController(Controller* newController);
	Controller* getController();

	Collider* getCollider();
	ObjectType getType() const;

	~GameObject();
protected:
	sf::Sprite sprite;
	Collider collider;

	Controller* controller;

	SpatialPartitionGrid* grid;
	bool managedByGrid;
	bool markedForDespawn;
private:
	const ObjectType type;

	//Spatial Partition Grid
	GameObject* prevObject;
	GameObject* nextObject;
};

