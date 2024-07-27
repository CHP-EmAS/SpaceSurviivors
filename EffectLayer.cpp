#include "EffectLayer.h"
#include "Defines.h"

EffectLayer::EffectLayer()
{
	validArea.left = -50.f;
	validArea.top = -50.f;
	validArea.width = WINDOW_SIZE + 100.f;
	validArea.height = WINDOW_SIZE + 100.f;
}

void EffectLayer::add(std::shared_ptr<GameObject> object)
{
	objects.push_back(object);
	broadcastEvent(Event::Event(Event::GRID_OBJECT_SPAWNED, object));
}

void EffectLayer::clear()
{
	for (auto& obj : objects) {
		obj->despawn();
		broadcastEvent(Event::Event(Event::GRID_OBJECT_DESPAWNED, obj));
	}

	objects.clear();
}

void EffectLayer::updateObjects(sf::Time deltaTime, GameState& state)
{
	auto it = objects.begin();

	while (it != objects.end())
	{
		std::shared_ptr<GameObject> obj = *it;

		//Update
		obj->update(deltaTime, state);
	
		//Object requests despawn
		if (!obj->isEnabled()) {
			broadcastEvent(Event::Event(Event::GRID_OBJECT_DESPAWNED, obj));
			it = objects.erase(it);
			continue;
		}

		if (!validArea.contains(obj->getPosition())) {
			obj->despawn();
			broadcastEvent(Event::Event(Event::GRID_OBJECT_OUT_OF_BOUNDS, obj));
			it = objects.erase(it);
			continue;
		}

		++it;
	}
}

void EffectLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& obj : objects) {
		target.draw(*obj, states);
	}
}
