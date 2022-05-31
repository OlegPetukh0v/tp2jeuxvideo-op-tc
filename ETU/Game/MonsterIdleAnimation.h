#pragma once
#include "stdafx.h"
#include "CyclicAnimation.h"

class MonsterIdleAnimation :
	public CyclicAnimation
{
public:
	static const float ANIMATION_LENGTH;

	MonsterIdleAnimation(sf::Sprite& initialSprite);
	bool init(const ContentManager& contentManager);
};
