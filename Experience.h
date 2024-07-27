#pragma once

#include "GameObject.h"

class Experience : public GameObject 
{
public:
	Experience();
	~Experience();

	void initializeComponents() override;
	void reinitialize(int amount);

	void trigger(std::weak_ptr<GameObject> target);
	void update(sf::Time deltaTime, GameState& state) override;
	
	bool isTriggerd() const;
	int getAmount() const;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::CircleShape circle;

	int amount;
	float collectionSpeed;

	bool moveToTarget;
	std::weak_ptr<GameObject> target;
};

