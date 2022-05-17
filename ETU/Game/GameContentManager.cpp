#include "stdafx.h"
#include "GameContentManager.h"

GameContentManager::GameContentManager()
{
}

bool GameContentManager::loadContent()
{
	if (!backgroundTexture.loadFromFile("Assets\\Sprites\\Level01\\SpaceBackground.png"))
		return false;
	else
		backgroundTexture.setRepeated(true);
	if (!mainCharacterTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - The Guardian Alyssa.bmp"))
		return false;
	if (!miscTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - Miscellaneous.png"))
		return false;
	if (!enemiesTexture.loadFromFile("Assets\\Sprites\\Level01\\NES - The Guardian Legend - Bosses.bmp"))
		return false;
	if (!playerGunSoundBuffer.loadFromFile("Assets\\SoundFX\\Level01\\playerGun.wav"))
		return false;
	if (!enemyGunSoundBuffer.loadFromFile("Assets\\SoundFX\\Level01\\enemyGun.wav"))
		return false;
	if (!healthBonusSoundBuffer.loadFromFile("Assets\\SoundFX\\Level01\\healthBonus.wav"))
		return false;
	if (!gunBonusSoundBuffer.loadFromFile("Assets\\SoundFX\\Level01\\gunBonus.wav"))
		return false;
	if (!enemyKilledSoundBuffer.loadFromFile("Assets\\SoundFX\\Level01\\enemyKilled.wav"))
		return false;

	return ContentManager::loadContent();
}

const sf::Texture& GameContentManager::getEnemiesTexture() const
{
	return enemiesTexture;
}

const sf::Texture& GameContentManager::getBackgroundTexture() const
{
	return backgroundTexture;
}
const sf::Texture& GameContentManager::getMiscTexture() const
{
	return miscTexture;
}
const sf::Texture& GameContentManager::getMainCharacterTexture() const
{
	return mainCharacterTexture;
}
const sf::SoundBuffer& GameContentManager::getPlayerGunSoundBuffer() const
{
	return playerGunSoundBuffer;
}
const sf::SoundBuffer& GameContentManager::getEnemyGunSoundBuffer() const
{
	return enemyGunSoundBuffer;
}
const sf::SoundBuffer& GameContentManager::getHealthSoundBuffer() const
{
	return healthBonusSoundBuffer;
}
const sf::SoundBuffer& GameContentManager::getGunBonusSoundBuffer() const
{
	return gunBonusSoundBuffer;
}
const sf::SoundBuffer& GameContentManager::getEnemyKilledSoundBuffer() const
{
	return enemyKilledSoundBuffer;
}
