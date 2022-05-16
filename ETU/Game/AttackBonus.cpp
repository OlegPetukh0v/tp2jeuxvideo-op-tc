#include "stdafx.h"
#include "AttackBonus.h"
#include "Game.h"
#include "GameContentManager.h"

const int AttackBonus::PICKUP_VOLUME = 50;
const int AttackBonus::SPEED = 120;
const int AttackBonus::SCALE = 2;

bool AttackBonus::update(float elapsedTime)
{
    move(0, SPEED * elapsedTime);
    if (getPosition().y - getGlobalBounds().height / 2 > Game::GAME_HEIGHT) deactivate();
    return false;
}

void AttackBonus::deactivate()
{
    pickupSound.play();
    GameObject::deactivate();
}

void AttackBonus::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
    setTexture(texture);
    setTextureRect(sf::IntRect(204, 103, 18, 18));
    setOrigin(sf::Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
    setScale(SCALE, SCALE);
    setPosition(initialPosition);
}

void AttackBonus::init(const GameContentManager& gameContentManager)
{
    this->initialize(gameContentManager.getMiscTexture(), sf::Vector2f(100, 0));
    pickupSound.setBuffer(gameContentManager.getGunBonusSoundBuffer());
}
