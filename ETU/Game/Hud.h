#pragma once
class Hud
{
public:
	static const std::string SCORE_TEXT;
	Hud();
	void draw(sf::RenderWindow& window) const;
	void setScore(const int newScore);
	void setLives(const int newScore);

private:
	sf::View hudView;
	sf::Text score;
	sf::Text lives;
	sf::Text time;
	sf::Sprite heart;
	sf::Sprite bonus;

};
// SCORE: 1000      heart life bonus time