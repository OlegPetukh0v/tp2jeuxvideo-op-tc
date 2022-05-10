#include "stdafx.h"
#include "LeaderboardScene.h"
#include "game.h"
#include <fstream>
#include <iostream>
#include "PlayerScore.h"

const std::string LeaderboardScene::GAME_OVER = "GAME OVER";
const std::string LeaderboardScene::TITLE = "LEADERBOARD";
const std::string LeaderboardScene::ENTER_NAME = "PLEASE ENTER YOUR NAME";
const std::string LeaderboardScene::EMPTY_STRING_NAME = "   ";
const unsigned int LeaderboardScene::INITIAL_PLAYER_POSIITON_IN_LEADERBOARD = -1;
const float LeaderboardScene::X_POSITION_LEADERBOARD_NAME = Game::GAME_WIDTH / 5.0f;
const float LeaderboardScene::NAME_HEIGHT = 22;
const unsigned int LeaderboardScene::X_POSITION_INITIAL_SCORE_HEIGHT = Game::GAME_HEIGHT / 3.0f;

LeaderboardScene::LeaderboardScene()
    : Scene(SceneType::LEADERBOARD)
{
}

LeaderboardScene::~LeaderboardScene()
{
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
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space)
                inputs.enter = true;
            else
            {
                inputs.newLetter = static_cast<char>(event.text.unicode + 65);
                std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode + 65) << std::endl;
            }
        }
    }
    return retval;
}

SceneType LeaderboardScene::update()
{
    SceneType retval = getSceneType();
    if (sceneNeedsToChange)
    {
        retval = SceneType::NONE;
    }
    if (isPlayerInTop5 && inputs.newLetter != ' ')
    {
        setNewPlayerName(inputs.newLetter);
        leaderboard[0][playerPosition].setString(playerName);
        leaderboard[0][playerPosition].setOrigin(leaderboard[0][playerPosition].getLocalBounds().width / 2.0f, leaderboard[0][playerPosition].getLocalBounds().height / 2.0f);
        inputs.newLetter = ' ';
    }
    return retval;
}

void LeaderboardScene::draw(sf::RenderWindow& window) const
{
    window.draw(backgroundImage);
    window.draw(gameOverMessage);
    window.draw(titleMessage); 
    window.draw(enterNameMessage);
    drawLeaderboard(window);
}

void LeaderboardScene::drawLeaderboard(sf::RenderWindow& window) const
{
    for (int i = 0; i < NB_COLUMNS_FOR_SCORE; i++)
    {
        for (int j = 0; j < SCORES_SHOWN; j++)
        {
            window.draw(leaderboard[i][j]);
        }
    }
}

bool LeaderboardScene::init()
{
    if (contentManager.loadContent() == false)
    {
        return false;
    }
    isPlayerInTop5 = false;
    playerPosition = INITIAL_PLAYER_POSIITON_IN_LEADERBOARD;

    //pas fonctionnel pour l'instant
    populateLeaderboardFile();

    readFromFile();
    // TODO: delete when dev finished
    result.gameSceneResult.score = 9000;
    addNewPlayerToList();
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
    writeResultToFile();
	return true;
}

void LeaderboardScene::initMessages()
{
    initGameOverMessage();
    initTitleMessage();
    initEnterNameMessage();
    initLeaderboardMessages();
}

void LeaderboardScene::initLeaderboardMessages()
{
    std::list<PlayerScore> tempPlayerScores = playerScores;
    for (int i = 0; i < playerScores.size(); i++)
    {
        sf::Text* currentName = &leaderboard[0][i];
        currentName->setFont(contentManager.getMainFont());
        currentName->setCharacterSize(25);
        if (playerPosition == i)
            currentName->setFillColor(sf::Color::Yellow);
        else
            currentName->setFillColor(sf::Color::White);
        currentName->setString(tempPlayerScores.front().getName());
        currentName->setOrigin(leaderboard[0][i].getLocalBounds().width / 2.0f, leaderboard[0][i].getLocalBounds().height / 2.0f);
        if (i == 0)
            currentName->setPosition(X_POSITION_LEADERBOARD_NAME, Game::GAME_HEIGHT / 3.0f);
        else
        {
            currentName->setPosition(X_POSITION_LEADERBOARD_NAME, leaderboard[0][i - 1].getPosition().y + (NAME_HEIGHT * 2));
        }
        tempPlayerScores.pop_front();
    }
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
    newPlayer.setName("OLE");
    newPlayer.setScore(12000);
    ofs.write((char*)&newPlayer, sizeof(PlayerScore));
    newPlayer.setName("THO");
    newPlayer.setScore(13000);
    ofs.write((char*)&newPlayer, sizeof(PlayerScore));
    newPlayer.setName("JDG");
    newPlayer.setScore(14000);
    ofs.write((char*)&newPlayer, sizeof(PlayerScore));
    newPlayer.setName("PWD");
    newPlayer.setScore(8000);
    ofs.write((char*)&newPlayer, sizeof(PlayerScore));
    newPlayer.setName("BAD");
    newPlayer.setScore(2000);
    ofs.write((char*)&newPlayer, sizeof(PlayerScore));
    ofs.close();
}

std::string LeaderboardScene::getTop5Players() const 
{
    std::string top5;
    std::list<PlayerScore> tempPlayerScores = playerScores;
    for (int i = 0; i < SCORES_SHOWN; i++)
    {
        if (!tempPlayerScores.empty())
        {
            PlayerScore currentPlayer = tempPlayerScores.front();
            tempPlayerScores.pop_front();
            top5 += (currentPlayer.getName() + std::to_string(currentPlayer.getScore()) + "\n");
        }
    }
    return top5;
}

void LeaderboardScene::setTop5Players()
{
    std::list<PlayerScore> tempPlayerScores = playerScores;
    std::list<PlayerScore> newPlayerScores;
    tempPlayerScores.sort();
    tempPlayerScores.reverse();
    for (int i = 0; i < SCORES_SHOWN; i++)
    {
        if (!tempPlayerScores.empty())
        {
            if (tempPlayerScores.front().isEmpty())
            {
                isPlayerInTop5 = true;
                playerPosition = i;
            }
            newPlayerScores.push_back(tempPlayerScores.front());
            tempPlayerScores.pop_front();
        }
    }
    playerScores = newPlayerScores;
}

void LeaderboardScene::addNewPlayerToList()
{
    PlayerScore newPlayer;
    newPlayer.setName(EMPTY_STRING_NAME);
    newPlayer.setScore(result.gameSceneResult.score);
    playerScores.push_back(newPlayer);

}

void LeaderboardScene::setNewPlayerName(char newChar)
{
    for (int i = 0; i < playerPosition; i++)
    {
        playerScores.push_back(playerScores.front());
        playerScores.pop_front();
    }

    std::cout << "get name: " << playerScores.front().getName() << std::endl;
    playerScores.front().addLetterToName(newChar);
    playerName = playerScores.front().getName();
    playerScores.sort();
    playerScores.reverse();
}

void LeaderboardScene::writeResultToFile()
{
    std::ofstream ofs("Leaderboard.txt");
    for (PlayerScore playerScore : playerScores)
    {
        ofs.write((char*)&playerScore, sizeof(PlayerScore));
    }
    ofs.close();
}
