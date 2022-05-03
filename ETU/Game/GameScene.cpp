#include "stdafx.h"
#include "GameScene.h"
#include "Game.h"
#include <iostream>

GameScene::GameScene()
    : Scene(SceneType::GAME)
{
}

GameScene::~GameScene()
{
}


SceneType GameScene::update()
{
    std::cout << "pos: " << backgroundImage.getPosition().y << std::endl;
    backgroundImage.setPosition(backgroundImage.getPosition() + sf::Vector2f(0, 1));
    if (backgroundImage.getPosition().y > 0) {
        backgroundImage.setPosition(0, -backgroundImage.getGlobalBounds().height + 1080); // GAME::CONST ?
    }

    return getSceneType();
}

void GameScene::draw(sf::RenderWindow& window) const
{
    window.draw(backgroundImage);
}

bool GameScene::init()
{
    if (false == contentManager.loadContent())
        return false;
    backgroundImage.setTexture(contentManager.getBackgroundTexture());
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
        //x sur la fen�tre
        if (event.type == sf::Event::Closed)
        {
            window.close();
            retval = true;
        }
    }
    return retval;
}
