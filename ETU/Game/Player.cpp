#include "stdafx.h"
#include "Player.h"
#include "Inputs.h"
#include "Publisher.h"
#include "Game.h"
#include "Hud.h"

const int Player::SHIP_SPEED = 360;
const float Player::SHOOTING_COOLDOWN = 0.2f;
const int Player::SHOOTING_VOLUME = 20;
const int Player::CANON_OFFSET = 14;
const int Player::BONUS_CANON_OFFSET = 32;
const int Player::INITIAL_HEALTH = 100;
const float Player::HURT_TIME = 0.4f;
const unsigned int Player::SCORE_INCREASE_KILL = 1000;
const unsigned int Player::BONUS_TIME = 5;

Player::Player()
	: Character(INITIAL_HEALTH)
{
	shootingCooldown = SHOOTING_COOLDOWN;
	hurtTime = 0;
	score = 0;
	bonusTime = 0;
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
	shootSound.setBuffer(this->contentManager.getPlayerGunSoundBuffer());
	shootSound.setVolume(SHOOTING_VOLUME);
	this->initialize(contentManager.getMainCharacterTexture(), sf::Vector2f((float)Game::GAME_WIDTH/2,(float)Game::GAME_HEIGHT - 100));
	return true;
}

bool Player::uninit()
{
	Publisher::removeSubscriber(*this, Event::ENEMY_KILLED);
	return true;
}

bool Player::update(const float deltaT, const Inputs& inputs)
{
	hurtTime = (float)std::fmax(0, hurtTime - deltaT);
	bonusTime = (float)std::fmax(0, bonusTime - deltaT);
	shootingCooldown -= deltaT;
	if (inputs.fireBullet) {
		if (shootingCooldown <= 0) {
			sf::Vector2f shootPos = sf::Vector2f(getPosition().x + CANON_OFFSET, getPosition().y);
			Publisher::notifySubscribers(Event::PLAYER_SHOOT, &shootPos);
			shootPos = sf::Vector2f(getPosition().x - CANON_OFFSET, getPosition().y);
			Publisher::notifySubscribers(Event::PLAYER_SHOOT, &shootPos);
			if (hasBonus())
			{
				shootPos = sf::Vector2f(getPosition().x + BONUS_CANON_OFFSET, getPosition().y);
				Publisher::notifySubscribers(Event::PLAYER_SHOOT, &shootPos);
				shootPos = sf::Vector2f(getPosition().x - BONUS_CANON_OFFSET, getPosition().y);
				Publisher::notifySubscribers(Event::PLAYER_SHOOT, &shootPos);
			}
			shootSound.play();
			shootingCooldown = SHOOTING_COOLDOWN;
		}
	}

	if (inputs.moveFactorX != 0 || inputs.moveFactorY != 0) {
		sf::Vector2f direction = sf::Vector2f(inputs.moveFactorX, inputs.moveFactorY);
		if (direction.x > 1) direction.x = 1;
		else if (direction.x < -1) direction.x = -1;
		if (direction.y > 1) direction.y = 1;
		else if (direction.y < -1) direction.y = -1;


		float angle = atan2f(direction.y, direction.x);
		
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

void Player::hit(const int damage)
{
	if (hasBonus())
		bonusTime = 0;
	else if (hurtTime == 0)
	{
		health -= damage;
		hurtTime = HURT_TIME;
	}
}

void Player::heal(const int health)
{
	this->health += health;
}

void Player::notify(const Event event, const void* data)
{
	if (event == Event::ENEMY_KILLED)
	{
		score += SCORE_INCREASE_KILL;
	}
}

void Player::activateBonus()
{
	bonusTime = BONUS_TIME;
}

bool Player::isAlive() const
{
	return getHealth() > 0;
}

bool Player::hasBonus() const
{
	if (bonusTime > 0)
		return true;
	return false;
}

unsigned int Player::getScore() const
{
	return score;
}

unsigned int Player::getBonusTime() const
{
	return (int)bonusTime;
}
