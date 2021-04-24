#include "resources.h"

void
ResourceManager_initialize (ResourceManager *mgr, SDL_Renderer *renderer)
{
  SDL_Surface *spritesheet = SDL_LoadBMP ("res/spritesheet.bmp");

  if (spritesheet == NULL)
	 {
		FATAL ("Could not load spritesheet: %s", SDL_GetError ());
	 }

  mgr->spritesheet = SDL_CreateTextureFromSurface (renderer, spritesheet);
  SDL_FreeSurface (spritesheet);

  SDL_Surface *logo = SDL_LoadBMP ("res/logo.bmp");

  if (spritesheet == NULL)
	 {
		FATAL ("Could not load logo: %s", SDL_GetError ());
	 }

  mgr->logo = SDL_CreateTextureFromSurface (renderer, logo);
  SDL_FreeSurface (logo);
}
