#include "stdafx.h"
#include "Enemy.h"
#include "Publisher.h"
#include "Game.h"
#include "EnemyShipAnimation.h"

const int Enemy::SHIP_SPEED = 120;
const int Enemy::SHIP_WIDTH = 73;
const int Enemy::DEATH_VOLUME = 70;
const int Enemy::SHOOT_VOLUME = 20;
const float Enemy::SHOOT_PERCENTAGE_ANIMATION = 0.94f;
const int Enemy::INITIAL_HEALTH = 50;
const int Enemy::CANON_OFFSET = 8;
const float Enemy::HURT_TIME = 0.32f;
const float Enemy::HURT_FLASH_TIME = HURT_TIME / 2;

Enemy::Enemy()
	: Character(INITIAL_HEALTH)
{
}

void Enemy::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
	setTexture(texture);
	AnimatedGameObject::init(contentManager);
	currentState = State::STANDARD_ENEMY;
	addAnimation<State::STANDARD_ENEMY, EnemyShipAnimation>(contentManager);
	setOrigin(sf::Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
	setPosition(initialPosition);
}

bool Enemy::init(const GameContentManager& contentManager)
{
	this->contentManager = contentManager;
    initialize(contentManager.getMainCharacterTexture(), sf::Vector2f(0, 0));
	deathSound.setBuffer(contentManager.getEnemyKilledSoundBuffer());
	deathSound.setVolume(DEATH_VOLUME);
	shootSound.setBuffer(contentManager.getEnemyGunSoundBuffer());
	shootSound.setVolume(SHOOT_VOLUME);
    return true;
}

bool Enemy::uninit()
{
	return true;
}

void Enemy::activate()
{
	health = INITIAL_HEALTH;
	hurtTime = 0;
	setColor(sf::Color::White);
	int x = rand() % (Game::GAME_WIDTH - Enemy::SHIP_WIDTH);
	setPosition(x + Enemy::SHIP_WIDTH / 2, -getLocalBounds().height);
	GameObject::activate();
}

void Enemy::shoot()
{
	sf::Vector2f offsetPos = sf::Vector2f(getPosition().x + CANON_OFFSET, getPosition().y);
	Publisher::notifySubscribers(Event::ENEMY_SHOOT, &offsetPos);
	offsetPos = sf::Vector2f(getPosition().x - CANON_OFFSET, getPosition().y);
	Publisher::notifySubscribers(Event::ENEMY_SHOOT, &offsetPos);
	shootSound.play();
}

bool Enemy::update(float deltaT)
{
	hurtTime = (float)std::fmax(0, hurtTime - deltaT);
	if (SHOOT_PERCENTAGE_ANIMATION < AnimatedGameObject::animations[AnimatedGameObject::currentState]->getPercentage()) {
		shoot();
	}

	this->move(sf::Vector2f(0, SHIP_SPEED * deltaT));

	float halfHeight = getGlobalBounds().height / 2;
	if (getPosition().y - halfHeight > Game::GAME_HEIGHT) setPosition(getPosition().x, -halfHeight);

	if (hurtTime > 0) {
		if (std::fmod(hurtTime, HURT_FLASH_TIME) > HURT_FLASH_TIME/2) { // When hurt, it makes the enemy flash white/orange every FlashTime.
			setColor(sf::Color(255, 120, 70, 120)); // Orange-transparent
		}
		else setColor(sf::Color::White);  
	}
	
	Inputs inputs;
	AnimatedGameObject::update(deltaT, inputs);
	return false;
}

void Enemy::hit(int damage)
{
	health -= damage;
	if (health <= 0) {
		deathSound.play();
		Publisher::notifySubscribers(Event::ENEMY_KILLED, this);
		deactivate();
	}
	else {
		hurtTime = HURT_TIME;
	}
}
