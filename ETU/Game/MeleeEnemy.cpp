#include "stdafx.h"
#include "MeleeEnemy.h"
#include "Publisher.h"
#include "Game.h"
#include "MonsterIdleAnimation.h"
#include <iostream>

const int MeleeEnemy::MONSTER_SPEED = 120;
const int MeleeEnemy::DEATH_VOLUME = 70;
const int MeleeEnemy::INITIAL_HEALTH = 150;
const float MeleeEnemy::HURT_TIME = 0.32f;
const float MeleeEnemy::HURT_FLASH_TIME = HURT_TIME / 2;

MeleeEnemy::MeleeEnemy()
	: Character(INITIAL_HEALTH)
{
	goingLeft = true;
}

void MeleeEnemy::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
	setTexture(texture);
	AnimatedGameObject::init(contentManager);
	currentState = State::MELEE_ENEMY;
	addAnimation<State::MELEE_ENEMY, MonsterIdleAnimation>(contentManager);
	setOrigin(sf::Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
	setPosition(initialPosition);
}

bool MeleeEnemy::init(const GameContentManager& contentManager)
{
	this->contentManager = contentManager;
	initialize(contentManager.getMainCharacterTexture(), sf::Vector2f(0, 0));
	deathSound.setBuffer(contentManager.getEnemyKilledSoundBuffer());
	deathSound.setVolume(DEATH_VOLUME);
	return true;
}

bool MeleeEnemy::uninit()
{
	return true;
}

void MeleeEnemy::activate()
{
	health = INITIAL_HEALTH;
	hurtTime = 0;
	setColor(sf::Color::White);
	int x = rand() % (int)(Game::GAME_WIDTH - getLocalBounds().width);
	setPosition((float)x + getLocalBounds().width / 2, -getLocalBounds().height);
	GameObject::activate();
}

void MeleeEnemy::charge()
{
}

bool MeleeEnemy::update(const float deltaT)
{
	hurtTime = (float)std::fmax(0, hurtTime - deltaT);

	int horizontalMovement = MONSTER_SPEED;
	if (goingLeft) horizontalMovement *= -1;

	this->move(sf::Vector2f(horizontalMovement * deltaT, MONSTER_SPEED * deltaT));

	float halfHeight = getGlobalBounds().height / 2;
	float halfWidth = getGlobalBounds().width / 2;
	if (getPosition().y - halfHeight > Game::GAME_HEIGHT) setPosition(getPosition().x, -halfHeight);

	if (getPosition().x - halfWidth < 0) {
		goingLeft = false;
	}
	if (getPosition().x + halfWidth > Game::GAME_WIDTH) {
		goingLeft = true;
	}

	if (hurtTime > 0) {
		if (std::fmod(hurtTime, HURT_FLASH_TIME) > HURT_FLASH_TIME / 2) { // When hurt, it makes the enemy flash white/orange every FlashTime.
			setColor(sf::Color(255, 120, 70, 120)); // Orange-transparent
		}
		else setColor(sf::Color::White);
	}

	Inputs inputs;
	AnimatedGameObject::update(deltaT, inputs);
	return false;
}

void MeleeEnemy::hit(const int damage)
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
