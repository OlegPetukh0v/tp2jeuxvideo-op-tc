#include "stdafx.h"
#include "Boss.h"
#include "BossAnimation.h"
#include "Game.h"
#include "Publisher.h"
const int Boss::BOSS_SPEED = 120;
const int Boss::INITIAL_HEALTH = 500;
const int Boss::SPAWNING_TIME = 2;

Boss::Boss()
	: Character(INITIAL_HEALTH)
{
	isMovingLeft = false;
	shootingCooldown = 0;
	shotsFired = 0;
}

void Boss::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
	setTexture(this->contentManager.getEnemiesTexture());
	setTextureRect(sf::IntRect(31, 1905, 86, 125));
	AnimatedGameObject::init(this->contentManager);
	currentState = State::BOSS;
	addAnimation<State::BOSS, BossAnimation>(this->contentManager);
	setOrigin(sf::Vector2f(getLocalBounds().width * 0.5, getLocalBounds().height * 0.5));
	setPosition(initialPosition);
}

bool Boss::init(const GameContentManager& contentManager)
{
	this->contentManager = contentManager;
	initialize(this->contentManager.getEnemiesTexture(), sf::Vector2f(0, 50));
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
		shootingCooldown += deltaT;
		if (shootingCooldown >= BossAnimation::ANIMATION_LENGTH) {
			shoot();
		}

		int direction = 1;
		if (isMovingLeft) direction = -1;
		this->move(sf::Vector2f(BOSS_SPEED * direction * deltaT, 0));

		float halfWidth = getGlobalBounds().width / 2;
		if (getPosition().x + halfWidth > Game::GAME_WIDTH) {
			setPosition(Game::GAME_WIDTH - halfWidth, getPosition().y);
			isMovingLeft = true;
		}
		if (getPosition().x - halfWidth < 0) {
			setPosition(halfWidth, getPosition().y);
			isMovingLeft = false;
		}

		if (hurtTime > 0) {
			if (std::fmod(hurtTime, 0.16f) > 0.08f) setColor(sf::Color(255, 155, 80, 120));
			else setColor(sf::Color::White);
		}

		Inputs inputs;
		AnimatedGameObject::update(deltaT, inputs);
		healthBar.update(health);
	}
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
	// TODO
}
