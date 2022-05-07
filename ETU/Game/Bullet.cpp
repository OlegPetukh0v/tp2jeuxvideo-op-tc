#include "stdafx.h"
#include "Bullet.h"

const float Bullet::BULLET_SPEED = 300;

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
	setScale(2, 2);
	setPosition(initialPosition);
	setRotation(90);
}

void Bullet::initialize(const sf::Texture& texture)
{
	Bullet::initialize(texture, sf::Vector2f(0, 0));
}
