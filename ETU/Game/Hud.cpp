#include "stdafx.h"
#include "Hud.h"
#include "Game.h"
#include "GameContentManager.h"

const std::string Hud::SCORE_TEXT = "Score: ";
const std::string Hud::DEFAULT_SCORE_TEXT = "Score: 0 ";
const float Hud::Y_POSITION_TXT = Game::GAME_HEIGHT / 1.1f;
const unsigned int Hud::CHARACTER_SIZE = 10;

Hud::Hud()
{

}

void Hud::init(GameContentManager& contentManager)
{
	heart.setTexture(contentManager.getMiscTexture());
	heart.setTextureRect(sf::IntRect(229, 64, 9, 10));
	heart.setOrigin(heart.getLocalBounds().width / 2.0f, heart.getLocalBounds().height / 2.0f);
	heart.setPosition(Game::GAME_WIDTH / 5.0f, Y_POSITION_TXT);

	bonus.setTexture(contentManager.getMiscTexture());
	bonus.setTextureRect(sf::IntRect(205, 104, 15, 15));
	bonus.setOrigin(bonus.getLocalBounds().width / 2.0f, bonus.getLocalBounds().height / 2.0f);
	bonus.setPosition(Game::GAME_WIDTH / 1.5f, Y_POSITION_TXT);

	score.setFont(contentManager.getMainFont());
	score.setCharacterSize(CHARACTER_SIZE);
	score.setFillColor(sf::Color::White);
	score.setString(DEFAULT_SCORE_TEXT);
	score.setOrigin(score.getLocalBounds().width / 2.0f, score.getLocalBounds().height / 2.0f);
	score.setPosition(Game::GAME_WIDTH / 7.0f, Y_POSITION_TXT);
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
