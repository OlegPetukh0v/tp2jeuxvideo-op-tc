#include "stdafx.h"
#include "Enemy.h"
#include "Publisher.h"
#include "Game.h"
#include "EnemyShipAnimation.h"

const int Enemy::SHIP_SPEED = 120;
const int Enemy::SHIP_WIDTH = 73;
const int Enemy::DEATH_VOLUME = 70;
const int Enemy::INITIAL_HEALTH = 50;
const int Enemy::CANON_OFFSET = 8;
const float Enemy::HURT_TIME = 0.32f;

Enemy::Enemy()
	: Character(INITIAL_HEALTH)
{
	shootingCooldown = EnemyShipAnimation::ANIMATION_LENGTH / 2;
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
	this->deathSound.setBuffer(contentManager.getEnemyKilledSoundBuffer());
	this->deathSound.setVolume(DEATH_VOLUME);
    return true;
}

void Enemy::activate()
{
	health = INITIAL_HEALTH;
	hurtTime = 0;
	setColor(sf::Color::White);
	float x = rand() % (Game::GAME_WIDTH - Enemy::SHIP_WIDTH);
	setPosition(x + Enemy::SHIP_WIDTH / 2, -getLocalBounds().height);
	GameObject::activate();
}

void Enemy::shoot()
{
	sf::Vector2f offsetPos = sf::Vector2f(getPosition().x + CANON_OFFSET, getPosition().y);
	Publisher::notifySubscribers(Event::ENEMY_SHOOT, &offsetPos);
	offsetPos = sf::Vector2f(getPosition().x - CANON_OFFSET, getPosition().y);
	Publisher::notifySubscribers(Event::ENEMY_SHOOT, &offsetPos);
	shootingCooldown = 0;
}

bool Enemy::update(float deltaT)
{
	hurtTime = std::fmax(0, hurtTime - deltaT);
	shootingCooldown += deltaT;
	if (0.98f < AnimatedGameObject::animations[AnimatedGameObject::currentState]->getTimeInCurrentState()) {
		shoot();
	}

	this->move(sf::Vector2f(0, SHIP_SPEED * deltaT));

	float halfHeight = getGlobalBounds().height / 2;
	if (getPosition().y - halfHeight > Game::GAME_HEIGHT) setPosition(getPosition().x, -halfHeight);

	if (hurtTime > 0) {
		if (std::fmod(hurtTime, 0.16f) > 0.08f) setColor(sf::Color(255, 155, 80, 120));
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
		this->deathSound.play();
		deactivate();
	}
	else {
		hurtTime = HURT_TIME;
	}
}
