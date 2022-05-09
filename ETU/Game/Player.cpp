#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "Publisher.h"
#include "Game.h"
#include "BitmaskManager.h"
#include <iostream>

const int Player::SHIP_SPEED = 360;
const float Player::SHOOTING_COOLDOWN = 0.25f;
const int Player::CANON_OFFSET = 14;
const int Player::INITIAL_LIFE = 300;
const float Player::HURT_TIME = 0.5f;

Player::Player()
{
	life = INITIAL_LIFE;
	shootingCooldown = SHOOTING_COOLDOWN;
	shootLeft = true;
	hurtTime = 0;
}

Player::~Player()
{
}

void Player::draw(sf::RenderWindow& window) const
{
	window.draw(*this);

	/*sf::RectangleShape shape(sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height));
	shape.setOutlineColor(getDebugColor());
	shape.setOutlineThickness(2);
	shape.setPosition(getPosition() - sf::Vector2f(getGlobalBounds().width * 0.5f, getGlobalBounds().height * 0.5f));
	shape.setFillColor(sf::Color::Transparent);

	window.draw(shape);*/
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
	activate();
	Publisher::addSubscriber(*this, Event::PLAYER_HIT);
	this->contentManager = contentManager;
	this->initialize(contentManager.getMainCharacterTexture(), sf::Vector2f(Game::GAME_WIDTH/2,Game::GAME_HEIGHT - 100));
	return true;
}

bool Player::update(float deltaT, const Inputs& inputs)
{
	hurtTime = std::fmax(0, hurtTime - deltaT);
	shootingCooldown -= deltaT;
	if (inputs.fireBullet) {
		if (shootingCooldown <= 0) {
			float offset = CANON_OFFSET;
			if (shootLeft) offset *= -1;
			shootLeft = !shootLeft;
			// TODO: add back when fixed
			//Publisher::notifySubscribers(Event::PLAYER_SHOOT, &sf::Vector2f(getPosition().x + offset, getPosition().y));
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

	if (hurtTime > 0) {
		if (std::fmod(hurtTime, 0.16f) > 0.08f) setColor(sf::Color(255, 50, 50, 255));
		else setColor(sf::Color::White);
	}

	return true;
}

void Player::notify(Event event, const void* data) {
	if (event == Event::PLAYER_HIT) {
		life -= *(int*)data;
		hurtTime = HURT_TIME;
		std::cout << life << std::endl;
	}
}