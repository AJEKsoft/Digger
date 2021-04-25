#include "state.h"

void
GameState_initialize (GameState *state, int width, int height)
{
  state->window_width = width;
  state->window_height = height;

  state->player_x = 5;
  state->player_y = 4;
  state->player_direction = 0;
  state->player_max_fuel = 200;
  state->player_fuel = state->player_max_fuel;
  state->player_money = 0;
  state->player_depth = 390;
  state->player_bombs = 50;
  state->boss_counter = 0;
  
  state->tiles = malloc (sizeof (char) * MAP_WIDTH * MAP_HEIGHT);

  if (state->tiles == NULL)
	 {
		FATAL ("Could not allocate memory for tiles.");
	 }

  state->state = MAIN;
}

void
GameState_update (GameState *state)
{
  (void) state;
}

void
GameState_next_level (GameState *state, ResourceManager *mgr)
{
  state->player_x = 5;
  state->player_y = 4;
  state->boss_counter = 0;
  GameState_generate_tiles (state, mgr);
}

void
GameState_generate_tiles (GameState *state, ResourceManager *mgr)
{
  for (int y = 0; y < MAP_HEIGHT; ++y)
	 {
		for (int x = 0; x < MAP_WIDTH; ++x)
		  {
			 if (y < 5)
				{
				  if (state->player_depth == 0)
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
						state->tiles[y * MAP_WIDTH + x] = BACKGROUND;
					 }
				}
			 else
				{
				  int r = rand () % 100;

				  if (state->player_depth < 100)
					 {
						if (r > 95)
						  {
							 state->tiles[y * MAP_WIDTH + x] = GEM_1;
						  }
						else if (r > 85 && r <= 95)
						  {
							 state->tiles[y * MAP_WIDTH + x] = GEM_2;
						  }
						else if (r > 80 && r <= 85)
						  {
							 state->tiles[y * MAP_WIDTH + x] = GEM_3;
						  }
						else
						  {
							 state->tiles[y * MAP_WIDTH + x] = STONE;	
						  }						
					 }
				  else if (state->player_depth > 100 && state->player_depth <= 200)
					 {
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
						else if (r > 73 && r <= 75)
						  {
							 state->tiles[y * MAP_WIDTH + x] = BONE;
						  }
						else if (r > 68 && r <= 73)
						  {
							 if (y != MAP_HEIGHT - 1)
								{
								  state->tiles[y * MAP_WIDTH + x] = LAVA;
								}
							 else
								{
								  state->tiles[y * MAP_WIDTH + x] = BONE;
								}
						  }
						else
						  {
							 state->tiles[y * MAP_WIDTH + x] = STONE;	
						  }
					 }
				  else if (state->player_depth > 200 && state->player_depth <= 400)
					 {
						if (r > 90)
						  {
							 state->tiles[y * MAP_WIDTH + x] = GEM_1;
						  }
						else if (r > 80 && r <= 90)
						  {
							 state->tiles[y * MAP_WIDTH + x] = GEM_2;
						  }
						else if (r > 65 && r <= 80)
						  {
							 state->tiles[y * MAP_WIDTH + x] = GEM_3;
						  }
						else if (r > 57 && r <= 65)
						  {
							 state->tiles[y * MAP_WIDTH + x] = BONE;
						  }
						else if (r > 49 && r <= 57)
						  {
							 if (y != MAP_HEIGHT - 1)
								{
								  state->tiles[y * MAP_WIDTH + x] = LAVA;
								}
							 else
								{
								  state->tiles[y * MAP_WIDTH + x] = BONE;
								}
						  }
						else
						  {
							 state->tiles[y * MAP_WIDTH + x] = STONE;	
						  }
					 }
				  else
					 {
						if (y < 10)
						  {
							 state->tiles[y * MAP_WIDTH + x] = WALL_1;
						  }
						else if (y < 12)
						  {
							 state->tiles[y * MAP_WIDTH + x] = BONE;
						  }
						else
						  {
							 state->tiles[y * MAP_WIDTH + x] = STONE;
						  }

						
					 }
				}
		  }
	 }

  if (state->player_depth > 400)
	 {
		state->tiles[17 * MAP_WIDTH + 5] = BOSS_NW;
		state->tiles[17 * MAP_WIDTH + 6] = BOSS_NE;
		state->tiles[18 * MAP_WIDTH + 5] = BOSS_SW;
		state->tiles[18 * MAP_WIDTH + 6] = BOSS_SE;

		Mix_PlayChannel (0, mgr->boss_music, -1);
	 }
}

