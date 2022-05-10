#pragma once
#include "stdafx.h"
#include "CyclicAnimation.h"

class EnemyShipAnimation :
	public CyclicAnimation
{
public:
	static const float ANIMATION_LENGTH;

	EnemyShipAnimation(sf::Sprite& initialSprite);
	bool init(const ContentManager& contentManager);
};