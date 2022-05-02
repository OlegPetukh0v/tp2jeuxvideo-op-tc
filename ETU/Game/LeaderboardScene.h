#pragma once
#include "Scene.h"
#include "ContentManager.h"
#include "LeaderboardSceneContentManager.h"

class LeaderboardScene :
    public Scene
{
public:
    static const std::string GAME_OVER;
    static const std::string TITLE;
    static const std::string ENTER_NAME;

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
    sf::Text gameOverMessage;
    sf::Text titleMessage;
    sf::Text enterNameMessage;
    sf::Text leaderboardMessage;

    bool sceneNeedsToChange;
};
