#include "stdafx.h"
#include "BossAnimation.h"
#include "GameContentManager.h"

const float BossAnimation::ANIMATION_LENGTH = 2;

BossAnimation::BossAnimation(sf::Sprite& initialSprite)
	:CyclicAnimation(initialSprite, ANIMATION_LENGTH, true)
{
}

bool BossAnimation::init(const ContentManager& contentManager)
{
	const GameContentManager& gameContentManager = static_cast<const GameContentManager&>(contentManager);
	sf::Texture ennemiesTexture = gameContentManager.getEnemiesTexture();
	frames.push_back(AnimationFrame(ennemiesTexture, sf::IntRect(31, 1905, 86, 125)));
	frames.push_back(AnimationFrame(ennemiesTexture, sf::IntRect(132, 1905, 84, 127)));
	frames.push_back(AnimationFrame(ennemiesTexture, sf::IntRect(231, 1905, 78, 140)));
	frames.push_back(AnimationFrame(ennemiesTexture, sf::IntRect(328, 1905, 76, 144)));
	frames.push_back(AnimationFrame(ennemiesTexture, sf::IntRect(425, 1905, 76, 145)));
	frames.push_back(AnimationFrame(ennemiesTexture, sf::IntRect(521, 1905, 74, 148)));

	frames.push_back(AnimationFrame(ennemiesTexture, sf::IntRect(32, 2069, 72, 152)));
	frames.push_back(AnimationFrame(ennemiesTexture, sf::IntRect(139, 2069, 70, 156)));
	frames.push_back(AnimationFrame(ennemiesTexture, sf::IntRect(236, 2069, 70, 157)));
	frames.push_back(AnimationFrame(ennemiesTexture, sf::IntRect(334, 2069, 66, 172)));
	frames.push_back(AnimationFrame(ennemiesTexture, sf::IntRect(432, 2069, 66, 177)));
	frames.push_back(AnimationFrame(ennemiesTexture, sf::IntRect(530, 2069, 66, 179)));
	return true;
}
