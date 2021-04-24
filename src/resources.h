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
	 GEM_3
  } Sprites;

typedef struct
ResourceManager
{
  SDL_Texture *spritesheet;
  SDL_Texture *logo;
  Mix_Chunk *destroy, *gem1, *gem2;
} ResourceManager;

void ResourceManager_initialize (ResourceManager *mgr, SDL_Renderer *renderer);
