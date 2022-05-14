#pragma once

struct GameSceneResult
{
  int score;
  bool hasPlayerWon;
};

union SceneResult
{
	GameSceneResult gameSceneResult;
};