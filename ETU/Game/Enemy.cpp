#include "stdafx.h"
#include "Enemy.h"
#include "Publisher.h"
#include "Game.h"

const int Enemy::SHIP_SPEED = 120;
const int Enemy::INITIAL_HEALTH = 20;
const float Enemy::SHOOTING_COOLDOWN = 1.75f;
const float Enemy::HURT_TIME = 0.32f;

Enemy::Enemy()
{
	health = INITIAL_HEALTH;
	shootingCooldown = SHOOTING_COOLDOWN;
	hurtTime = 0;
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

void Enemy::activate()
{
	health = INITIAL_HEALTH;
	hurtTime = 0;
	setColor(sf::Color::White);
	float x = rand() % (Game::GAME_WIDTH - (int)getGlobalBounds().width);
	setPosition(x +(getGlobalBounds().width /2), -getGlobalBounds().height);
	GameObject::activate();
}

bool Enemy::update(float deltaT)
{
	hurtTime = std::fmax(0, hurtTime - deltaT);
	shootingCooldown -= deltaT;
	if (shootingCooldown <= 0) {
		Publisher::notifySubscribers(Event::ENEMY_SHOOT, &getPosition());
		shootingCooldown = SHOOTING_COOLDOWN;
	}

	this->move(sf::Vector2f(0, SHIP_SPEED * deltaT));

	float halfHeight = getGlobalBounds().height / 2;
	if (getPosition().y - halfHeight > Game::GAME_HEIGHT) setPosition(getPosition().x, -halfHeight);

	if (hurtTime > 0) {
		if (std::fmod(hurtTime, 0.16f) > 0.08f) setColor(sf::Color(255, 155, 80, 120));
		else setColor(sf::Color::White);  
	}
	
	return false;
}


void Enemy::hit(int damage)
{
	health -= damage;
	if (health <= 0) {
		deactivate();
	}
	else {
		hurtTime = HURT_TIME;
	}
}
