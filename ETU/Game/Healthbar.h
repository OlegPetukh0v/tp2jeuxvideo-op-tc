#pragma once
#include "GameObject.h"
#include "Character.h"

class Healthbar :
	public GameObject
{
public:
	static const int HEALTH_BAR_LENGTH;
	static const int HEALTH_BAR_HEIGHT;

	virtual bool init(const int maxHp, Character* character);
	virtual void draw(sf::RenderWindow& window) const;
	void update();

private:
	int maxHp;
	Character* character = nullptr;

	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarBack;
};
