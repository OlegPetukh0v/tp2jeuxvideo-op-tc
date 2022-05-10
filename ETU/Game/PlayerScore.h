#pragma once
class PlayerScore
{
public:
	static const int NAME_LENGTH = 3;

	void setName(std::string newName);
	void addLetterToName(char letter);
	void deleteFrontLetter();
	void setScore(const int newScore);

	std::string getName() const;
	int getScore() const;

	bool operator <(const PlayerScore& studObj) const;
	bool isEmpty() const;
private:
	int score;
	char name[NAME_LENGTH];
};

