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

}

bool Boss::init(const GameContentManager& contentManager)
{
	this->contentManager = contentManager;
	AnimatedGameObject::init(contentManager);
	currentState = State::BOSS;
	addAnimation<State::BOSS, BossAnimation>(contentManager);

	setOrigin(sf::Vector2f(getLocalBounds().width * 0.5, getLocalBounds().height * 0.5));
	setPosition(0, 0);

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
	hurtTime = std::fmax(0, hurtTime - deltaT);
	shootingCooldown += deltaT;
	if (shootingCooldown >= BossAnimation::ANIMATION_LENGTH) {
		shoot();
	}

	this->move(sf::Vector2f(BOSS_SPEED * deltaT, 0));

	float halfWidth = getGlobalBounds().width / 2;
	if (getPosition().x - halfWidth > Game::GAME_WIDTH) setPosition(Game::GAME_WIDTH - halfWidth, getPosition().y);
	if (getPosition().x - halfWidth < 0) setPosition(halfWidth, getPosition().y);

	if (hurtTime > 0) {
		if (std::fmod(hurtTime, 0.16f) > 0.08f) setColor(sf::Color(255, 155, 80, 120));
		else setColor(sf::Color::White);
	}

	Inputs inputs;
	AnimatedGameObject::update(deltaT, inputs);
	healthBar.update(health);
	return false;
}

void Boss::draw(sf::RenderWindow& window) const
{
	Character::draw(window);
	healthBar.draw(window);
}

void Boss::shoot()
{
	// TODO
}
