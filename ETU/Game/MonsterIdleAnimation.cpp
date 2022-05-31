#include "stdafx.h"
#include "MonsterIdleAnimation.h"
#include "GameContentManager.h"

const float MonsterIdleAnimation::ANIMATION_LENGTH = 2;

MonsterIdleAnimation::MonsterIdleAnimation(sf::Sprite& initialSprite)
	:CyclicAnimation(initialSprite, ANIMATION_LENGTH, true)
{
}

bool MonsterIdleAnimation::init(const ContentManager& contentManager)
{
	const GameContentManager& gameContentManager = static_cast<const GameContentManager&>(contentManager);
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(81, 359, 46, 110)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(138, 359, 46, 110)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(195, 359, 46, 110)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(258, 359, 46, 110)));

	return true;
}
