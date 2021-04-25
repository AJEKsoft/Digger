#include "graphics.h"

int
main ()
{
  SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO);

  Mix_Init (0);
  if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
	 {
		FATAL ("Could not initialize audio: %s", SDL_GetError ());
	 }

  GameState state = { 0 };
  /* 11 x 25, tiles 11 x 23 */
  GameState_initialize (&state, MAP_WIDTH * 16, MAP_HEIGHT * 16);
  
  GraphicsContext gfx_ctx = { 0 };
  GraphicsContext_initialize (&gfx_ctx, &state);

  ResourceManager res_mgr = { 0 };
  ResourceManager_initialize (&res_mgr, gfx_ctx.renderer);

  GameState_generate_tiles (&state, &res_mgr);

  Mix_PlayChannel (0, res_mgr.main_theme, -1);
  
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
								GameState_player_move (&state, &res_mgr, LEFT);
								break;
							 case SDLK_RIGHT:
								GameState_player_move (&state, &res_mgr, RIGHT);
								break;
							 case SDLK_DOWN:
								GameState_player_move (&state, &res_mgr, DOWN);
								break;
							 case SDLK_RETURN:
								if (state.player_bombs > 0)
								  {
									 GameState_use_bomb (&state, &res_mgr);
								  }
								break;
							 }
						  break;
						case INTERMISSION:
						  switch (e.key.keysym.sym)
							 {
							 case SDLK_a:
								if (state.player_money >= 50
									 && state.player_fuel < state.player_max_fuel)
								  {
									 state.player_fuel = state.player_fuel + 1;
									 state.player_money = state.player_money - 50;
									 Mix_PlayChannel (-1, res_mgr.click, 0);
								  }
								else
								  {
									 Mix_PlayChannel (-1, res_mgr.error, 0);
								  }
								break;
							 case SDLK_b:
								if (state.player_money >= 500)
								  {
									 state.player_max_fuel = state.player_max_fuel + 1;
									 state.player_money = state.player_money - 500;
									 Mix_PlayChannel (-1, res_mgr.click, 0);
								  }
								else
								  {
									 Mix_PlayChannel (-1, res_mgr.error, 0);
								  }
								break;
							 case SDLK_c:
								if (state.player_money >= 800)
								  {
									 state.player_bombs = state.player_bombs + 1;
									 state.player_money = state.player_money - 800;
									 Mix_PlayChannel (-1, res_mgr.click, 0);
								  }
								else
								  {
									 Mix_PlayChannel (-1, res_mgr.error, 0);
								  }
								break;
							 case SDLK_SPACE:
								GameState_next_level (&state, &res_mgr);
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

		GameState_update (&state);
		GraphicsContext_update (&gfx_ctx, &state, &res_mgr);
	 }

  SDL_Quit ();
  
  return 0;
}
