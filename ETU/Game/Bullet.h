#pragma once
#include "stdafx.h"
#include "GameObject.h"

class Bullet : public GameObject
{
	static const float BULLET_SPEED;
	static const int DAMAGE;
public:
	Bullet();
	virtual bool update(float elapsedTime);
	virtual void activate() override;
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
	virtual int getDamage();

private:
	sf::Sound shootSfx;
};

