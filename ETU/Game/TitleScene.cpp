#include "stdafx.h"
#include "TitleScene.h"
#include "game.h"

const std::string TitleScene::PRESS_KEY_MESSAGE = "PRESS ANY KEY TO START";
const int TitleScene::MUSIC_VOLUME = 50;

TitleScene::TitleScene()
	: Scene(SceneType::TITLE_SCENE)
{
}

TitleScene::~TitleScene()
{

}
SceneType TitleScene::update()
{
	if (onLoad) {
		titleMusic->play();
		onLoad = false;
	}
	if (!playGame) return getSceneType();
	else {
		titleMusic->stop();
		playGame = false;
		onLoad = true;
		return SceneType::GAME;
	}
}

void TitleScene::draw(sf::RenderWindow& window) const
{
	window.draw(menuImage);
	window.draw(pressKeyMessage);
}

bool TitleScene::init()
{
	if (false == contentManager.loadContent())
		return false;
	playGame = false;
	onLoad = false;

	menuImage.setTexture(contentManager.getBackgroundTexture());
	menuImage.setOrigin(menuImage.getTexture()->getSize().x / 2.0f, menuImage.getTexture()->getSize().y / 2.0f);
	menuImage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 2.0f);

	titleMusic = const_cast<sf::Music*>(&contentManager.getTitleMusic());
	titleMusic->setLoop(true);
	titleMusic->setVolume(MUSIC_VOLUME);
	titleMusic->play();

	pressKeyMessage.setFont(contentManager.getMainFont());
	pressKeyMessage.setCharacterSize(24);
	pressKeyMessage.setFillColor(sf::Color::White);
	pressKeyMessage.setString(PRESS_KEY_MESSAGE);
	pressKeyMessage.setOrigin(pressKeyMessage.getLocalBounds().width / 2.0f, pressKeyMessage.getLocalBounds().height / 2.0f);
	pressKeyMessage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 1.25f);

	return true;
}

bool TitleScene::uninit()
{
	return true;
}

bool TitleScene::handleEvents(sf::RenderWindow& window)
{
	bool retval = false;
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
			retval = true;
		}
		else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed) {
			playGame = true;
		}
	}
	return retval;

}
