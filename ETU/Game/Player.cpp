#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "Publisher.h"
#include "Game.h"
#include "Hud.h"
#include <iostream>

const int Player::SHIP_SPEED = 360;
const float Player::SHOOTING_COOLDOWN = 0.2f;
const int Player::SHOOTING_VOLUME = 30;
const int Player::CANON_OFFSET = 14;
// TODO: remettre a 300
const int Player::INITIAL_LIFE = 30;
const float Player::HURT_TIME = 0.5f;
const unsigned int Player::SCORE_INCREASE_KILL = 1000;

Player::Player()
	: Character(INITIAL_LIFE)
{
	shootingCooldown = SHOOTING_COOLDOWN;
	hurtTime = 0;
	score = 0;
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
	activate();
	currentState = State::SHIP;
	addAnimation<State::SHIP, ShipAnimation>(contentManager);
	Publisher::addSubscriber(*this, Event::PLAYER_HIT);
	Publisher::addSubscriber(*this, Event::ENEMY_KILLED);
	setTexture(texture);
	setTextureRect(sf::IntRect(269, 47, 26, 29));
	setOrigin(sf::Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
	setScale(2, 2);
	setPosition(initialPosition);
}

bool Player::init(const GameContentManager& contentManager)
{
	this->contentManager = contentManager;
	this->initialize(contentManager.getMainCharacterTexture(), sf::Vector2f(Game::GAME_WIDTH/2,Game::GAME_HEIGHT - 100));
	return true;
}

bool Player::uninit()
{
	Publisher::removeSubscriber(*this, Event::PLAYER_HIT);
	Publisher::removeSubscriber(*this, Event::ENEMY_KILLED);
	return true;
}

bool Player::update(float deltaT, const Inputs& inputs)
{
	hurtTime = std::fmax(0, hurtTime - deltaT);
	shootingCooldown -= deltaT;
	if (inputs.fireBullet) {
		if (shootingCooldown <= 0) {
			float offset = CANON_OFFSET;
			sf::Vector2f shootPos = sf::Vector2f(getPosition().x + offset, getPosition().y);
			Publisher::notifySubscribers(Event::PLAYER_SHOOT, &shootPos);
			shootPos = sf::Vector2f(getPosition().x - offset, getPosition().y);
			Publisher::notifySubscribers(Event::PLAYER_SHOOT, &shootPos);
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
	if (getPosition().y + halfHeight > Game::GAME_HEIGHT - Hud::HUD_HEIGHT) setPosition(getPosition().x, Game::GAME_HEIGHT - Hud::HUD_HEIGHT - halfHeight);

	if (hurtTime > 0) {
		if (std::fmod(hurtTime, 0.16f) > 0.08f) setColor(sf::Color(255, 50, 50, 255));
		else setColor(sf::Color::White);
	}

	AnimatedGameObject::update(deltaT, inputs);

	if (!this->isAlive())
		return false;
	return true;
}

void Player::notify(Event event, const void* data) 
{
	if (event == Event::PLAYER_HIT) 
	{
		if (hurtTime == 0) 
		{
			health -= *(int*)data;
			hurtTime = HURT_TIME;
		}
	}
	else if (event == Event::ENEMY_KILLED)
	{
		score += SCORE_INCREASE_KILL;
	}
}

bool Player::isAlive()
{
	return getHealth() > 0;
}

unsigned int Player::getScore()
{
	return score;
}
