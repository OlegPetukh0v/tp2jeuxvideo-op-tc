#pragma once
#include "stdafx.h"
#include "Bullet.h"

class EnemyBullet : public Bullet
{
	static const float BULLET_SPEED;
	static const int DAMAGE;
	static const int ROTATION;

public:
	EnemyBullet();
	virtual void activate() override;
	virtual bool update(const float elapsedTime);
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
	virtual void init(const GameContentManager& contentManager) override;

private:
	sf::Sound shootSfx;

};

