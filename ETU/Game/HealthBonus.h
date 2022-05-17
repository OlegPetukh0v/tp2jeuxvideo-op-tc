#pragma once
#include "stdafx.h"
#include "Bonus.h"

class HealthBonus : public Bonus
{
public:
	static const int HEALTH;

	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
	virtual void init(const GameContentManager& gameContentManager);
	virtual void onPick(Player& player);

};
