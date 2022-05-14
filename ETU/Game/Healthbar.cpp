#include "stdafx.h"
#include "Healthbar.h"
#include "Game.h"

//static const int HEALTH_BAR_LENGTH = 150;
//static const int HEALTH_BAR_HEIGHT = 25;

bool Healthbar::init(const int maxHp)
{
	this->maxHp = maxHp;
	hpBar.setSize(sf::Vector2f((float)150, (float)25));
	hpBar.setFillColor(sf::Color::Red);
	hpBar.setPosition(0,0);
	hpBar.setOrigin(hpBar.getLocalBounds().width * 0.5f, hpBar.getLocalBounds().height * 0.5f);

	hpBarBack = hpBar;
	hpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

	return true;
}

void Healthbar::update(const int hp)
{
	float hpPercent = hp / maxHp;
	hpBar.setSize(sf::Vector2f(hpBarBack.getSize().x * hpPercent, hpBar.getSize().y));
}

void Healthbar::draw(sf::RenderWindow& window) const
{
	window.draw(hpBarBack);
	window.draw(hpBar);
}
