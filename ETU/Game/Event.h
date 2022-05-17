#pragma once

enum class Event 
{
  NONE,
  ENEMY_SPAWN,
  ENEMY_SHOOT,
  ENEMY_KILLED,
  PLAYER_SHOOT,
  PLAYER_DEATH,
  BOSS_SPAWN,
  BOSS_KILLED,
  HEALTH_PICKED_UP,
  GUN_PICKED_UP
};
