#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map* map;
Manager manager;

//text colors
SDL_Color white = { 255,255,255,255 };
SDL_Color red = { 255,0,0,0 };

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;

//player and stats text
auto& player(manager.addEntity());
auto& pScore(manager.addEntity());
auto& pHealth(manager.addEntity());
auto& eScore(manager.addEntity());
auto& escGame(manager.addEntity());

//enemies
auto& enemy1(manager.addEntity());
auto& enemy2(manager.addEntity());
auto& enemy3(manager.addEntity());
auto& enemy4(manager.addEntity());
auto& enemy5(manager.addEntity());
auto& enemy6(manager.addEntity());
auto& enemy7(manager.addEntity());
auto& enemy8(manager.addEntity());
auto& enemy9(manager.addEntity());
auto& enemy10(manager.addEntity());
auto& enemy11(manager.addEntity());
auto& enemy12(manager.addEntity());
auto& enemy13(manager.addEntity());
auto& enemy14(manager.addEntity());
auto& enemy15(manager.addEntity());


// Up until this point it just initializes a bunch of important crap. (enemies, player, manager, some global colors, etc.)

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen) //
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	if (TTF_Init() == -1) {
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	//add all the textures in
	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "assets/player_anims.png");
	assets->AddTexture("enemy", "assets/enemy.png");
	assets->AddTexture("end", "assets/end.png");

	//get a font
	assets->AddFont("arcade", "assets/ARCADECLASSIC.ttf", 30);

	//create the map and open it
	map = new Map("terrain", 2, 32);
	map->LoadMap("assets/map.map", 25, 20);
    delete map;

	//make player and give it all the functions
    
	player.addComponent<TransformComponent>(860, 600, 32, 32, 4); // (x, y, width, height, scale)
    // TransformComponent holds all position/velocity/image-scale variables. Important for anything graphic and moving.
	
    player.addComponent<SpriteComponent>("player", true); // (sprite-id, animatedTrueFalse)
    // SpriteComponent is responsible for animation and actually drawing the image to our render (its draw function is called via the game.render() -> manager.draw() -> entity.draw() -> SpriteComponent.draw()).
	
    player.addComponent<KeyboardController>(); // (no args)
    // KeyboardController in another component that simply takes in keyboard input by SDL commands to make things happen. Likely that only the player will have this component.
	
    player.addComponent<ColliderComponent>("player"); // (classifier)
    // ColliderComponent essentially gives the object a "collision box" per its sprite and classifier.
    
    player.addComponent<CharacteristicComponent>(); // (score, healthMax, health)
    
    player.addGroup(groupPlayers); // (enumerator)
    // This is not a component. addGroup assigns the entity (player) to the enumerator group 'groupPlayers' so the manager object may use its 2-dimensional pointer to cycle through all entities classified within its own group.

    
	//make a bunch of enemies that you run away from
	enemy1.addComponent<TransformComponent>(300, 600, 32, 32, 4);
	enemy1.addComponent<SpriteComponent>("enemy", true);
	enemy1.addComponent<ColliderComponent>("enemy");
	enemy1.addGroup(groupEnemies);

	enemy2.addComponent<TransformComponent>(400, 400, 32, 32, 4);
	enemy2.addComponent<SpriteComponent>("enemy", true);
	enemy2.addComponent<ColliderComponent>("enemy");
	enemy2.addGroup(groupEnemies);

	enemy3.addComponent<TransformComponent>(300, 200, 32, 32, 4);
	enemy3.addComponent<SpriteComponent>("enemy", true);
	enemy3.addComponent<ColliderComponent>("enemy");
	enemy3.addGroup(groupEnemies);

	enemy4.addComponent<TransformComponent>(1000, 550, 32, 32, 4);
	enemy4.addComponent<SpriteComponent>("enemy", true);
	enemy4.addComponent<ColliderComponent>("enemy");
	enemy4.addGroup(groupEnemies);

	enemy5.addComponent<TransformComponent>(1200, 900, 32, 32, 4);
	enemy5.addComponent<SpriteComponent>("enemy", true);
	enemy5.addComponent<ColliderComponent>("enemy");
	enemy5.addGroup(groupEnemies);

	enemy6.addComponent<TransformComponent>(100, 100, 32, 32, 4);
	enemy6.addComponent<SpriteComponent>("enemy", true);
	enemy6.addComponent<ColliderComponent>("enemy");
	enemy6.addGroup(groupEnemies);

	enemy7.addComponent<TransformComponent>(100, 700, 32, 32, 4);
	enemy7.addComponent<SpriteComponent>("enemy", true);
	enemy7.addComponent<ColliderComponent>("enemy");
	enemy7.addGroup(groupEnemies);

	enemy8.addComponent<TransformComponent>(200, 300, 32, 32, 4);
	enemy8.addComponent<SpriteComponent>("enemy", true);
	enemy8.addComponent<ColliderComponent>("enemy");
	enemy8.addGroup(groupEnemies);

	enemy9.addComponent<TransformComponent>(1200, 600, 32, 32, 4);
	enemy9.addComponent<SpriteComponent>("enemy", true);
	enemy9.addComponent<ColliderComponent>("enemy");
	enemy9.addGroup(groupEnemies);

	enemy10.addComponent<TransformComponent>(400, 300, 32, 32, 4);
	enemy10.addComponent<SpriteComponent>("enemy", true);
	enemy10.addComponent<ColliderComponent>("enemy");
	enemy10.addGroup(groupEnemies);

	enemy11.addComponent<TransformComponent>(300, 350, 32, 32, 4);
	enemy11.addComponent<SpriteComponent>("enemy", true);
	enemy11.addComponent<ColliderComponent>("enemy");
	enemy11.addGroup(groupEnemies);

	enemy12.addComponent<TransformComponent>(10, 1200, 32, 32, 4);
	enemy12.addComponent<SpriteComponent>("enemy", true);
	enemy12.addComponent<ColliderComponent>("enemy");
	enemy12.addGroup(groupEnemies);

	enemy13.addComponent<TransformComponent>(400, 100, 32, 32, 4);
	enemy13.addComponent<SpriteComponent>("enemy", true);
	enemy13.addComponent<ColliderComponent>("enemy");
	enemy13.addGroup(groupEnemies);

	enemy14.addComponent<TransformComponent>(1000, 1000, 32, 32, 4);
	enemy14.addComponent<SpriteComponent>("enemy", true);
	enemy14.addComponent<ColliderComponent>("enemy");
	enemy14.addGroup(groupEnemies);

	enemy15.addComponent<TransformComponent>(100, 100, 32, 32, 4);
	enemy15.addComponent<SpriteComponent>("enemy", true);
	enemy15.addComponent<ColliderComponent>("enemy");
	enemy15.addGroup(groupEnemies);

	//set up where the score and health text will be
	pScore.addComponent<UILabel>(10, 10, "Score", "arcade", white);
	pHealth.addComponent<UILabel>(10, 50, "Health", "arcade", red);
	eScore.addComponent<UILabel>(275, 250, "End Score", "arcade", white);
	escGame.addComponent<UILabel>(150, 350, "Esc Game", "arcade", white);
}

