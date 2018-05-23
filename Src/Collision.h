#pragma once

#ifdef __APPLE__
#include "SDL2/SDL.h"
#elif _WIN32
#include "SDL.h"
#endif

class ColliderComponent;

class Collision {
public:
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
};
