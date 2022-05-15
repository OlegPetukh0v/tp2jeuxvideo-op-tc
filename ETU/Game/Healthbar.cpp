#include "stdafx.h"
#include "Healthbar.h"
#include "Game.h"

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
	hpBarBack.setOutlineThickness(4);
	hpBarBack.setOutlineColor(sf::Color::White);
	hpBarBack.setFillColor(sf::Color(25, 25, 25, 230));

	return true;
}

void Healthbar::update(const float hp, sf::Vector2f characterPosition, float characterSize)
{
	float hpPercent = hp / maxHp;
	hpBar.setSize(sf::Vector2f(hpBarBack.getSize().x * hpPercent, hpBar.getSize().y));
	hpBar.setPosition(sf::Vector2f(characterPosition.x, characterPosition.y - (characterSize / 2 + HEALTH_BAR_HEIGHT)));
	hpBarBack.setPosition(sf::Vector2f(characterPosition.x, characterPosition.y - (characterSize / 2 + HEALTH_BAR_HEIGHT)));
	std::cout << "hpBarBack: " << hpBarBack.getPosition().x << ", " << hpBarBack.getPosition().y << std::endl;
}

void Healthbar::draw(sf::RenderWindow& window) const
{
	window.draw(hpBarBack);
	window.draw(hpBar);
}
