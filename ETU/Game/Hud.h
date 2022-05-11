#pragma once
class GameContentManager;
class Hud
{
public:
	static const std::string SCORE_TEXT;
	static const std::string DEFAULT_SCORE_TEXT;
	static const float Y_POSITION_TXT;
	static const unsigned int CHARACTER_SIZE;
	Hud();
	void init(GameContentManager& contentManager);
	void draw(sf::RenderWindow& window) const;
	void setScore(const int newScore);
	void setLives(const int newLives);

private:
	sf::View hudView;
	sf::Text score;
	sf::Text lives;
	sf::Text time;
	sf::Sprite heart;
	sf::Sprite bonus;

};
// SCORE: 1000      heart life bonus time