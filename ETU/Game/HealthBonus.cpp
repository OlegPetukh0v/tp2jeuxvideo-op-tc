#include "stdafx.h"
#include "HealthBonus.h"
#include "Game.h"

const int HealthBonus::SPEED = 120;

bool HealthBonus::update(float elapsedTime)
{
    move(0, SPEED * elapsedTime);
    if (getPosition().y - getGlobalBounds().height / 2 > Game::GAME_HEIGHT) deactivate();
    return false;
}

void HealthBonus::activate()
{
    float x = rand() % (int)(Game::GAME_WIDTH - getGlobalBounds().width);
    setPosition(x + getGlobalBounds().width / 2, -getGlobalBounds().height);
    setPosition(300, 10);
    GameObject::activate();
}

void HealthBonus::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
    setTexture(contentManager.getMiscTexture());
    setTextureRect(sf::IntRect(289, 84, 16, 16));
    setOrigin(sf::Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
    setScale(2, 2);
    setPosition(initialPosition);
}

void HealthBonus::init(const GameContentManager& contentManger)
{
    this->contentManager = contentManager;
    this->initialize(this->contentManager.getMiscTexture(), sf::Vector2f(0, 0));
}
