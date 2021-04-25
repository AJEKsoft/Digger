#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "utilities.h"

#define SPRITE_SIZE 16

typedef enum
Sprites
  {
	 DIGGER_L,
	 DIGGER_R,
	 STONE,
	 STARS_1,
	 STARS_2,
	 STARS_3,
	 BACKGROUND,
	 GEM_1,
	 GEM_2,
	 GEM_3,
	 BONE,
	 BONE_BROKEN,
	 LAVA,
	 WALL_1,
	 WALL_2,
	 WALL_3,
	 BOSS_NW,
	 BOSS_NE,
	 BOSS_SW,
	 BOSS_SE,
	 BOSS_DAMAGED_NW,
	 BOSS_DAMAGED_NE,
	 BOSS_DAMAGED_SW,
	 BOSS_DAMAGED_SE
  } Sprites;

typedef struct
ResourceManager
{
  SDL_Texture *spritesheet;
  SDL_Texture *logo;
  SDL_Texture *bomb;
  Mix_Chunk *destroy, *gem1, *gem2, *explode, *click, *error, *main_theme, *boss, *boss_music;
} ResourceManager;

void ResourceManager_initialize (ResourceManager *mgr, SDL_Renderer *renderer);