// Returns the refrences to the vector pointer to each group. i.e. 'tiles' references to the manager's vector of every tile in the map.
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& enemies(manager.getGroup(Game::groupEnemies));
// GAME:: IDENTIFIER NECESSARY BECAUSE OUTSIDE OF { GAME SCOPE }.

void Game::handleEvents() // Literally just handles the event of SDL_QUIT.
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {// Updates all entities and interaction among them.
    
    // NOTE : this should all be moved into CharacteristicComponent.h in the update function.
    
	int tempScore = player.getComponent<CharacteristicComponent>().getScore();

	//basically ends the game
	if (player.getComponent<CharacteristicComponent>().getHealth() <= 0) {
        for (auto& e : enemies) {
			e->destroy();
        }
        for (auto& c : colliders){
			c->destroy();
        }
		
        map = new Map("end", 3, 32); // Goes to new map
		map->LoadMap("assets/end.txt", 25, 20);
        delete map;
        
		std::stringstream end;
		end << "Ending  Score :    " << tempScore;
		eScore.getComponent<UILabel>().SetLabelText(end.str(), "arcade");

		std::string esc;
		esc = "Please  press  'esc'  to  leave  the  game";
		escGame.getComponent<UILabel>().SetLabelText(esc, "arcade");
	}
	else {
		std::stringstream sc;
		sc << "Score : " << tempScore;
		pScore.getComponent<UILabel>().SetLabelText(sc.str(), "arcade");
		player.getComponent<CharacteristicComponent>().addScore(.06);

		std::stringstream hp;
		hp << "Health : " << player.getComponent<CharacteristicComponent>().getHealth();
		pHealth.getComponent<UILabel>().SetLabelText(hp.str(), "arcade");
	}
    
    SDL_Rect playerOldCol = player.getComponent <ColliderComponent>().collider;
    Vector2D playerOldPos = player.getComponent<TransformComponent>().position;
    
    manager.refresh(); // Removes any entities that are not active (by checking if isActive == true).
    manager.update(); // Updates each component of every entity within the manager's pointer containers for each group.
    
    SDL_Rect playerNewCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerNewPos = player.getComponent<TransformComponent>().position;

    for (auto& c : colliders) { // EDIT THIS: make it only check colliders within the screen view.
        
        if (true) { // Precisely here.
            
            SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
            if ((playerNewPos.x <= cCol.x + cCol.w + 3) && !(playerOldPos.x <= cCol.x + cCol.w) && // Left-collision
                (playerNewPos.y >= cCol.y) && (playerNewPos.y <= cCol.y + cCol.h)) {
                player.getComponent<TransformComponent>().position.x = playerOldPos.x;
            }
            if ((playerNewPos.y <= cCol.y + cCol.h + 3) && !(playerOldPos.y <= cCol.y + cCol.h) && // Top-collision
                (playerNewPos.x >= cCol.x) && (playerNewPos.x <= cCol.x + cCol.w)) {
                player.getComponent<TransformComponent>().position.y = playerOldPos.y;
            }
            if ((playerNewPos.x + playerNewCol.w + 3 >= cCol.x) && !(playerOldPos.x + playerOldCol.w >= cCol.x) && // Right-collision
                (playerNewPos.y >= cCol.y) && (playerNewPos.y <= cCol.y + cCol.h)) {
                player.getComponent<TransformComponent>().position.x = playerOldPos.x;
            }
            if ((playerNewPos.y + playerNewCol.h + 3 >= cCol.y) && !(playerOldPos.y + playerOldCol.h >= cCol.y) && //Bottom-collision
                (playerNewPos.x >= cCol.x) && (playerNewPos.x <= cCol.x + cCol.w)) {
                player.getComponent<TransformComponent>().position.y = playerOldPos.y;
            }
        }
    }

    //makes enemies "explode" when they hit the player and doesn't let them create one super zombie thing. Makes them spread apart
    for (auto& e : enemies) {
        if (Collision::AABB(player.getComponent<ColliderComponent>().collider, e->getComponent<ColliderComponent>().collider)) {
            player.getComponent<TransformComponent>().velocity = player.getComponent<TransformComponent>().velocity * -1;
            player.getComponent<KeyboardController>().stun = 3;
            e->destroy();
            player.getComponent<CharacteristicComponent>().addHealth(-30);
        }
    for (auto& contact : enemies) {
        if (Collision::AABB(e->getComponent<ColliderComponent>().collider, contact->getComponent<ColliderComponent>().collider)) {
            e->getComponent<TransformComponent>().position.x += 300;
            contact->getComponent<TransformComponent>().position.x -= 300;
            e->getComponent<TransformComponent>().position.y += 300;
            contact->getComponent<TransformComponent>().position.y -= 300;
        }
    }
        
        // AI of how the enemies move to the player
        // Note: should be turned into an PathfindingComponent in the future.
        if (player.getComponent<TransformComponent>().position.x > e->getComponent<TransformComponent>().position.x) {
            e->getComponent<TransformComponent>().position.x += 2;
            e->getComponent<SpriteComponent>().play("Walk");
            e->getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_NONE;
        }
        if (player.getComponent<TransformComponent>().position.x < e->getComponent<TransformComponent>().position.x) {
            e->getComponent<TransformComponent>().position.x -= 2;
            e->getComponent<SpriteComponent>().play("Walk");
            e->getComponent<SpriteComponent>().spriteFlip = SDL_FLIP_HORIZONTAL;
        }
        if (player.getComponent<TransformComponent>().position.y > e->getComponent<TransformComponent>().position.y) {
            e->getComponent<TransformComponent>().position.y += 2;
            e->getComponent<SpriteComponent>().play("Walk");
        }
        if (player.getComponent<TransformComponent>().position.y < e->getComponent<TransformComponent>().position.y) {
            e->getComponent<TransformComponent>().position.y -= 2;
            e->getComponent<SpriteComponent>().play("Walk");
        }
    }
    
    if (player.getComponent<CharacteristicComponent>().getHealth() > 0) {
        camera.x = player.getComponent<TransformComponent>().position.x - 400;
        camera.y = player.getComponent<TransformComponent>().position.y - 320;

        if (camera.x < 0) {
            camera.x = 0;
        }
        if (camera.y < 0) {
            camera.y = 0;
        }
        if (camera.x > camera.w) {
            camera.x = camera.w;
        }
        if (camera.y > camera.h) {
            camera.y = camera.h;
        }
    }
}

// Draws everything to our renderer.
void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& t : tiles) {
		t->draw();
	}
	if (player.getComponent<CharacteristicComponent>().getHealth() > 0) { // Only draw player if still alive. This is a temporary work-around to the fact that the player is our only source of keyboard input as of now.
		for (auto& p : players) {
			p->draw();
		}
	}
	for (auto& e : enemies) {
		e->draw();
	}
	if (player.getComponent<CharacteristicComponent>().getHealth() > 0) {
		pScore.draw();
		pHealth.draw();
	}
	else {
		eScore.draw();
		escGame.draw();
	}
	SDL_RenderPresent(renderer);
}

//deletes everything
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


