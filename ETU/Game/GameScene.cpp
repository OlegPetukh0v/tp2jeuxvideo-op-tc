#include "stdafx.h"
#include "GameScene.h"
#include "Game.h"
#include <iostream>

const int GameScene::BACKGROUND_SPEED = 3;

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
    backgroundImage.setPosition(backgroundImage.getPosition() + sf::Vector2f(0, BACKGROUND_SPEED));
    backgroundImage2.setPosition(backgroundImage2.getPosition() + sf::Vector2f(0, BACKGROUND_SPEED));

    if (backgroundImage.getPosition().y > backgroundImage.getGlobalBounds().height) {
        backgroundImage.setPosition(0, -backgroundImage.getGlobalBounds().height); 
    }
    if (backgroundImage2.getPosition().y > backgroundImage.getGlobalBounds().height) {
        backgroundImage2.setPosition(0, -backgroundImage.getGlobalBounds().height); // GAME::CONST ?
    }

    return getSceneType();
}

void GameScene::draw(sf::RenderWindow& window) const
{
    window.draw(backgroundImage);
    window.draw(backgroundImage2);
}

bool GameScene::init()
{
    if (false == contentManager.loadContent())
        return false;
    backgroundImage.setTexture(contentManager.getBackgroundTexture());
    backgroundImage2.setTexture(contentManager.getBackgroundTexture());
    backgroundImage2.setPosition(0, -backgroundImage2.getGlobalBounds().height);
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
