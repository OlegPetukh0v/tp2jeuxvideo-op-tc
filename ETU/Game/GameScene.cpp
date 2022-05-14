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
    gameHasEnded = false;
}

GameScene::~GameScene()
{
}

SceneType GameScene::update()
{
    if (gameHasEnded)
        return SceneType::NONE;
    bool gameNeedsToEnd = false;
    float deltaT = ((float)clock.getElapsedTime().asMilliseconds()) / 1000;
    clock.restart();

    backgroundImage.setTextureRect(sf::IntRect(0, (int)(scrollPos-=3), Game::GAME_WIDTH, Game::GAME_HEIGHT));

    if (!player.update(deltaT, inputs))
        gameNeedsToEnd = true;
    
    pooler.update(deltaT, player);
    spawner.update(deltaT);
    boss.update(deltaT);
    // TODO: enlever quand on va avoir le cooldown du bonus
    int cooldown = 5;
    hud.update(player.getScore(), player.getHealth(), cooldown);

    if (gameNeedsToEnd)
    {
        result.gameSceneResult.hasPlayerWon = player.isAlive();
        result.gameSceneResult.score = player.getScore();
        gameHasEnded = true;
        return SceneType::LEADERBOARD;
    }

    return getSceneType();
}

void GameScene::draw(sf::RenderWindow& window) const
{
    window.draw(backgroundImage);
    pooler.draw(window);
    boss.draw(window);
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

    Publisher::addSubscriber(*this, Event::BOSS_SPAWN);

    player.init(contentManager);
    pooler.init(contentManager);
    hud.init(contentManager);
    boss.init(contentManager);
    spawner.init();

    return true;
}

bool GameScene::uninit()
{
    pooler.uninit();
    player.uninit();
    spawner.uninit();
    Publisher::removeSubscriber(*this, Event::BOSS_SPAWN);
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

void GameScene::notify(Event event, const void* data)
{
    if (event == Event::BOSS_SPAWN)
    {
        boss.activate();
    }
}
