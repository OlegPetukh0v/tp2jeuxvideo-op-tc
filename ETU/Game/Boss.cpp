#include "stdafx.h"
#include "Boss.h"
#include "BossAnimation.h"
#include "Game.h"
#include "Publisher.h"
#include <iostream>

const int Boss::BOSS_SPEED = 200;
const int Boss::INITIAL_HEALTH = 700;
const int Boss::SPAWNING_TIME = 2;
const float Boss::HURT_TIME = 0.5f;
const float Boss::SPAWN_TIME = 2.0f;
const sf::Vector2f Boss::INTIAL_POSITION = sf::Vector2f(0, 135);

Boss::Boss()
	: Character(INITIAL_HEALTH)
{
	shootingCooldown = 0;
	shotsFired = 0;
}

void Boss::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
	setTexture(this->contentManager.getEnemiesTexture());
	AnimatedGameObject::init(this->contentManager);
	currentState = State::BOSS;
	addAnimation<State::BOSS, BossAnimation>(this->contentManager);
	setOrigin(sf::Vector2f(getLocalBounds().width * 0.5, getLocalBounds().height * 0.5));
	setPosition(initialPosition);
}

bool Boss::init(const GameContentManager& contentManager)
{
	this->contentManager = contentManager;
	initialize(this->contentManager.getEnemiesTexture(), INTIAL_POSITION);
	health = INITIAL_HEALTH;
	healthBar.init(INITIAL_HEALTH);
	healthBar.setPosition(sf::Vector2f(getPosition().x + healthBar.getGlobalBounds().width, getPosition().y + healthBar.getGlobalBounds().height));

	return true;
}

bool Boss::uninit()
{
	return true;
}

bool Boss::update(float deltaT)
{
	if (isActive()) {
		hurtTime = (float)std::fmax(0, hurtTime - deltaT);

		if (1.2f < AnimatedGameObject::animations[AnimatedGameObject::currentState]->getTimeInCurrentState()) {
			shoot();
		}

		int direction = 1;
		if (targetPos.x > getPosition().x)
		{
			if ((targetPos.x - (BOSS_SPEED * deltaT)) > getPosition().x) this->move(sf::Vector2f(BOSS_SPEED * deltaT, 0));
			else this->setPosition(sf::Vector2f(targetPos.x, getPosition().y));
		}
		else if (targetPos.x < getPosition().x)
		{
			if ((targetPos.x + (BOSS_SPEED * deltaT)) < getPosition().x) this->move(sf::Vector2f(BOSS_SPEED * deltaT * -1, 0));
			else this->setPosition(sf::Vector2f(targetPos.x, getPosition().y));
		}

		float halfWidth = getGlobalBounds().width / 2;
		if (getPosition().x + halfWidth > Game::GAME_WIDTH) {
			setPosition(Game::GAME_WIDTH - halfWidth, getPosition().y);
		}
		else if (getPosition().x - halfWidth < 0) {
			setPosition(halfWidth, getPosition().y);
		}

		if (hurtTime > 0) {
			if (std::fmod(hurtTime, 0.16f) > 0.08f) setColor(sf::Color(255, 155, 80, 120));
			else setColor(sf::Color::White);
		}

		Inputs inputs;
		AnimatedGameObject::update(deltaT, inputs);
		healthBar.update(getHealth(), getPosition(), getLocalBounds().height);
	}
	return false;
}

bool Boss::update(float deltaT, sf::Vector2f targetPos)
{
	this->targetPos = targetPos;
	this->update(deltaT);
	return false;
}

void Boss::draw(sf::RenderWindow& window) const
{
	if (isActive()) {
		window.draw(*this);
		healthBar.draw(window);
	}
}

void Boss::shoot()
{
	Publisher::notifySubscribers(Event::ENEMY_SHOOT, &getPosition());
}

void Boss::hit(int damage)
{
	health -= damage;
	if (health <= 0) {
		deactivate();
		Publisher::notifySubscribers(Event::BOSS_KILLED, this);
	}
	else {
		hurtTime = HURT_TIME;
	}
}
