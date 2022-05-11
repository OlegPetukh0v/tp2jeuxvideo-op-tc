#include "stdafx.h"
#include "TitleSceneContentManager.h"

TitleSceneContentManager::TitleSceneContentManager()
{
}

bool TitleSceneContentManager::loadContent()
{
	if (!menuImage.loadFromFile("Assets\\Sprites\\Title\\Title.png"))
		return false;
	if (!titleMusic.openFromFile("Assets\\Music\\Title\\SkyFire (Title Screen).ogg"))
		return false;
	return ContentManager::loadContent();
}

const sf::Texture& TitleSceneContentManager::getBackgroundTexture() const
{
	return menuImage;
}

const sf::Music& TitleSceneContentManager::getTitleMusic() const
{
	return titleMusic;
}
