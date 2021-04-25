#pragma once

#include <stdlib.h>

#include "resources.h"
#include "utilities.h"

#define MAP_WIDTH 12
#define MAP_HEIGHT 25

typedef enum
State
  {
	 QUIT,
	 MAIN,
	 GAME,
	 INTERMISSION,
	 FAIL,
	 WIN
  } State;

typedef enum
MoveDir
  {
	 LEFT,
	 RIGHT,
	 DOWN
  } MoveDir;

typedef struct
GameState
{
  State state;
  int window_width, window_height, current_time;
  float delta_time;

  int player_x, player_y;
  _Bool player_direction;
  int player_fuel, player_max_fuel;
  int player_money;
  int player_depth;
  int player_bombs;
  char *tiles;

  int boss_counter;
} GameState;

void GameState_initialize (GameState *state, int width, int height);
void GameState_update (GameState *state);
void GameState_generate_tiles (GameState *state, ResourceManager *mgr);
void GameState_next_level (GameState *state, ResourceManager *mgr);

void GameState_player_move (GameState *state, ResourceManager *mgr, MoveDir dir);
void GameState_use_bomb (GameState *state, ResourceManager *mgr);
