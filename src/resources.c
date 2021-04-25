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

  if (logo == NULL)
	 {
		FATAL ("Could not load logo: %s", SDL_GetError ());
	 }

  mgr->logo = SDL_CreateTextureFromSurface (renderer, logo);
  SDL_FreeSurface (logo);

  SDL_Surface *bomb = SDL_LoadBMP ("res/bomb.bmp");

  if (bomb == NULL)
	 {
		FATAL ("Could not load bomb: %s", SDL_GetError ());
	 }

  mgr->bomb = SDL_CreateTextureFromSurface (renderer, bomb);
  SDL_FreeSurface (bomb);

  mgr->destroy = Mix_LoadWAV ("res/destroy.wav");
  mgr->gem1 = Mix_LoadWAV ("res/gem1.wav");
  mgr->gem2 = Mix_LoadWAV ("res/gem2.wav");
  mgr->explode = Mix_LoadWAV ("res/explode.wav");
  mgr->click = Mix_LoadWAV ("res/click.wav");
  mgr->error = Mix_LoadWAV ("res/error.wav");
  mgr->main_theme = Mix_LoadWAV ("res/main_theme.wav");
}
