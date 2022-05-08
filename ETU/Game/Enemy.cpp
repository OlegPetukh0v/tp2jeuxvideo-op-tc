#include "stdafx.h"
#include "Enemy.h"
#include "Publisher.h"

const int Enemy::SHIP_SPEED = 120;
const int Enemy::INITIAL_HEALTH = 30;
const float Enemy::SHOOTING_COOLDOWN = 1.75f;

Enemy::Enemy()
{
	health = INITIAL_HEALTH;
	shootingCooldown = SHOOTING_COOLDOWN;
}

void Enemy::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
	setTexture(texture);
	setTextureRect(sf::IntRect(28, 917, 65, 96));
	setOrigin(sf::Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
	setPosition(initialPosition);
}

bool Enemy::init(const GameContentManager& contentManager)
{
    initialize(contentManager.getEnemiesTexture(), sf::Vector2f(0, 0));
    return true;
}

bool Enemy::update(float deltaT)
{
	shootingCooldown -= deltaT;
	if (shootingCooldown <= 0) {
		Publisher::notifySubscribers(Event::ENEMY_SHOOT, &getPosition());
		shootingCooldown = SHOOTING_COOLDOWN;
	}
	return false;
}

void Enemy::hit(int damage)
{
	health -= damage;
	if (health <= 0) {
		deactivate();
	}
}
