#pragma once

#include <unordered_map>
#include <memory>
#include <typeindex>

#include "SceneManager.h"
#include "GraphicService.h"
#include "SoundManager.h"
#include "HighscoreService.h"

#include "World.h"
#include "GameObjectFactory.h"
#include "CollisionGrid.h"
#include "EventDispatcher.h"

class Locator
{
public:
	template<typename T>
	static void provideGlobal(std::shared_ptr<T>& obj) {
		instances[std::type_index(typeid(T))] = obj;
	}
	
	template<typename T>
	static std::shared_ptr<T> get() {
		auto it = instances.find(std::type_index(typeid(T)));
		if (it != instances.end()) {
			if (auto ptr = it->second.lock()) {
				return std::static_pointer_cast<T>(ptr);
			}
		}

		throw std::runtime_error("LOCATOR ERROR: Object of the requested type is not available.");
	}

private:

	static std::unordered_map<std::type_index, std::weak_ptr<void>> instances;
};
