#pragma once
#include "stdafx.h"
#include "GameContentManager.h"
#include "InputBasedAnimation.h"

class ShipAnimation : public InputBasedAnimation
{
public:
	ShipAnimation(sf::Sprite& initialSprite);
	bool init(const ContentManager& contentManager);
	void adjustNextFrame(const Inputs& inputs);

private:
	int nbFrameInState;
};