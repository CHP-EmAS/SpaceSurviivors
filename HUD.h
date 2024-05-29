#pragma once

#include "SFML/Graphics.hpp"
#include "Observer.h"
#include "GameState.h"

class HUD : public sf::Drawable, public Observer
{
public:
	HUD();

	void setGameState(GameState* gameState);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void updateScore(int score);
private:
	void onEvent(const GameObject* object, Observable::Event event) override;

	sf::Sprite scoreFrame;
	sf::Text scoreText;

	GameState* gameState;
};