int
GameState_break_tile (GameState *state, ResourceManager *mgr, char *tile, _Bool bomb)
{
  switch (*tile)
	 {
	 case STONE:
		*tile = BACKGROUND;
		state->player_money = state->player_money + 10;
		Mix_PlayChannel (-1, mgr->destroy, 0);
		return 1;
	 case GEM_1:
		*tile = BACKGROUND;
		state->player_money = state->player_money + 50;
		Mix_PlayChannel (-1, mgr->gem1, 0);
		return 1;
	 case GEM_2:
		*tile = BACKGROUND;
		state->player_money = state->player_money + 100;
		Mix_PlayChannel (-1, mgr->gem1, 0);
		return 1;
	 case GEM_3:
		*tile = BACKGROUND;
		state->player_money = state->player_money + 250;
		Mix_PlayChannel (-1, mgr->gem2, 0);
		return 1;
	 case BONE:
		*tile = BONE_BROKEN;
		if (!bomb)
		  {
			 state->player_fuel = state->player_fuel - 3;
		  }
		Mix_PlayChannel (-1, mgr->destroy, 0);
		return 0;
	 case BONE_BROKEN:
		*tile = BACKGROUND;
		state->player_money = state->player_money + 1000;
		Mix_PlayChannel (-1, mgr->gem2, 0);
		return 1;
	 case LAVA:
		*tile = BACKGROUND;
		if (!bomb)
		  {
			 state->player_fuel = state->player_fuel - 10;
		  }
		Mix_PlayChannel (-1, mgr->explode, 0);
		return 1;
	 case WALL_1:
		*tile = WALL_2;
		if (!bomb)
		  {
			 state->player_fuel = state->player_fuel - 20;
		  }
		Mix_PlayChannel (-1, mgr->destroy, 0);
		return 0;
	 case WALL_2:
		*tile = WALL_3;
		if (!bomb)
		  {
			 state->player_fuel = state->player_fuel - 10;
		  }
		Mix_PlayChannel (-1, mgr->destroy, 0);
		return 0;
	 case WALL_3:
		*tile = BACKGROUND;
		if (!bomb)
		  {
			 state->player_fuel = state->player_fuel - 10;
		  }
		state->player_money = state->player_money + 10;
		Mix_PlayChannel (-1, mgr->destroy, 0);
		return 1;
	 case BOSS_NW:
		if (!bomb)
		  {
			 *tile = BOSS_DAMAGED_NW;
			 state->player_fuel = state->player_fuel - 20;
			 Mix_PlayChannel (-1, mgr->boss, 0);
		  }
		return 0;
	 case BOSS_NE:
		if (!bomb)
		  {
			 *tile = BOSS_DAMAGED_NE;
			 state->player_fuel = state->player_fuel - 20;
			 Mix_PlayChannel (-1, mgr->boss, 0);
		  }
		return 0;
	 case BOSS_SW:
		if (!bomb)
		  {
			 *tile = BOSS_DAMAGED_SW;
			 state->player_fuel = state->player_fuel - 20;
			 Mix_PlayChannel (-1, mgr->boss, 0);
		  }
		return 0;
	 case BOSS_SE:
		if (!bomb)
		  {
			 *tile = BOSS_DAMAGED_SE;
			 state->player_fuel = state->player_fuel - 20;
			 Mix_PlayChannel (-1, mgr->boss, 0);
		  }
		return 0;
	 case BOSS_DAMAGED_NW:
		if (!bomb)
		  {
			 *tile = BACKGROUND;
			 state->player_fuel = state->player_fuel - 20;
			 state->boss_counter = state->boss_counter + 1;
			 Mix_PlayChannel (-1, mgr->boss, 0);
		  }
		return 1;
	 case BOSS_DAMAGED_NE:
		if (!bomb)
		  {
			 *tile = BACKGROUND;
			 state->player_fuel = state->player_fuel - 20;
			 state->boss_counter = state->boss_counter + 1;
			 Mix_PlayChannel (-1, mgr->boss, 0);
		  }
		return 1;
	 case BOSS_DAMAGED_SW:
		if (!bomb)
		  {
			 *tile = BACKGROUND;
			 state->player_fuel = state->player_fuel - 20;
			 state->boss_counter = state->boss_counter + 1;
			 Mix_PlayChannel (-1, mgr->boss, 0);
		  }
		return 1;
	 case BOSS_DAMAGED_SE:
		if (!bomb)
		  {
			 *tile = BACKGROUND;
			 state->player_fuel = state->player_fuel - 20;
			 state->boss_counter = state->boss_counter + 1;
			 Mix_PlayChannel (-1, mgr->boss, 0);
		  }
		return 1;		

	 default:
		return 1;
	 }
}

