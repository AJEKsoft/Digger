#include "state.h"

void
GameState_initialize (GameState *state, int width, int height)
{
  state->window_width = width;
  state->window_height = height;

  state->player_x = 5;
  state->player_y = 3;
  state->player_direction = 0;
  state->player_max_fuel = 25;
  state->player_fuel = state->player_max_fuel;
  state->player_money = 0;
  state->player_depth = 0;

  state->tiles = malloc (sizeof (char) * MAP_WIDTH * MAP_HEIGHT);

  if (state->tiles == NULL)
	 {
		FATAL ("Could not allocate memory for tiles.");
	 }

  state->state = MAIN;
}

void
GameState_next_level (GameState *state)
{
  state->player_x = 5;
  state->player_y = 3;  
  GameState_generate_tiles (state);
}

void
GameState_generate_tiles (GameState *state)
{
  for (int y = 0; y < MAP_HEIGHT; ++y)
	 {
		for (int x = 0; x < MAP_WIDTH; ++x)
		  {
			 if (y < 4)
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
				  int r = rand () % 100;

				  if (r > 95)
					 {
						state->tiles[y * MAP_WIDTH + x] = GEM_1;
					 }
				  else if (r > 85 && r <= 95)
					 {
						state->tiles[y * MAP_WIDTH + x] = GEM_2;
					 }
				  else if (r > 75 && r <= 85)
					 {
						state->tiles[y * MAP_WIDTH + x] = GEM_3;
					 }
				  else
					 {
						state->tiles[y * MAP_WIDTH + x] = STONE;	
					 }
				}
		  }
	 }
}

void
GameState_player_move_left (GameState *state)
{
  state->player_direction = 0;

  if (state->player_x > 0 && state->player_fuel > 0)
	 {
		switch (state->tiles[(state->player_y * MAP_WIDTH + state->player_x - 1)])
		  {
		  case STONE:
			 state->player_money = state->player_money + 10;
			 goto stuff;
		  case GEM_1:
			 state->player_money = state->player_money + 50;
			 goto stuff;
		  case GEM_2:
			 state->player_money = state->player_money + 100;
			 goto stuff;
		  case GEM_3:
			 state->player_money = state->player_money + 250;
			 goto stuff;
		  stuff:
			 state->tiles[(state->player_y * MAP_WIDTH + state->player_x - 1)] = BACKGROUND;
			 state->player_x = state->player_x - 1;
			 state->player_fuel = state->player_fuel - 1;
			 break;
		  default:
			 state->player_x = state->player_x - 1;
			 break;
		  }
	 }

  if (state->player_fuel == 0)
	 {
		state->state = INTERMISSION;
	 }
}

void
GameState_player_move_right (GameState *state)
{
  state->player_direction = 1;

  if (state->player_x < MAP_WIDTH - 1 && state->player_fuel > 0)
	 {
		switch (state->tiles[(state->player_y * MAP_WIDTH + state->player_x + 1)])
		  {
		  case STONE:
			 state->player_money = state->player_money + 10;
			 goto stuff;
		  case GEM_1:
			 state->player_money = state->player_money + 50;
			 goto stuff;
		  case GEM_2:
			 state->player_money = state->player_money + 100;
			 goto stuff;
		  case GEM_3:
			 state->player_money = state->player_money + 250;
			 goto stuff;
		  stuff:
			 state->tiles[(state->player_y * MAP_WIDTH + state->player_x + 1)] = BACKGROUND;
			 state->player_x = state->player_x + 1;
			 state->player_fuel = state->player_fuel - 1;
			 break;
		  default:
			 state->player_x = state->player_x + 1;
			 break;
		  }
	 }

  if (state->player_fuel == 0)
	 {
		state->state = INTERMISSION;
	 }
}

void
GameState_player_move_down (GameState *state)
{
  if (state->player_y < MAP_HEIGHT - 1 && state->player_fuel > 0)
	 {
		switch (state->tiles[((state->player_y + 1) * MAP_WIDTH + state->player_x)])
		  {
		  case STONE:
			 state->player_money = state->player_money + 10;
			 goto stuff;
		  case GEM_1:
			 state->player_money = state->player_money + 50;
			 goto stuff;
		  case GEM_2:
			 state->player_money = state->player_money + 100;
			 goto stuff;
		  case GEM_3:
			 state->player_money = state->player_money + 250;
			 goto stuff;
		  stuff:
			 state->tiles[((state->player_y + 1) * MAP_WIDTH + state->player_x)] = BACKGROUND;
			 state->player_y = state->player_y + 1;
			 state->player_fuel = state->player_fuel - 1;
			 state->player_depth = state->player_depth + 1;
			 break;
		  default:
			 break;
		  }	
	 }

  if (state->player_fuel == 0)
	 {
		state->state = INTERMISSION;
	 }
}
