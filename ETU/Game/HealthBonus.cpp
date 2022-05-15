#include "stdafx.h"
#include "HealthBonus.h"
#include "Game.h"

const int HealthBonus::HEALTH = 100;
const int HealthBonus::PICKUP_VOLUME = 50;
const int HealthBonus::SPEED = 120;

bool HealthBonus::update(float elapsedTime)
{
    move(0, SPEED * elapsedTime);
    if (getPosition().y - getGlobalBounds().height / 2 > Game::GAME_HEIGHT) deactivate();
    return false;
}

void HealthBonus::deactivate()
{
    pickupSound.play();
    GameObject::deactivate();
}

void HealthBonus::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
    setTexture(texture);
    //setTextureRect(sf::IntRect(270, 83, 16, 16)); // For Gun bonus
    setTextureRect(sf::IntRect(229, 64, 11, 10));
    setOrigin(sf::Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
    setScale(2, 2); // TO CONST
    setPosition(initialPosition);
}

void HealthBonus::init(const GameContentManager& gameContentManager)
{
    this->contentManager = gameContentManager;
    this->initialize(this->contentManager.getMiscTexture(), sf::Vector2f(100, 0));
    pickupSound.setBuffer(this->contentManager.getHealthSoundBuffer());
}
