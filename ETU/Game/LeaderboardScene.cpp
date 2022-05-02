#include "stdafx.h"
#include "LeaderboardScene.h"
#include "game.h"

const std::string LeaderboardScene::GAME_OVER = "GAME OVER";
const std::string LeaderboardScene::TITLE = "LEADERBOARD";
const std::string LeaderboardScene::ENTER_NAME = "PLEASE ENTER YOUR NAME";

LeaderboardScene::LeaderboardScene()
    : Scene(SceneType::LEADERBOARD)
{
}

LeaderboardScene::~LeaderboardScene()
{
}

SceneType LeaderboardScene::update()
{
    SceneType retval = getSceneType();
    if (sceneNeedsToChange)
    {
        retval = SceneType::NONE;
    }

    return retval;
}

void LeaderboardScene::draw(sf::RenderWindow& window) const
{
    window.draw(backgroundImage);
    window.draw(gameOverMessage);
}

bool LeaderboardScene::init()
{
    if (contentManager.loadContent() == false)
    {
        return false;
    }
    backgroundImage.setTexture(contentManager.getBackgroundTexture());
    backgroundImage.setOrigin(backgroundImage.getLocalBounds().width * 0.5f, backgroundImage.getLocalBounds().height * 0.5f);
    backgroundImage.setPosition(Game::GAME_WIDTH * 0.5f, Game::GAME_HEIGHT * 0.5f);

    gameOverMessage.setFont(contentManager.getMainFont());
    gameOverMessage.setCharacterSize(64);
    gameOverMessage.setFillColor(sf::Color::Red);
    gameOverMessage.setString(GAME_OVER);
    gameOverMessage.setOrigin(gameOverMessage.getLocalBounds().width / 2.0f, gameOverMessage.getLocalBounds().height / 2.0f);
    gameOverMessage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 10.0f);

    sceneNeedsToChange = false;
	return true;
}

bool LeaderboardScene::uninit()
{
	return true;
}

bool LeaderboardScene::handleEvents(sf::RenderWindow& window)
{
    bool retval = false;
    sf::Event event;
    while (window.pollEvent(event))
    {
        //x sur la fenêtre
        if (event.type == sf::Event::Closed)
        {
            window.close();
            retval = true;
        }
    }
    return retval;
}
