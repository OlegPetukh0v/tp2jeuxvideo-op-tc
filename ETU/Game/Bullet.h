#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "GameContentManager.h"

class Bullet : public GameObject
{
	static const float BULLET_SPEED;
	static const int DAMAGE;
	static const int ROTATION;

public:
	Bullet();
	virtual bool update(const float elapsedTime);
	virtual void activate() override;
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
	virtual void init(const GameContentManager& contentManger);
	virtual int getDamage() const;

};
