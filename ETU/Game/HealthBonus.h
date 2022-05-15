#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "GameContentManager.h"

class HealthBonus : public GameObject
{
	static const int HEALTH;
	static const int SPEED;
public:
	virtual bool update(float elapsedTime);
	virtual void activate() override;
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
	virtual void init(const GameContentManager& contentManger);
protected:
	GameContentManager contentManager;
};

