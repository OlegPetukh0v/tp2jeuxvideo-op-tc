#pragma once
#include "GameObject.h"

class Healthbar :
	public GameObject
{
public:
	static const int HEALTH_BAR_LENGTH;
	static const int HEALTH_BAR_HEIGHT;

	virtual bool init(int maxHp);
	virtual void draw(sf::RenderWindow& window) const;

private:
	int hp;
	int maxHp;

	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarBack;
};
