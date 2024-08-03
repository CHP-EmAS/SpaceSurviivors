#pragma once
#include "Component.h"
class ExperienceController : public Component
{
friend class Experience;

public:
	ExperienceController(std::shared_ptr<GameObject> parent);

	void onDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void onUpdate(const sf::Time& deltaTime) override;

private:
	sf::CircleShape circle;

	int amount;
	float collectionSpeed;

	bool moveToTarget;
	std::weak_ptr<GameObject> target;
};

