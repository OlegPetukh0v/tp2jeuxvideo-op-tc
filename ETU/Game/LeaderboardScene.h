#pragma once
#include "Scene.h"
#include "ContentManager.h"
#include "LeaderboardSceneContentManager.h"

class LeaderboardScene :
    public Scene
{
public:

    LeaderboardScene();
    ~LeaderboardScene();
    virtual SceneType update() override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    virtual bool handleEvents(sf::RenderWindow& window) override;
private:
    LeaderboardSceneContentManager contentManager;

    sf::Sprite backgroundImage;

    bool sceneNeedsToChange;
};
