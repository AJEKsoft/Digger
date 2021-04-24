#include "graphics.h"

int
main ()
{
  SDL_Init (SDL_INIT_VIDEO);

  GameState state = { 0 };
  /* 11 x 25, tiles 11 x 23 */
  GameState_initialize (&state, MAP_WIDTH * 16, MAP_HEIGHT * 16);
  GameState_generate_tiles (&state);
  
  GraphicsContext gfx_ctx = { 0 };
  GraphicsContext_initialize (&gfx_ctx, &state);

  ResourceManager res_mgr = { 0 };
  ResourceManager_initialize (&res_mgr, gfx_ctx.renderer);
  
  SDL_Event e;
  
  while (state.running)
	 {
		while (SDL_PollEvent (&e))
		  {
			 if (e.type == SDL_QUIT)
				{
				  state.running = 0;
				}
		  }

		GraphicsContext_update (&gfx_ctx, &state, &res_mgr);
	 }

  SDL_Quit ();
  
  return 0;
}