void
GameState_player_move (GameState *state, ResourceManager *mgr, MoveDir dir)
{
  char *tile = NULL;
  
  switch (dir)
	 {
	 case LEFT:
		if (state->player_x > 0)
		  {
			 state->player_direction = 0;
			 tile = &state->tiles[(state->player_y * MAP_WIDTH + state->player_x - 1)];
		  }
		break;
	 case RIGHT:
		if (state->player_x < MAP_WIDTH - 1)
		  {
			 state->player_direction = 1;
			 tile = &state->tiles[(state->player_y * MAP_WIDTH + state->player_x + 1)];
		  }
		break;
	 case DOWN:
		if (state->player_y < MAP_HEIGHT - 1)
		  {
			 tile = &state->tiles[((state->player_y + 1) * MAP_WIDTH + state->player_x)];
		  }
		break;
	 }

  if (tile != NULL && state->player_fuel > 0)
	 {
		if (GameState_break_tile (state, mgr, tile, 0))
		  {
			 state->player_x = state->player_x - (dir == LEFT ? 1 : dir == RIGHT ? -1 : 0);
			 state->player_y = state->player_y + (dir == DOWN ? 1 : 0);
			 state->player_fuel = state->player_fuel - 1;
			 if (dir == DOWN)
				{
				  state->player_depth = state->player_depth + 1;
				}
		  }			 
	 }

  if (state->player_fuel <= 0 && state->player_money < 50)
	 {
		state->state = FAIL;
	 }
  else if (state->player_fuel <= 0)
	 {
		state->state = INTERMISSION;
	 }

  if (state->boss_counter == 4)
	 {
		state->state = WIN;
	 }
}

void
GameState_use_bomb (GameState *state, ResourceManager *mgr)
{
  int minx = MAX (state->player_x - 1, 0);
  int miny = MAX (state->player_y - 1, 0);
  int maxx = MIN (state->player_x + 1, MAP_WIDTH - 1);
  int maxy = MIN (state->player_y + 1, MAP_HEIGHT - 1);
  
  for (int x = minx; x <= maxx; ++x)
	 {
		for (int y = miny; y <= maxy; ++y)
		  {
			 GameState_break_tile (state, mgr, &state->tiles[y * MAP_WIDTH + x], 1);
		  }
	 }

  if (state->player_y < MAP_HEIGHT - 1
		&& state->tiles[(state->player_y + 1) * MAP_WIDTH + state->player_x] == BACKGROUND)
	 {
		state->player_y = state->player_y + 1;
	 }

  state->player_bombs = state->player_bombs - 1;
}
