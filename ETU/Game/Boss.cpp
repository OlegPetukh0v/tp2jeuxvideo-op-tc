#include "stdafx.h"
#include "Boss.h"
#include "BossAnimation.h"
#include "Game.h"
#include "Publisher.h"

const int Boss::BOSS_SPEED_HORIZONTAL = 200;
const int Boss::BOSS_SPEED_VERTICAL = 150;
const int Boss::INITIAL_HEALTH = 700;
const int Boss::SPAWNING_TIME = 2;
const float Boss::SPAWN_TIME = 2.0f;
const float Boss::SHOOTING_COOLDOWN = 0.7f;
const sf::Vector2f Boss::INTIAL_POSITION = sf::Vector2f((float)Game::GAME_WIDTH / 2, -130);
const float Boss::HURT_TIME = 0.32f;
const float Boss::HURT_FLASH_TIME = HURT_TIME / 2;

Boss::Boss()
	: Character(INITIAL_HEALTH)
{
	shootingCooldown = 0;
	shotsFired = 0;
	spawnCooldown = 0;
}

void Boss::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
	setTexture(this->contentManager.getEnemiesTexture());
	AnimatedGameObject::init(this->contentManager);
	currentState = State::BOSS;
	addAnimation<State::BOSS, BossAnimation>(this->contentManager);
	setOrigin(sf::Vector2f((float)(getLocalBounds().width * 0.5), (float)(getLocalBounds().height * 0.5)));
	setPosition(initialPosition);
}

bool Boss::init(const GameContentManager& contentManager)
{
	this->contentManager = contentManager;
	initialize(this->contentManager.getEnemiesTexture(), INTIAL_POSITION);
	health = INITIAL_HEALTH;
	healthBar.init(INITIAL_HEALTH, this);
	healthBar.update();
	return true;
}

bool Boss::uninit()
{
	return true;
}

bool Boss::update(float deltaT)
{
	if (isActive()) {
		if (SPAWNING_TIME > spawnCooldown)
		{
			updateSpawnTransition(deltaT);
		}
		else
		{
			hurtTime = (float)std::fmax(0, hurtTime - deltaT);

			if (SHOOTING_COOLDOWN < AnimatedGameObject::animations[AnimatedGameObject::currentState]->getPercentage()) {
				shoot();
			}

			int direction = 1;
			if (targetPos.x > getPosition().x)
			{
				if ((targetPos.x - (BOSS_SPEED_HORIZONTAL * deltaT)) > getPosition().x) this->move(sf::Vector2f(BOSS_SPEED_HORIZONTAL * deltaT, 0));
				else this->setPosition(sf::Vector2f(targetPos.x, getPosition().y));
			}
			else if (targetPos.x < getPosition().x)
			{
				if ((targetPos.x + (BOSS_SPEED_HORIZONTAL * deltaT)) < getPosition().x) this->move(sf::Vector2f(BOSS_SPEED_HORIZONTAL * deltaT * -1, 0));
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
				if (std::fmod(hurtTime, HURT_FLASH_TIME) > HURT_FLASH_TIME/2) setColor(sf::Color(255, 140, 70, 120));
				else setColor(sf::Color::White);
			}

			healthBar.update();
		}
		Inputs inputs;
		AnimatedGameObject::update(deltaT, inputs);
	}
	return false;
}

bool Boss::update(float deltaT, sf::Vector2f targetPos)
{
	this->targetPos = targetPos;
	this->update(deltaT);
	return false;
}

void Boss::updateSpawnTransition(float deltaT)
{
	spawnCooldown += deltaT;
	if (spawnCooldown <= SPAWNING_TIME)
	{
		move(0, BOSS_SPEED_VERTICAL * deltaT);
		setColor(sf::Color(255, 255, 255, 255*(spawnCooldown / SPAWNING_TIME)));
	}
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
