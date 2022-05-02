#include "stdafx.h"
#include "LeaderboardScene.h"
#include "game.h"

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
}

bool LeaderboardScene::init()
{
    if (contentManager.loadContent() == false)
    {
        return false;
    }
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
