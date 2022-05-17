#pragma once
#include "stdafx.h"
#include "GameContentManager.h"
#include "InputBasedAnimation.h"

class ShipAnimation : public InputBasedAnimation
{
public:
	static const int CENTER_ANIMATION;
	ShipAnimation(sf::Sprite& initialSprite);
	bool init(const ContentManager& contentManager);
	void adjustNextFrame(const Inputs& inputs);

private:
	int nbFrameInState;
};