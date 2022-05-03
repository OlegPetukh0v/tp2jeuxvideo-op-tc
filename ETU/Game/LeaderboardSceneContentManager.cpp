#include "stdafx.h"
#include "LeaderboardSceneContentManager.h"

LeaderboardSceneContentManager::LeaderboardSceneContentManager()
{
}

bool LeaderboardSceneContentManager::loadContent()
{
	if (!backgroundTexture.loadFromFile("Assets\\Sprites\\Level01\\SpaceBackground.png"))
		return false;
	else
		backgroundTexture.setRepeated(true);
	return ContentManager::loadContent();
}

const sf::Texture& LeaderboardSceneContentManager::getBackgroundTexture() const
{
	return backgroundTexture;
}