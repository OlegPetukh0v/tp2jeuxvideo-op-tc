#include "stdafx.h"
#include "ShipAnimation.h"
#include "Inputs.h"
#include "ContentManager.h"
#include "GameContentManager.h"


ShipAnimation::ShipAnimation(sf::Sprite& initialSprite)
	:InputBasedAnimation(initialSprite)
{
}

bool ShipAnimation::init(const ContentManager& contentManager) {

	const GameContentManager& gameContentManager = static_cast<const GameContentManager&>(contentManager);
	frames.push_back(AnimationFrame(gameContentManager.getMainCharacterTexture(), sf::IntRect(325, 47, 14, 28)));
	frames.push_back(AnimationFrame(gameContentManager.getMainCharacterTexture(), sf::IntRect(301, 47, 18, 28)));
	frames.push_back(AnimationFrame(gameContentManager.getMainCharacterTexture(), sf::IntRect(269, 47, 26, 28)));
	frames.push_back(AnimationFrame(gameContentManager.getMainCharacterTexture(), sf::IntRect(246, 47, 18, 28)));
	frames.push_back(AnimationFrame(gameContentManager.getMainCharacterTexture(), sf::IntRect(227, 47, 14, 28)));

	return true;
}

void ShipAnimation::adjustNextFrame(const Inputs& inputs)
{
	if (inputs.moveFactorX > 0) {
		nbFrameInState = std::min(nbFrameInState + 1, 49);
	}
	else if (inputs.moveFactorX < 0) {
		nbFrameInState = std::max(nbFrameInState - 1, 0);
	}
	else {
		if (nbFrameInState < 25) nbFrameInState++;
		else if (nbFrameInState > 25) nbFrameInState--;
	}

	if (nbFrameInState > 40) nextFrame = 0;
	else if (nbFrameInState > 30) nextFrame = 1;
	else if (nbFrameInState > 20) nextFrame = 2;
	else if (nbFrameInState > 10) nextFrame = 3;
	else nextFrame = 4;
}