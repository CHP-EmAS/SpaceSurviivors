#include "PlayerInputComponent.h"

#include "RigidBody.h"

#include "VectorExtension.h"
#include "Locator.h"

PlayerInputComponent::PlayerInputComponent(std::shared_ptr<GameObject> parent) : Component(parent) {}
PlayerInputComponent::~PlayerInputComponent() {}

void PlayerInputComponent::onUpdate(const sf::Time& deltaTime)
{
    if (auto parent = _parent.lock()) {
        sf::Vector2f movement(0.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            movement.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            movement.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            movement.x -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            movement.x += 1;
        }

        movement = normalize(movement);
        movement *= Locator::get<GameState>()->getPlayerAcceleration() * deltaTime.asSeconds();

        RigidBody* rigidBody = parent->getComponent<RigidBody>();
        if (rigidBody) {
            rigidBody->applyForce(movement);
        }

        rotateToMouse(deltaTime);
    }
}

void PlayerInputComponent::rotateToMouse(const sf::Time& deltaTime)
{
    if (auto parent = _parent.lock()) {
        sf::Vector2f rotateToPosition = Locator::get<SceneManager>()->getMousePosition();

        float targetAngle = getAngle(rotateToPosition - parent->getPosition());
        float deltaAngle = targetAngle - parent->getRotation();

        if (deltaAngle > 180.f) deltaAngle -= 360.f;
        if (deltaAngle < -180.f) deltaAngle += 360.f;

        float maxRotation = 240 * (Locator::get<GameState>()->getPlayerAcceleration() / 1500.f) * deltaTime.asSeconds();

        if (std::abs(deltaAngle) < maxRotation) {
            parent->setRotation(targetAngle);
        }
        else {
            if (deltaAngle > 0) {
                parent->rotate(maxRotation);
            }
            else {
                parent->rotate(-maxRotation);
            }
        }
    } else {
        std::cout << "Input Component has no parent!\n";
    }
}
