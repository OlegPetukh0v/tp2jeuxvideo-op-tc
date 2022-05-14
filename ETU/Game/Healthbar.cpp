#include "stdafx.h"
#include "Healthbar.h"
#include "Game.h"

static const int HEALTH_BAR_LENGTH = 150;
static const int HEALTH_BAR_HEIGHT = 25;

bool Healthbar::init(int maxHp)
{
	this->maxHp = maxHp;
	hp = maxHp;
	hpBar.setSize(sf::Vector2f(HEALTH_BAR_LENGTH, HEALTH_BAR_HEIGHT));
	hpBar.setFillColor(sf::Color::Red);
	hpBar.setPosition(0,0);
	hpBar.setOrigin(hpBar.getLocalBounds().width * 0.5, hpBar.getLocalBounds().height * 0.5);

	hpBarBack = hpBar;
	hpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

	return true;
}

void Healthbar::draw(sf::RenderWindow& window) const
{
	window.draw(hpBarBack);
	window.draw(hpBar);
}
