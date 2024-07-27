#pragma once

#include <list>
#include <memory>

#include <SFML/Graphics.hpp>

#include "GameObject.h"

class EffectLayer : public sf::Drawable, public Observable
{
public:
	EffectLayer();

	void add(std::shared_ptr<GameObject> object);
	void clear();

	void updateObjects(sf::Time deltaTime, GameState& state);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::list<std::shared_ptr<GameObject>> objects;
	
	sf::FloatRect validArea;
};

