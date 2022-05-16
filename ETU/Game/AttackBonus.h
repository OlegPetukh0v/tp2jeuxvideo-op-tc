#pragma once
#include "Bonus.h"
#include "stdafx.h"

class AttackBonus :
    public Bonus
{
public:
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
	virtual void init(const GameContentManager& gameContentManager);
	virtual void onPick(Player& player);
};
