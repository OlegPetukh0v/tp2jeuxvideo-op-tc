#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include <iostream>

const int Player::SHIP_SPEED = 320;

Player::Player()
{
}

Player::~Player()
{
}

void Player::draw(sf::RenderWindow& window) const
{
	window.draw(*this);
}

void Player::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
	setTexture(texture);
	setTextureRect(sf::IntRect(269, 47, 26, 29));
	setScale(2, 2);
	setPosition(initialPosition);
}

bool Player::init(const GameContentManager& contentManager)
{
	this->contentManager = contentManager;
	this->initialize(contentManager.getMainCharacterTexture(), sf::Vector2f(100,100));
	return true;
}

bool Player::update(float deltaT)
{
	return false;
}

bool Player::update(float deltaT, const Inputs& inputs)
{
	std::cout << inputs.moveFactorX << inputs.moveFactorY << std::endl;
	if (inputs.moveFactorX == 0 && inputs.moveFactorY == 0) return true;
	sf::Vector2f direction = sf::Vector2f(inputs.moveFactorX, inputs.moveFactorY);
	if (direction.x > 1) direction.x = 1;
	if (direction.x < -1) direction.x = -1;
	float angle = atan2(direction.y, direction.x);
	direction = sf::Vector2f(cos(angle) * SHIP_SPEED, sin(angle) * SHIP_SPEED);
	this->move(direction * deltaT);

	return true;
}
