#include "stdafx.h"
#include "Boss.h"
// TODO: delete after tests finished
#include "Game.h"

const int Boss::BOSS_SPEED = 120;
const int Boss::INITIAL_HEALTH = 1000;

bool Boss::init(const GameContentManager& contentManager)
{
	this->contentManager = contentManager;

	setOrigin(sf::Vector2f(getLocalBounds().width * 0.5, getLocalBounds().height * 0.5));
	setPosition(Game::GAME_WIDTH, Game::GAME_HEIGHT);

	health = INITIAL_HEALTH;
	healthBar.init(INITIAL_HEALTH);
	healthBar.setPosition(sf::Vector2f(getPosition().x + healthBar.getGlobalBounds().width, getPosition().y + healthBar.getGlobalBounds().height));
	return true;
}

void Boss::draw(sf::RenderWindow& window) const
{
	Character::draw(window);
	healthBar.draw(window);
}
