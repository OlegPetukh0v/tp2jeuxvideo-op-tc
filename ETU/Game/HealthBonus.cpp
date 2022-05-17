#include "stdafx.h"
#include "HealthBonus.h"
#include "Game.h"
#include "GameContentManager.h"
#include "Player.h"

const int HealthBonus::HEALTH = 100;

void HealthBonus::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
    setTexture(texture);
    setTextureRect(sf::IntRect(229, 64, 11, 10));
    setOrigin(sf::Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
    Bonus::initialize(texture, initialPosition);
}

void HealthBonus::init(const GameContentManager& gameContentManager)
{
    initialize(gameContentManager.getMiscTexture(), sf::Vector2f(100, 0));
    pickupSound.setBuffer(gameContentManager.getHealthSoundBuffer());
}

void HealthBonus::onPick(Player& player)
{
    player.heal(HEALTH);
    Bonus::onPick();
}
