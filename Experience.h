#pragma once

#include "GameObject.h"

class Experience : public GameObject 
{
public:
	Experience();
	~Experience();

	void initializeComponents() override;
	void reinitialize(int amount);

	void trigger(std::weak_ptr<GameObject> target);
	
	bool isTriggerd() const;
	int getAmount() const;
};

