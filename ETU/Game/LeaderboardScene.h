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
    static const int NAME_LENGTH = 3;
    static const int SCORES_SHOWN;

    LeaderboardScene();
    ~LeaderboardScene();
    virtual SceneType update() override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    virtual bool handleEvents(sf::RenderWindow& window) override;

    struct PlayerScore
    {
        int score;
        char name[NAME_LENGTH];

        bool operator <(const PlayerScore& studObj) const
        {
            return score < studObj.score;
        }

        bool isEmpty() const
        {
            if (name[0] == (char)"" && name[1] == (char)"" && name[2] == (char)"") return true;
            return false;
        }
    };
private:
    LeaderboardSceneContentManager contentManager;

    sf::Sprite backgroundImage;
    sf::Text gameOverMessage;
    sf::Text titleMessage;
    sf::Text enterNameMessage;
    sf::Text top5Message;

    std::list<PlayerScore> playerScores;
    std::list<PlayerScore> top5Scores;

    void initMessages();
    void initGameOverMessage();
    void initTitleMessage();
    void initEnterNameMessage();
    void initTop5Message();

    bool sceneNeedsToChange;

    void readFromFile();
    void populateLeaderboardFile();
    void writeResultToFile();

    std::string getTop5Players() const;
    void setTop5Players();

    bool isPlayerInTop5;
    PlayerScore playerScore;
    std::string playerName;
};
