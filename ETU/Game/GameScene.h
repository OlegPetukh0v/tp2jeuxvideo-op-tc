#pragma once
#include "Scene.h"
#include "scenetype.h"
#include "GameContentManager.h"
#include "Player.h"
#include "Inputs.h"
#include "PoolManager.h"
#include "Spawner.h"
#include "Hud.h"
#include "Boss.h"

class GameScene :
    public Scene, public Subscriber
{
public:
    static const int BACKGROUND_SPEED;

    GameScene();
    ~GameScene();
    virtual SceneType update() override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    virtual bool handleEvents(sf::RenderWindow& window) override;
    virtual void notify(Event event, const void* data);
private:
    GameContentManager contentManager;
    PoolManager pooler;
    Spawner spawner;
    Boss boss;

    sf::Sprite backgroundImage;
    sf::Music gameMusic;
    Hud hud;
    Inputs inputs;

    sf::Clock clock;

    Player player;
    int scrollPos;

    bool gameHasEnded;
    bool gameNeedsToEnd;
};
