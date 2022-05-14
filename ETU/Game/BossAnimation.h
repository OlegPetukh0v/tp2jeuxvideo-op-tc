#pragma once
#include "CyclicAnimation.h"
class BossAnimation :
    public CyclicAnimation
{
public:
	static const float ANIMATION_LENGTH;

	BossAnimation(sf::Sprite& initialSprite);
	bool init(const ContentManager& contentManager);
};
