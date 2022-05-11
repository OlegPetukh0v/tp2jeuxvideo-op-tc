#include "stdafx.h"
#include "Hud.h"

const std::string Hud::SCORE_TEXT = "Score: ";

Hud::Hud()
{

}

void Hud::draw(sf::RenderWindow& window) const
{
	window.setView(hudView);
	window.draw(score);
	window.draw(lives);
}

void Hud::setScore(const int newScore)
{
	score.setString(SCORE_TEXT + std::to_string(newScore));
}

void Hud::setLives(const int newLives)
{
	lives.setString(std::to_string(newLives));
}
