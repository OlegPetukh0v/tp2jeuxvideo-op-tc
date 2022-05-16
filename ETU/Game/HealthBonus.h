#pragma once
#include "stdafx.h"
#include "GameObject.h"

class HealthBonus : public GameObject
{
public:
	static const int HEALTH;
	static const int PICKUP_VOLUME;
	static const int SPEED;
	static const int SCALE;

	virtual bool update(float elapsedTime);
	virtual void deactivate() override;
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
	virtual void init(const GameContentManager& gameContentManager);
protected:
	sf::Sound pickupSound;
};

