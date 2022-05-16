#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "GameContentManager.h"
#include "Player.h"

class Bonus : public GameObject
{
public:
	static const int PICKUP_VOLUME;
	static const int SPEED;
	static const int SCALE;

	virtual bool update(float elapsedTime);
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
	virtual void onPick(Player& player);

protected:
	sf::Sound pickupSound;
};
