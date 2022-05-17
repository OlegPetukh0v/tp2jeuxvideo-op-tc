#pragma once
#include "ContentManager.h"
class LeaderboardSceneContentManager :
	public ContentManager
{
public:
	LeaderboardSceneContentManager();
	virtual bool loadContent();
	const sf::Texture& getBackgroundTexture() const;

private:
	sf::Texture backgroundTexture;
};
