#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "Publisher.h"
#include "Game.h"
#include <iostream>

const int Player::SHIP_SPEED = 360;
const float Player::SHOOTING_COOLDOWN = 0.25f;

Player::Player()
{
	shootingCooldown = SHOOTING_COOLDOWN;
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
	setOrigin(sf::Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
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
	shootingCooldown -= deltaT;
	if (inputs.fireBullet) {
		if (shootingCooldown <= 0) {
			Publisher::notifySubscribers(Event::PLAYER_SHOOT, this);
			shootingCooldown = SHOOTING_COOLDOWN;
		}
	}

	if (inputs.moveFactorX != 0 || inputs.moveFactorY != 0) {
		sf::Vector2f direction = sf::Vector2f(inputs.moveFactorX, inputs.moveFactorY);
		if (direction.x > 1) direction.x = 1;
		if (direction.x < -1) direction.x = -1;
		float angle = atan2(direction.y, direction.x);
		direction = sf::Vector2f(cos(angle) * SHIP_SPEED, sin(angle) * SHIP_SPEED);
		this->move(direction * deltaT);
	}

	float halfWidth = getGlobalBounds().width / 2;
	float halfHeight = getGlobalBounds().height / 2;

	if (getPosition().x - halfWidth < 0) setPosition(halfWidth, getPosition().y);
	if (getPosition().x + halfWidth > Game::GAME_WIDTH) setPosition(Game::GAME_WIDTH - halfWidth, getPosition().y);
	if (getPosition().y - halfHeight < 0) setPosition(getPosition().x, halfHeight);
	if (getPosition().y + halfHeight > Game::GAME_HEIGHT) setPosition(getPosition().x, Game::GAME_HEIGHT - halfHeight);


	return true;
}
