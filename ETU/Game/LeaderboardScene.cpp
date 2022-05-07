#include "stdafx.h"
#include "LeaderboardScene.h"
#include "game.h"
#include <fstream>

const std::string LeaderboardScene::GAME_OVER = "GAME OVER";
const std::string LeaderboardScene::TITLE = "LEADERBOARD";
const std::string LeaderboardScene::ENTER_NAME = "PLEASE ENTER YOUR NAME";

LeaderboardScene::LeaderboardScene()
    : Scene(SceneType::LEADERBOARD)
{
}

LeaderboardScene::~LeaderboardScene()
{
}

SceneType LeaderboardScene::update()
{
    SceneType retval = getSceneType();
    if (sceneNeedsToChange)
    {
        retval = SceneType::NONE;
    }

    return retval;
}

void LeaderboardScene::draw(sf::RenderWindow& window) const
{
    window.draw(backgroundImage);
    window.draw(gameOverMessage);
    window.draw(titleMessage); 
    window.draw(enterNameMessage);
}

bool LeaderboardScene::init()
{
    if (contentManager.loadContent() == false)
    {
        return false;
    }
    backgroundImage.setTexture(contentManager.getBackgroundTexture());
    backgroundImage.setOrigin(backgroundImage.getLocalBounds().width * 0.5f, backgroundImage.getLocalBounds().height * 0.5f);
    backgroundImage.setPosition(Game::GAME_WIDTH * 0.5f, Game::GAME_HEIGHT * 0.5f);

    gameOverMessage.setFont(contentManager.getMainFont());
    gameOverMessage.setCharacterSize(64);
    gameOverMessage.setFillColor(sf::Color::Red);
    gameOverMessage.setString(GAME_OVER);
    gameOverMessage.setOrigin(gameOverMessage.getLocalBounds().width / 2.0f, gameOverMessage.getLocalBounds().height / 2.0f);
    gameOverMessage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 10.0f);

    titleMessage.setFont(contentManager.getMainFont());
    titleMessage.setCharacterSize(45);
    titleMessage.setFillColor(sf::Color::White);
    titleMessage.setString(TITLE);
    titleMessage.setOrigin(titleMessage.getLocalBounds().width / 2.0f, titleMessage.getLocalBounds().height / 2.0f);
    titleMessage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 5.0f);

    enterNameMessage.setFont(contentManager.getMainFont());
    enterNameMessage.setCharacterSize(25);
    enterNameMessage.setFillColor(sf::Color::White);
    enterNameMessage.setString(ENTER_NAME);
    enterNameMessage.setOrigin(enterNameMessage.getLocalBounds().width / 2.0f, enterNameMessage.getLocalBounds().height / 2.0f);
    enterNameMessage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 1.3f);

    readFromFile();

    sceneNeedsToChange = false;
	return true;
}

bool LeaderboardScene::uninit()
{
	return true;
}

bool LeaderboardScene::handleEvents(sf::RenderWindow& window)
{
    bool retval = false;
    sf::Event event;
    while (window.pollEvent(event))
    {
        //x sur la fenêtre
        if (event.type == sf::Event::Closed)
        {
            window.close();
            retval = true;
        }
    }
    return retval;
}

void LeaderboardScene::readFromFile()
{
    std::ifstream ifs("LeaderBoard.txt");
    if (!ifs)
        return; // selon ce que doit retourner la méthode qui fait la lecture
    std::string line;
    while (getline(ifs, line)) 
    {
        PlayerScore newPlayerScore;
        for (int i = 0; i < LeaderboardScene::NAME_LENGTH; i++)
        {
            newPlayerScore.name[i] = *line.substr(i, 1).c_str();
        }
        newPlayerScore.score = stoi(line.substr(LeaderboardScene::NAME_LENGTH));
        playerScores.push_back(newPlayerScore);
    }
    ifs.close();
}

void LeaderboardScene::orderPlayerScores()
{
    struct {
        bool operator()(PlayerScore playerA, PlayerScore playerB) const {
            return playerA.score < playerB.score;
        }
    } customLess;
    std::sort(playerScores.begin(), playerScores.end(), customLess);
}
