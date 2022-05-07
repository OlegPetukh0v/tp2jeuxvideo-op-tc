#pragma once
#include "stdafx.h"
#include "Bullet.h"

class EnemyBullet : public Bullet
{
	static const float BULLET_SPEED;
public:
	EnemyBullet();
	virtual bool update(float elapsedTime);
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;

private:
	sf::Sound shootSfx;
};

