#include "stdafx.h"
#include "Hud.h"
#include "Game.h"
#include "GameContentManager.h"

const std::string Hud::SCORE_TEXT = "Score: ";
const float Hud::Y_POSITION_TXT = Game::GAME_HEIGHT / 1.03f + 8;
const unsigned int Hud::CHARACTER_SIZE = 24;
const unsigned int Hud::HUD_HEIGHT = 48;
const float Hud::HEART_SCALE = 3.3f;
const float Hud::BONUS_SCALE = 2.3f;
const unsigned int Hud::DEFAULT_SCORE = 0;
const unsigned int Hud::DEFAULT_TIME = 0;
const unsigned int Hud::DEFAULT_LIVES = 300;

Hud::Hud()
{

}

void Hud::init(GameContentManager& contentManager)
{
	hudView = sf::View(sf::FloatRect(0, 0, (float)Game::GAME_WIDTH, (float)Game::GAME_HEIGHT));
	setLives(DEFAULT_LIVES);
	setScore(DEFAULT_SCORE);

	initScore(contentManager);
	initHeart(contentManager);
	initBonus(contentManager);
	initLives(contentManager);
	initTime(contentManager);
}

void Hud::initScore(GameContentManager& contentManager)
{
	score.setFont(contentManager.getMainFont());
	score.setCharacterSize(CHARACTER_SIZE);
	score.setFillColor(sf::Color::White);
	score.setOrigin(score.getLocalBounds().width / 2.0f, score.getLocalBounds().height / 2.0f);
	score.setPosition(Game::GAME_WIDTH / 6.0f, Y_POSITION_TXT);
}

void Hud::initHeart(GameContentManager& contentManager)
{
	heart.setTexture(contentManager.getMiscTexture());
	heart.setTextureRect(sf::IntRect(229, 64, 11, 10));
	heart.setOrigin(heart.getLocalBounds().width / 2.0f, heart.getLocalBounds().height / 2.0f);
	heart.setPosition(Game::GAME_WIDTH / 1.6f, Y_POSITION_TXT);
	heart.scale(sf::Vector2f(HEART_SCALE, HEART_SCALE));
}

void Hud::initBonus(GameContentManager& contentManager)
{
	bonus.setTexture(contentManager.getMiscTexture());
	bonus.setTextureRect(sf::IntRect(205, 104, 15, 15));
	bonus.setOrigin(bonus.getLocalBounds().width / 2.0f, bonus.getLocalBounds().height / 2.0f);
	bonus.setPosition(Game::GAME_WIDTH / 1.2f, Y_POSITION_TXT);
	bonus.scale(sf::Vector2f(BONUS_SCALE, BONUS_SCALE));
}

void Hud::initLives(GameContentManager& contentManager)
{
	lives.setFont(contentManager.getMainFont());
	lives.setCharacterSize(CHARACTER_SIZE);
	lives.setFillColor(sf::Color::White);
	lives.setString(std::to_string(DEFAULT_LIVES));
	lives.setOrigin(score.getLocalBounds().width / 2.0f, score.getLocalBounds().height / 2.0f);
	lives.setPosition(Game::GAME_WIDTH / 1.25f, Y_POSITION_TXT);
}

void Hud::initTime(GameContentManager& contentManager)
{
	time.setFont(contentManager.getMainFont());
	time.setCharacterSize(CHARACTER_SIZE);
	time.setFillColor(sf::Color::White);
	time.setString(std::to_string(DEFAULT_TIME));
	time.setOrigin(score.getLocalBounds().width / 2.0f, score.getLocalBounds().height / 2.0f);
	time.setPosition(Game::GAME_WIDTH * 1.03f, Y_POSITION_TXT);
}

void Hud::update(unsigned int score, unsigned int playerHealth, unsigned int bonusCountdown)
{
	setScore(score);
	setLives(playerHealth);
	time.setString(std::to_string(bonusCountdown));
}

void Hud::draw(sf::RenderWindow& window) const
{
	window.setView(hudView);
	window.draw(score);
	window.draw(heart);
	window.draw(lives);
	window.draw(bonus);
	window.draw(time);
}

void Hud::setScore(const int newScore)
{
	score.setString(SCORE_TEXT + std::to_string(newScore));
}

void Hud::setLives(const int newLives)
{
	lives.setString(std::to_string(newLives));
}
