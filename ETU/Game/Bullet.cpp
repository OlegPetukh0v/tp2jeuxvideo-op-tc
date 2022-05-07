#include "stdafx.h"
#include "Bullet.h"

const float Bullet::BULLET_SPEED = 420;

Bullet::Bullet()
{
}

bool Bullet::update(float elapsedTime)
{
	move(sf::Vector2f(0, -BULLET_SPEED * elapsedTime));
	if (getPosition().y < 0) {
		GameObject::deactivate();
		return true;
	}

	return false;
}

void Bullet::activate() {
	GameObject::activate();
	// shootSfx.play();
}

void Bullet::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
	setTexture(texture);
	setTextureRect(sf::IntRect(264, 106, 16, 5));
	setOrigin(sf::Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
	setScale(2, 2);
	setPosition(initialPosition);
	setRotation(90);
}