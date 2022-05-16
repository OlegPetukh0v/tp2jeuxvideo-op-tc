#pragma once
#include "GameObject.h"
class AttackBonus :
    public GameObject
{
public:
	static const int PICKUP_VOLUME;
	static const int SPEED;
	static const int SCALE;

	virtual bool update(float elapsedTime);
	virtual void deactivate() override;
	virtual void initialize(const sf::Texture& texture, const sf::Vector2f& initialPosition) override;
	virtual void init(const GameContentManager& gameContentManager);
protected:
	GameContentManager contentManager;
	sf::Sound pickupSound;
};
