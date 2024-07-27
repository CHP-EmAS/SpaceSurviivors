#include "SpriteRenderer.h"
#include "Locator.h"

SpriteRenderer::SpriteRenderer(std::shared_ptr<GameObject> parent) : Component(parent) {}

SpriteRenderer::~SpriteRenderer() {}

void SpriteRenderer::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(sprite, states);
}

void SpriteRenderer::setSprite(sf::Sprite sprite)
{
	this->sprite = sprite;
}

sf::Sprite* SpriteRenderer::getSprite()
{
	return &sprite;
}
