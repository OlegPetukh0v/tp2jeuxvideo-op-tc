#pragma once
#include "GameObject.h"

class Healthbar :
	public GameObject
{
public:
	static const int HEALTH_BAR_LENGTH;
	static const int HEALTH_BAR_HEIGHT;

	virtual bool init(const int maxHp);
	virtual void draw(sf::RenderWindow& window) const;
	void update(const float hp, sf::Vector2f characterPosition, float characterSize);

private:
	float maxHp;

	sf::RectangleShape hpBar;
	sf::RectangleShape hpBarBack;
};
