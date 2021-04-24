#include "graphics.h"

void
GraphicsContext_initialize (GraphicsContext *ctx, GameState *state)
{
  ctx->window = SDL_CreateWindow ("Digger", SDL_WINDOWPOS_UNDEFINED,
											 SDL_WINDOWPOS_UNDEFINED, state->window_width,
											 state->window_height, 0);

  if (!ctx->window)
	 {
		FATAL ("Could not initialize SDL window: %s", SDL_GetError ());
	 }
  
  ctx->renderer = SDL_CreateRenderer (ctx->window, -1,
												  SDL_RENDERER_ACCELERATED);

  if (!ctx->window)
	 {
		FATAL ("Could not initialize SDL renderer: %s", SDL_GetError ());
	 }
}

void
GraphicsContext_draw_player (GraphicsContext *ctx, GameState *state, ResourceManager *res_mgr)
{
  SDL_RenderCopy (ctx->renderer, res_mgr->spritesheet,
						&(SDL_Rect) { DIGGER_L * 16, 0, 16, 16 },
						&(SDL_Rect) { state->player_x * 16, state->player_y * 16, 16, 16 });  
}


void
GraphicsContext_draw_tiles (GraphicsContext *ctx, GameState *state, ResourceManager *res_mgr)
{
  for (int y = 0; y < MAP_HEIGHT; ++y)
	 {
		for (int x = 0; x < MAP_WIDTH; ++x)
		  {
			 SDL_RenderCopy (ctx->renderer, res_mgr->spritesheet,
								  &(SDL_Rect) { state->tiles[y * MAP_WIDTH + x] * 16, 0, 16, 16},
								  &(SDL_Rect) { x * 16, y * 16, 16, 16 });
		  }
	 }
}

void
GraphicsContext_draw_fuel_bar (GraphicsContext *ctx, GameState *state)
{
  (void) state;
  SDL_SetRenderDrawColor (ctx->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect (ctx->renderer,
							 &(SDL_Rect) { 4, 4, MAP_WIDTH * 16 - 8, 8});
  SDL_SetRenderDrawColor (ctx->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect (ctx->renderer,
							 &(SDL_Rect) { 6, 6, (MAP_WIDTH * 16 - 12) * state->player_fuel / 25, 4});
}

void
GraphicsContext_update (GraphicsContext *ctx, GameState *state, ResourceManager *res_mgr)
{
  SDL_RenderClear (ctx->renderer);

  GraphicsContext_draw_tiles (ctx, state, res_mgr);
  GraphicsContext_draw_fuel_bar (ctx, state);
  GraphicsContext_draw_player (ctx, state, res_mgr);
  
  SDL_RenderPresent(ctx->renderer);
}
