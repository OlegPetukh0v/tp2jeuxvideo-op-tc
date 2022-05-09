#include "stdafx.h"
#include "EnemyShipAnimation.h"
#include "GameContentManager.h"

const float EnemyShipAnimation::ANIMATION_LENGTH = 2;

EnemyShipAnimation::EnemyShipAnimation(sf::Sprite& initialSprite)
	:CyclicAnimation(initialSprite, ANIMATION_LENGTH, true)
{
}

bool EnemyShipAnimation::init(const ContentManager& contentManager)
{
	const GameContentManager& gameContentManager = static_cast<const GameContentManager&>(contentManager);
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(24, 917, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(97, 917, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(170, 917, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(243, 917, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(316, 917, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(389, 917, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(462, 917, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(535, 917, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(608, 917, 73, 96)));

	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(24, 1031, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(97, 1031, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(170, 1031, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(243, 1031, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(316, 1031, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(389, 1031, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(462, 1031, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(535, 1031, 73, 96)));
	frames.push_back(AnimationFrame(gameContentManager.getEnemiesTexture(), sf::IntRect(608, 1031, 73, 96)));
	return true;
}

