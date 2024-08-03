#pragma once

#include <SFML/Graphics.hpp>

#include "Component.h"

class SpriteRenderer : public Component {
public:
	SpriteRenderer(std::shared_ptr<GameObject> parent);
	~SpriteRenderer();

	void onDraw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void setSprite(sf::Sprite sprite);
	sf::Sprite* getSprite();

private:
	sf::Sprite sprite;
	
};