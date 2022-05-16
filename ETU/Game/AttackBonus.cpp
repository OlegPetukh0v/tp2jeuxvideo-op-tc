#include "stdafx.h"
#include "AttackBonus.h"
#include "Game.h"
#include "GameContentManager.h"
#include "Player.h"

void AttackBonus::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
    setTexture(texture);
    setTextureRect(sf::IntRect(204, 103, 18, 18));
    setOrigin(sf::Vector2f(getGlobalBounds().width / 2, getGlobalBounds().height / 2));
    Bonus::initialize(texture, initialPosition);
}

void AttackBonus::init(const GameContentManager& gameContentManager)
{
    initialize(gameContentManager.getMiscTexture(), sf::Vector2f(100, 0));
    pickupSound.setBuffer(gameContentManager.getGunBonusSoundBuffer());
}

void AttackBonus::onPick(Player& player)
{
    player.activateBonus();
    Bonus::onPick(player);
}
