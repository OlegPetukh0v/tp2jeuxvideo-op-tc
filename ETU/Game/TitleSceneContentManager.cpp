#include "stdafx.h"
#include "TitleSceneContentManager.h"

TitleSceneContentManager::TitleSceneContentManager()
{
}

bool TitleSceneContentManager::loadContent()
{
	if (!menuImage.loadFromFile("Assets\\Sprites\\Title\\Title.png"))
		return false;
	return ContentManager::loadContent();
}

const sf::Texture& TitleSceneContentManager::getBackgroundTexture() const
{
	return menuImage;
}
