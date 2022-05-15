#include "stdafx.h"
#include "Healthbar.h"
#include "Game.h"
#include <iostream>

const int Healthbar::HEALTH_BAR_LENGTH = 150;
const int Healthbar::HEALTH_BAR_HEIGHT = 25;

bool Healthbar::init(const int maxHp)
{
	this->maxHp = maxHp;
	hpBar.setSize(sf::Vector2f((float)HEALTH_BAR_LENGTH, (float)HEALTH_BAR_HEIGHT));
	hpBar.setFillColor(sf::Color::Red);
	hpBar.setPosition(0,0);
	hpBar.setOrigin(hpBar.getLocalBounds().width * 0.5f, hpBar.getLocalBounds().height * 0.5f);

	hpBarBack = hpBar;
	hpBarBack.setFillColor(sf::Color::Transparent);

	return true;
}

void Healthbar::update(const float hp, sf::Vector2f characterPosition, float characterSize)
{
	float hpPercent = hp / maxHp;
	std::cout << "hpPercent: " << hpPercent << std::endl;
	hpBar.setSize(sf::Vector2f(hpBarBack.getSize().x * hpPercent, hpBar.getSize().y));
	hpBar.setPosition(sf::Vector2f(characterPosition.x, characterPosition.y - (characterSize / 2 + HEALTH_BAR_HEIGHT)));
	hpBarBack.setPosition(sf::Vector2f(characterPosition.x, characterPosition.y - (characterSize / 2 + HEALTH_BAR_HEIGHT)));
}

void Healthbar::draw(sf::RenderWindow& window) const
{
	window.draw(hpBarBack);
	window.draw(hpBar);
}
