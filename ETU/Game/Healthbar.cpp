#include "stdafx.h"
#include "Healthbar.h"
#include "Game.h"

const int Healthbar::HEALTH_BAR_LENGTH = 150;
const int Healthbar::HEALTH_BAR_HEIGHT = 25;

bool Healthbar::init(const int maxHp, Character* character)
{
	this->maxHp = maxHp;
	hpBar.setSize(sf::Vector2f((float)HEALTH_BAR_LENGTH, (float)HEALTH_BAR_HEIGHT));
	hpBar.setFillColor(sf::Color::Red);
	hpBar.setPosition(0,0);
	hpBar.setOrigin(hpBar.getLocalBounds().width * 0.5f, hpBar.getLocalBounds().height * 0.5f);

	hpBarBack = hpBar;
	hpBarBack.setOutlineThickness(4);
	hpBarBack.setOutlineColor(sf::Color::White);
	hpBarBack.setFillColor(sf::Color(25, 25, 25, 230));

	this->character = character;

	return true;
}

void Healthbar::update()
{
	float hpPercent = character->getHealth() / maxHp;
	hpBar.setSize(sf::Vector2f(hpBarBack.getSize().x * hpPercent, hpBar.getSize().y));
	hpBar.setPosition(sf::Vector2f(character->getPosition().x, character->getPosition().y - (character->getLocalBounds().height / 2 + HEALTH_BAR_HEIGHT)));
	hpBarBack.setPosition(sf::Vector2f(character->getPosition().x, character->getPosition().y - (character->getLocalBounds().height / 2 + HEALTH_BAR_HEIGHT)));
}

void Healthbar::draw(sf::RenderWindow& window) const
{
	window.draw(hpBarBack);
	window.draw(hpBar);
}
