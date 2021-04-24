#pragma once

#include <stdlib.h>

#include "resources.h"
#include "utilities.h"

#define MAP_WIDTH 11
#define MAP_HEIGHT 25

typedef struct
GameState
{
  _Bool running;
  int window_width, window_height, current_time;
  float delta_time;

  int player_x, player_y;
  int player_fuel;
  char *tiles;
} GameState;

void GameState_initialize (GameState *state, int width, int height);
void GameState_generate_tiles (GameState *state);
