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
	 INTERMISSION
  } State;

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
  char *tiles;
} GameState;

void GameState_initialize (GameState *state, int width, int height);
void GameState_generate_tiles (GameState *state);
void GameState_next_level (GameState *state);

void GameState_player_move_left (GameState *state, ResourceManager *mgr);
void GameState_player_move_right (GameState *state, ResourceManager *mgr);
void GameState_player_move_down (GameState *state, ResourceManager *mgr);
