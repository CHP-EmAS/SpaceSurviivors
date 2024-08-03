#pragma once

#include "GameState.h"
#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();

	void initializeComponents() override;
};

