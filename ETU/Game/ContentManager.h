#pragma once
class ContentManager
{
public:
	ContentManager();
	virtual bool loadContent();

	const sf::Font& getMainFont() const;
private:
	sf::Font mainFont;
};



