#pragma once
class PlayerScore
{
public:
	static const int NAME_LENGTH = 3;

	void setName(const std::string newName);
	void addLetterToName(const char letter);
	void deleteFrontLetter();
	void setScore(const int newScore);

	std::string getName() const;
	int getScore() const;

	bool operator <(const PlayerScore& studObj) const;
	bool isEmpty() const;
	bool isFullyFilled() const;

private:
	int score;
	char name[NAME_LENGTH];

};
