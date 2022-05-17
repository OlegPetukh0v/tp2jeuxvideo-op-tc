#pragma once
#include "stdafx.h"
#include "GameContentManager.h"
#include "InputBasedAnimation.h"

class ShipAnimation : public InputBasedAnimation
{
	static const unsigned int INITIAL_FRAMES_IN_STATE;
public:
	ShipAnimation(sf::Sprite& initialSprite);
	bool init(const ContentManager& contentManager);
	void adjustNextFrame(const Inputs& inputs);

private:
	int nbFrameInState;
};
