#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component {
public:
    bool up = 0;
    bool down = 0;
    bool left = 0;
    bool right = 0;
    int stun = 0;
    
	TransformComponent *transform;
	SpriteComponent* sprite;
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
        if (stun > 0) {
            stun -= 0.1;
        }
        if (stun < 0) {
            stun = 0;
        }
        if (stun > 3) {
            stun = 3;
        }
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
                case SDLK_a:
                    left = true;
                    sprite->play("Walk");
                    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                    break;
                case SDLK_d:
                    right = true;
                    sprite->play("Walk");
                    break;
                case SDLK_w:
                    up = true;
                    sprite->play("Walk");
                    break;
                case SDLK_s:
                    down = true;
                    sprite->play("Walk");
                    break;
                default:
                    break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
                case SDLK_a:
                    left = false;
                    sprite->play("Idle");
                    sprite->spriteFlip = SDL_FLIP_NONE;
                    break;
                case SDLK_d:
                    right = false;
                    sprite->play("Idle");
                    break;
                case SDLK_w:
                    up = false;
                    sprite->play("Idle");
                    break;
                case SDLK_s:
                    down = false;
                    sprite->play("Idle");
                    break;
                case SDLK_ESCAPE:
                    Game::isRunning = false;
                default:
                    break;
			}
		}
        
        if (left == true) {
            if (transform->velocity.x >= 0) {
                transform->velocity.x -= 1 - stun;
            }
            if (transform->velocity.x < 0 && transform->velocity.x > -1) {
                transform->velocity.x = -1 - stun;
            }
        }
        else if (right == true) {
            if (transform->velocity.x <= 0) {
                transform->velocity.x += 1 - stun;
            }
            if (transform->velocity.x > 0 && transform->velocity.x < 1) {
                transform->velocity.x = 1 - stun;
            }
        }
        else {
            transform->velocity.x = 0;
        }
        if (up == true) {
            if (transform->velocity.y >= 0) {
                transform->velocity.y -= 1 - stun;
            }
            if (transform->velocity.y < 0 && transform->velocity.y > -1) {
                transform->velocity.y = -1 - stun;
            }
        }
        else if (down == true) {
            if (transform->velocity.y <= 0) {
                transform->velocity.y += 1 - stun;
            }
            if (transform->velocity.y > 0 && transform->velocity.y < 1) {
                transform->velocity.y = +1 - stun;
            }
        }
        else {
            transform->velocity.y = 0;
        }
	}
};
