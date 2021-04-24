#include "state.h"

void
GameState_initialize (GameState *state, int width, int height)
{
  state->window_width = width;
  state->window_height = height;
  state->running = 1;

  state->player_x = 5;
  state->player_y = 1;
  state->player_fuel = 20;

  state->tiles = malloc (sizeof (char) * MAP_WIDTH * MAP_HEIGHT);

  if (state->tiles == NULL)
	 {
		FATAL ("Could not allocate memory for tiles.");
	 }
}

void
GameState_generate_tiles (GameState *state)
{
  for (int y = 0; y < MAP_HEIGHT; ++y)
	 {
		for (int x = 0; x < MAP_WIDTH; ++x)
		  {
			 if (y < 2)
				{
				  int r = rand () % 100;
				  if (r > 80)
					 {
						state->tiles[y * MAP_WIDTH + x] = STARS_1;
					 }
				  else if (r > 50 && r <= 80)
					 {
						state->tiles[y * MAP_WIDTH + x] = STARS_3;
					 }
				  else
					 {
						state->tiles[y * MAP_WIDTH + x] = STARS_2;
					 }
				}
			 else
				{
				  state->tiles[y * MAP_WIDTH + x] = STONE;
				}
		  }
	 }
}
