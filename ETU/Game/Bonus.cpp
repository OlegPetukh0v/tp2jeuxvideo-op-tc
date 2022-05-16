#include "stdafx.h"
#include "Bonus.h"
#include "Game.h"
#include "GameContentManager.h"
#include "Player.h"

const int Bonus::PICKUP_VOLUME = 50;
const int Bonus::SPEED = 120;
const int Bonus::SCALE = 2;

bool Bonus::update(float elapsedTime)
{
    move(0, SPEED * elapsedTime);
    if (getPosition().y - getGlobalBounds().height / 2 > Game::GAME_HEIGHT) deactivate();
    return false;
}

void Bonus::initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition)
{
    setScale(Bonus::SCALE, Bonus::SCALE);
    setPosition(initialPosition);
}

void Bonus::onPick(Player& player)
{
    pickupSound.play();
    GameObject::deactivate();
}
