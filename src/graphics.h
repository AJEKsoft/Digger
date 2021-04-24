#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "state.h"
#include "resources.h"
#include "utilities.h"

typedef struct
GraphicsContext
{
  SDL_Window *window;
  SDL_Renderer *renderer;
} GraphicsContext;

void GraphicsContext_initialize (GraphicsContext *ctx, GameState *state);
void GraphicsContext_update (GraphicsContext *ctx, GameState *state, ResourceManager *res_mgr);
