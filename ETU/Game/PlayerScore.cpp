#include "stdafx.h"
#include "PlayerScore.h"

void PlayerScore::setName(const std::string newName)
{
    for (int i = 0; i < sizeof(name); i++)
    {
        this->name[i] = newName.at(i);
    }
}

void PlayerScore::addLetterToName(const char letter)
{
    for (int i = 0; i < sizeof(name); i++)
    {
        if (name[i] == ' ')
        {
            name[i] = letter;
            return;
        }
    }
}

void PlayerScore::deleteFrontLetter()
{
    for (int i = sizeof(name) - 1; i >= 0; i--)
    {
        if (name[i] != ' ')
        {
            name[i] = ' ';
            return;
        }
    }
}

void PlayerScore::setScore(const int newScore)
{
    this->score = newScore;
}

bool PlayerScore::operator <(const PlayerScore& studObj) const
{
    return score < studObj.score;
}

bool PlayerScore::isEmpty() const
{
    for (int i = 0; i < sizeof(name); i++)
    {
        if (name[i] != ' ')
            return false;
    }
    return true;
}

bool PlayerScore::isFullyFilled() const
{
    for (int i = 0; i < sizeof(name); i++)
    {
        if (name[i] == ' ')
            return false;
    }
    return true;
}

std::string PlayerScore::getName() const
{
    std::string stringName = "";
    for (int i = 0; i < NAME_LENGTH; i++)
        stringName += name[i];
    return stringName;
}

int PlayerScore::getScore() const
{
    return this->score;
}