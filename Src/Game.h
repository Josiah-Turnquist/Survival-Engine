#pragma once


#ifdef __APPLE__
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#elif _WIN32
#include "SDL.h"
#include "SDL_image.h"
#endif

#include <iostream>
#include <vector>

class AssetManager;
class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen); // Initializes all the important stuff you see.
    // ^ loads graphics and fonts into the game, initializes player, loads and initializes map, initialize enemies,
    // ^ assign all entities their proper components, etc.

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean(); // Handles SDL-related cleanup. 

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static bool isRunning;
	static SDL_Rect camera;
	static AssetManager* assets;
	enum groupLabels : std::size_t { // Public groups are used by the manager
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupEnemies
	};

private:

	int cnt = 0;
	SDL_Window *window;
};
