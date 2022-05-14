#pragma once
#include "Scene.h"
#include "ContentManager.h"
#include "LeaderboardSceneContentManager.h"
#include "Inputs.h"

class PlayerScore;
class LeaderboardScene :
    public Scene
{
public:
    static const std::string GAME_OVER;
    static const std::string TITLE;
    static const std::string ENTER_NAME;
    static const std::string PRESS_TO_LEAVE;
    static const int SCORES_SHOWN = 5;
    static const int NB_COLUMNS_FOR_SCORE = 2;
    static const std::string EMPTY_STRING_NAME;
    static const unsigned int INITIAL_PLAYER_POSIITON_IN_LEADERBOARD;
    static const float X_POSITION_LEADERBOARD_NAME;
    static const float X_POSITION_LEADERBOARD_SCORE;
    static const float NAME_HEIGHT;
    static const unsigned int X_POSITION_INITIAL_SCORE_HEIGHT;

    LeaderboardScene();
    ~LeaderboardScene();
    virtual SceneType update() override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual bool init() override;
    virtual bool uninit() override;
    virtual bool handleEvents(sf::RenderWindow& window) override;
private:
    LeaderboardSceneContentManager contentManager;
    Inputs inputs;

    sf::Sprite backgroundImage;
    sf::Text gameOverMessage;
    sf::Text titleMessage;
    sf::Text enterNameMessage;
    sf::Text top5Message;
    sf::Text leaderboard[NB_COLUMNS_FOR_SCORE][SCORES_SHOWN];

    std::list<PlayerScore> playerScores;

    void initMessages();
    void initGameOverMessage();
    void initTitleMessage();
    void initEnterNameMessage();
    void initLeaderboardMessages();
    void drawLeaderboard(sf::RenderWindow& window) const;

    bool nameconfirmed;

    void readFromFile();
    void populateLeaderboardFile();
    void writeResultToFile();

    std::string getTop5Players() const;
    void setTop5Players();
    void getPlayerInFrontOfList();
    void reorderList();
    void deleteCharacterFromPlayerName();

    void addNewPlayerToList();
    bool isPlayerInTop5;
    int playerPosition;
    void setNewPlayerName(char newChar);
    std::string playerName;
    bool playerNameConfirmed;
    void setPlayerNameConfirmed();
};
