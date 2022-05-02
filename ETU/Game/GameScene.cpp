#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene()
    : Scene(SceneType::GAME)
{
}

GameScene::~GameScene()
{
}


SceneType GameScene::update()
{
    return getSceneType();
}

void GameScene::draw(sf::RenderWindow& window) const
{
}

bool GameScene::init()
{
    return true;
}

bool GameScene::uninit()
{
    return true;
}

bool GameScene::handleEvents(sf::RenderWindow& window)
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
