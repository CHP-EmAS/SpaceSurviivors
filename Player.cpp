#include "Player.h"
#include "Locator.h"

#include "VectorExtension.h"

#include "RigidBody.h"
#include "SpriteRenderer.h"
#include "PlayerInputComponent.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Explosion.h"
#include "PlayerController.h"
#include "GridComponent.h"

Player::Player() : GameObject(ObjectType::O_Player) 
{
}

void Player::initializeComponents()
{
	PlayerController controller(shared_from_this());
	RigidBody rigidBody(shared_from_this());
	PlayerInputComponent input(shared_from_this());
	SpriteRenderer spriteRenderer(shared_from_this());
	BoxCollider collider(shared_from_this(), 35, 25);

	GridComponent grid(shared_from_this(), GRID::G_DYNAMIC);

	sf::Sprite playerSprite = sf::Sprite(Locator::get<GraphicService>()->getTexture(GraphicService::Player));
	spriteRenderer.setSprite(playerSprite);

	rigidBody.setMaxSpeed(1800.f);
	rigidBody.setFriction(0.01f);
	rigidBody.setBoundingBox(sf::FloatRect(0, 0, WINDOW_SIZE, WINDOW_SIZE));

	sf::Vector2f origin = sf::Vector2f(playerSprite.getTextureRect().getSize().x / 2 - 5, playerSprite.getTextureRect().getSize().y / 2);
	setOrigin(origin);

	collider.setPosition(origin);

	controller.bulletSpawnPoint.x = playerSprite.getTextureRect().getSize().x - 5;
	controller.bulletSpawnPoint.y = static_cast<float>(playerSprite.getTextureRect().getSize().y) / 2.f;

	registerComponent(std::make_unique<RigidBody>(rigidBody));
	registerComponent(std::make_unique<PlayerInputComponent>(input));
	registerComponent(std::make_unique<SpriteRenderer>(spriteRenderer));
	registerComponent(std::make_unique<BoxCollider>(collider));
	registerComponent(std::make_unique<PlayerController>(controller));
	registerComponent(std::make_unique<GridComponent>(grid));
}