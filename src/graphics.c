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
						&(SDL_Rect) { state->player_direction * 16, 0, 16, 16 },
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
							 &(SDL_Rect) { 6, 6, (MAP_WIDTH * 16 - 12) * state->player_fuel / state->player_max_fuel, 4});
}

void
GraphicsContext_draw_money (GraphicsContext *ctx, GameState *state)
{
  char str[64];
  sprintf (str, "$%d", state->player_money);

  SDL_SetRenderDrawColor (ctx->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect (ctx->renderer,
							 &(SDL_Rect) { 4, 16, strlen (str) * 8 + 3, 11 });
  
  stringRGBA (ctx->renderer, 6, 18, str, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void
GraphicsContext_draw_depth (GraphicsContext *ctx, GameState *state)
{
  char str[64];
  sprintf (str, "%d m", state->player_depth);

  SDL_SetRenderDrawColor (ctx->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect (ctx->renderer,
							 &(SDL_Rect) { 4, 31, strlen (str) * 8 + 3, 11 });
  
  stringRGBA (ctx->renderer, 6, 33, str, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void
GraphicsContext_draw_main_menu (GraphicsContext *ctx, ResourceManager *res_mgr)
{
  SDL_RenderCopy (ctx->renderer, res_mgr->logo, NULL,
						&(SDL_Rect) { 64, 16, 64, 32 });

  stringRGBA (ctx->renderer, 32, 64, "Press any key...", 255, 255, 255, SDL_ALPHA_OPAQUE);
  stringRGBA (ctx->renderer, 48, 96, "Instructions", 255, 255, 255, SDL_ALPHA_OPAQUE);
  stringRGBA (ctx->renderer, 24, 112, "Arrow keys to move", 255, 255, 255, SDL_ALPHA_OPAQUE);

  stringRGBA (ctx->renderer, 40, MAP_HEIGHT * 16 - 16 - 8, "(!C) Emil Kosz", 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void
GraphicsContext_draw_intermission (GraphicsContext *ctx, GameState *state, ResourceManager *res_mgr)
{
  SDL_RenderCopy (ctx->renderer, res_mgr->logo, NULL,
						&(SDL_Rect) { 64, 16, 64, 32 });

  stringRGBA (ctx->renderer, 40, 64, "You've reached", 255, 255, 255, SDL_ALPHA_OPAQUE);
  stringRGBA (ctx->renderer, 56, 80, "a depth of", 255, 255, 255, SDL_ALPHA_OPAQUE);

  char str[64];
  sprintf (str, "%d m", state->player_depth);
  stringRGBA (ctx->renderer, MAP_WIDTH * 16 / 2 - strlen (str) / 2 * 8, 96, str, 255, 255, 255, SDL_ALPHA_OPAQUE);

  stringRGBA (ctx->renderer, 64, 128, "You have", 255, 255, 255, SDL_ALPHA_OPAQUE);

  sprintf (str, "$%d", state->player_money);
  stringRGBA (ctx->renderer, MAP_WIDTH * 16 / 2 - strlen (str) / 2 * 8, 144, str, 255, 255, 255, SDL_ALPHA_OPAQUE);

  stringRGBA (ctx->renderer, 32, 176, "What do you want", 255, 255, 255, SDL_ALPHA_OPAQUE);

  sprintf (str, "a) fuel, %d/%d ($50)", state->player_fuel, state->player_max_fuel);
  
  stringRGBA (ctx->renderer, MAP_WIDTH * 16 / 2 - strlen (str) / 2 * 8, 192, str, 255, 255, 255, SDL_ALPHA_OPAQUE);

  stringRGBA (ctx->renderer, 16, 208, "b) fuel size ($500)", 255, 255, 255, SDL_ALPHA_OPAQUE);

  stringRGBA (ctx->renderer, 16, 240, "Press SPACE to leave", 255, 255, 255, SDL_ALPHA_OPAQUE);
  
  (void) state;
}

void
GraphicsContext_update (GraphicsContext *ctx, GameState *state, ResourceManager *res_mgr)
{
  SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear (ctx->renderer);

  switch (state->state)
	 {
	 case MAIN:
		GraphicsContext_draw_main_menu (ctx, res_mgr);
		break;
	 case GAME:
		GraphicsContext_draw_tiles (ctx, state, res_mgr);
		GraphicsContext_draw_fuel_bar (ctx, state);
		GraphicsContext_draw_money (ctx, state);
		GraphicsContext_draw_depth (ctx, state);
		GraphicsContext_draw_player (ctx, state, res_mgr);
		break;
	 case INTERMISSION:
		GraphicsContext_draw_intermission (ctx, state, res_mgr);
		break;
	 default:
		break;
	 }
  
  SDL_RenderPresent(ctx->renderer);
}
