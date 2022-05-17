#include "stdafx.h"
#include "EnemyBullet.h"
#include "Bullet.h"
#include "Game.h"
#include "Publisher.h"

const float EnemyBullet::BULLET_SPEED = 500;
const int EnemyBullet::DAMAGE = 10;
const int EnemyBullet::ROTATION = 270;

EnemyBullet::EnemyBullet()
{
}

void EnemyBullet::activate()
{
	Bullet::activate();
}

bool EnemyBullet::update(const float elapsedTime)
{
	move(sf::Vector2f(0, BULLET_SPEED * elapsedTime));
	if (getPosition().y > Game::GAME_HEIGHT) {
		GameObject::deactivate();
		return true;
	}

	return false;
}

void EnemyBullet::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
	deactivate();
	setTexture(texture);
	setTextureRect(sf::IntRect(287, 106, 16, 5));
	setOrigin(sf::Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
	setScale(2, 2);
	setPosition(initialPosition);
	setRotation(ROTATION);
}

void EnemyBullet::init(const GameContentManager& contentManager)
{
	this->initialize(contentManager.getMainCharacterTexture(), sf::Vector2f(0, 0));
}
