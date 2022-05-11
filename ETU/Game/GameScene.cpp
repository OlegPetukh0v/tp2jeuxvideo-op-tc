#include "stdafx.h"
#include "GameScene.h"
#include "Game.h"
#include "PoolManager.h"
#include "Publisher.h"
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
    float deltaT = ((float)clock.getElapsedTime().asMilliseconds()) / 1000;
    clock.restart();

    backgroundImage.setTextureRect(sf::IntRect(0, (int)(scrollPos-=3), Game::GAME_WIDTH, Game::GAME_HEIGHT));

    player.update(deltaT, inputs);
    pooler.update(deltaT, player);
    spawner.update(deltaT);

    return getSceneType();
}

void GameScene::draw(sf::RenderWindow& window) const
{
    window.draw(backgroundImage);
    pooler.draw(window);
    player.draw(window);
    hud.draw(window);
}

bool GameScene::init()
{
    if (false == contentManager.loadContent())
        return false;
    scrollPos = 0;
    backgroundImage.setTexture(contentManager.getBackgroundTexture());
    if (!gameMusic.openFromFile("Assets\\Music\\Level01\\Albator-La-Bataille.ogg")) {
        return false;
    }
    gameMusic.setLoop(true);
    gameMusic.play();

    player.init(contentManager);
    pooler.init(contentManager);
    hud.init(contentManager);

    return true;
}

bool GameScene::uninit()
{
    pooler.uninit();
    return true;
}

bool GameScene::handleEvents(sf::RenderWindow& window)
{
    bool retval = false;
    inputs.reset();
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

    inputs.moveFactorY += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ? -1.0f : 0.0f;
    inputs.moveFactorY += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ? 1.0f : 0.0f;
    inputs.moveFactorX += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ? -3.0f : 0.0f;
    inputs.moveFactorX += sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ? 3.0f : 0.0f;
    inputs.fireBullet = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    return retval;
}
