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
  
  while (state.state != QUIT)
	 {
		while (SDL_PollEvent (&e))
		  {
			 switch (e.type)
				{
				case SDL_QUIT:
				  {
					 state.state = QUIT;
				  }
				  break;
				case SDL_KEYDOWN:
				  {
					 switch (state.state)
						{
						case MAIN:
						  state.state = GAME;
						  break;
						case GAME:
						  switch (e.key.keysym.sym)
							 {
							 case SDLK_LEFT:
								GameState_player_move_left (&state);
								break;
							 case SDLK_RIGHT:
								GameState_player_move_right (&state);
								break;
							 case SDLK_DOWN:
								GameState_player_move_down (&state);
								break;
							 }
						  break;
						case INTERMISSION:
						  switch (e.key.keysym.sym)
							 {
							 case SDLK_a:
								if (state.player_money >= 100
									 && state.player_fuel < state.player_max_fuel)
								  {
									 state.player_fuel = state.player_fuel + 1;
									 state.player_money = state.player_money - 100;
								  }
								break;
							 case SDLK_b:
								if (state.player_money >= 500)
								  {
									 state.player_max_fuel = state.player_max_fuel + 1;
									 state.player_money = state.player_money - 500;
								  }
								break;
							 case SDLK_SPACE:
								GameState_next_level (&state);
								state.state = GAME;
								break;
							 }
						  break;
						default:
						  break;
						}
				  }
				  break;
				}
		  }

		GraphicsContext_update (&gfx_ctx, &state, &res_mgr);
	 }

  SDL_Quit ();
  
  return 0;
}
