#include "stdafx.h"
#include "LeaderboardScene.h"
#include "game.h"
#include <fstream>
#include <iostream>

const std::string LeaderboardScene::GAME_OVER = "GAME OVER";
const std::string LeaderboardScene::TITLE = "LEADERBOARD";
const std::string LeaderboardScene::ENTER_NAME = "PLEASE ENTER YOUR NAME";
const int LeaderboardScene::SCORES_SHOWN = 5;

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
    // TODO: if change occured and player is in top 5, set name to new name

    return retval;
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

void LeaderboardScene::draw(sf::RenderWindow& window) const
{
    window.draw(backgroundImage);
    window.draw(gameOverMessage);
    window.draw(titleMessage); 
    window.draw(enterNameMessage);
    window.draw(top5Message);
}

bool LeaderboardScene::init()
{
    if (contentManager.loadContent() == false)
    {
        return false;
    }
    isPlayerInTop5 = false;

    //pas fonctionnel pour l'instant
    //populateLeaderboardFile();

    writeResultToFile();
    readFromFile();
    setTop5Players();

    backgroundImage.setTexture(contentManager.getBackgroundTexture());
    backgroundImage.setOrigin(backgroundImage.getLocalBounds().width * 0.5f, backgroundImage.getLocalBounds().height * 0.5f);
    backgroundImage.setPosition(Game::GAME_WIDTH * 0.5f, Game::GAME_HEIGHT * 0.5f);

    initMessages();

    sceneNeedsToChange = false;
	return true;
}

bool LeaderboardScene::uninit()
{
	return true;
}

void LeaderboardScene::initMessages()
{
    initGameOverMessage();
    initTitleMessage();
    initEnterNameMessage();
    initTop5Message();
}

void LeaderboardScene::initGameOverMessage()
{
    gameOverMessage.setFont(contentManager.getMainFont());
    gameOverMessage.setCharacterSize(64);
    gameOverMessage.setFillColor(sf::Color::Red);
    gameOverMessage.setString(GAME_OVER);
    gameOverMessage.setOrigin(gameOverMessage.getLocalBounds().width / 2.0f, gameOverMessage.getLocalBounds().height / 2.0f);
    gameOverMessage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 10.0f);
}

void LeaderboardScene::initTitleMessage()
{
    titleMessage.setFont(contentManager.getMainFont());
    titleMessage.setCharacterSize(45);
    titleMessage.setFillColor(sf::Color::White);
    titleMessage.setString(TITLE);
    titleMessage.setOrigin(titleMessage.getLocalBounds().width / 2.0f, titleMessage.getLocalBounds().height / 2.0f);
    titleMessage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 5.0f);
}

void LeaderboardScene::initEnterNameMessage()
{
    enterNameMessage.setFont(contentManager.getMainFont());
    enterNameMessage.setCharacterSize(25);
    enterNameMessage.setFillColor(sf::Color::White);
    enterNameMessage.setString(ENTER_NAME);
    enterNameMessage.setOrigin(enterNameMessage.getLocalBounds().width / 2.0f, enterNameMessage.getLocalBounds().height / 2.0f);
    enterNameMessage.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 1.3f);
}

void LeaderboardScene::initTop5Message()
{
    top5Message.setFont(contentManager.getMainFont());
    top5Message.setCharacterSize(25);
    top5Message.setFillColor(sf::Color::White);
    top5Message.setString(getTop5Players());
    top5Message.setOrigin(top5Message.getLocalBounds().width / 2.0f, top5Message.getLocalBounds().height / 2.0f);
    top5Message.setPosition(Game::GAME_WIDTH / 2.0f, Game::GAME_HEIGHT / 2.0f);
}

void LeaderboardScene::readFromFile()
{
    std::ifstream ifs("Leaderboard.txt");
    if (!ifs)
        return;
    PlayerScore newPlayer;
    while (ifs.read((char*)&newPlayer, sizeof(PlayerScore))) {
        playerScores.push_back(newPlayer);
    }
    ifs.close();
}

void LeaderboardScene::populateLeaderboardFile()
{
    std::ifstream ifs("Leaderboard.txt");
    if (!ifs)
        return;
    std::ofstream ofs("Leaderboard.txt");
    PlayerScore newPlayer;
    newPlayer.name[0] = (char)"O";
    newPlayer.name[1] = (char)"L";
    newPlayer.name[2] = (char)"E";
    newPlayer.score = 91000;
    ofs.write((char*)&newPlayer, sizeof(PlayerScore));
    ofs.close();
}

std::string LeaderboardScene::getTop5Players() const 
{
    std::string top5;
    std::list<PlayerScore> tempPlayerScores = playerScores;
    tempPlayerScores.sort();
    tempPlayerScores.reverse();
    for (int i = 0; i < SCORES_SHOWN; i++)
    {
        if (!tempPlayerScores.empty())
        {
            PlayerScore currentPlayer = tempPlayerScores.front();
            tempPlayerScores.pop_front();
            top5 += (currentPlayer.name + std::to_string(currentPlayer.score) + "\n");
        }
    }
    return top5;
}

void LeaderboardScene::setTop5Players()
{
    std::list<PlayerScore> tempPlayerScores = playerScores;
    tempPlayerScores.sort();
    tempPlayerScores.reverse();
    for (int i = 0; i < SCORES_SHOWN; i++)
    {
        if (!tempPlayerScores.empty())
        {
            top5Scores.push_back(tempPlayerScores.front());
            tempPlayerScores.pop_front();
        }
    }
}

void LeaderboardScene::writeResultToFile()
{
    std::ofstream ofs("Leaderboard.txt");
    // TODO: enlever quand on recoit des vrais valeurs de la partie
    result.gameSceneResult.score = 101;
    PlayerScore newPlayer;
    newPlayer.name[0] = 'A';
    newPlayer.name[1] = 'C';
    newPlayer.name[2] = 'E';
    newPlayer.score = result.gameSceneResult.score;
    ofs.write((char*)&newPlayer, sizeof(PlayerScore));
    ofs.close();
}
