#pragma once
#include "stdafx.h"
#include "Bullet.h"

class EnemyBullet : public Bullet
{
	static const float BULLET_SPEED;
	static const int DAMAGE;
public:
	EnemyBullet();
	virtual bool update(float elapsedTime);
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
	bool collidesWith(const GameObject& other) const;

private:
	sf::Sound shootSfx;
};

