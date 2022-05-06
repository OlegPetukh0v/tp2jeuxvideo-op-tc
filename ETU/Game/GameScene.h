#pragma once
#include "Scene.h"
#include "scenetype.h"
#include "GameContentManager.h"
#include "Player.h"
#include "Inputs.h"
class GameScene :
    public Scene
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
private:
    GameContentManager contentManager;
    sf::Sprite backgroundImage;
    sf::Sprite backgroundImage2;
    Player player;
    Inputs inputs;
};
