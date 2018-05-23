#pragma once

#include <string>
#include "Components.h"

class CharacteristicComponent : public Component {
public:
    CharacteristicComponent(int initScore = 0, int maxHP = 100, int HP = 100) : score(initScore), healthMax(maxHP), health(HP) { // Our current setup for stats...
        
    }
    ~CharacteristicComponent();
    
    void destroy() {
        
    }
    
    void addScore(double amt) {
        score = score + amt;
    }
    
    void addHealth(int amt) {
        health = health + amt;
        if (health > healthMax) {
            health = healthMax;
        }
        if (health < 0) {
            health = 0;
        }
    }
    
    double getScore() {
        return score;
    }
    int getHealthMax() {
        return healthMax;
    }
    int getHealth() {
        return health;
    }
    int getManaMax() {
        return manaMax;
    }
    int getMana() {
        return mana;
    }
    int getLevel() {
        return level;
    }
    int getExperienceCap() {
        return experienceCap;
    }
    int getExperience() {
        return this->experience;
    }
    int getExperienceToLevel() {
        return this->experienceCap - this->experience;
    }
    int getWeightMax() {
        return this->weightMax;
    }
    int getWeight() {
        return this->weight;
    }
    int getHungerMax() {
        return this->hungerMax;
    }
    int getHunger() {
        return this->hunger;
    }
    int getSpeed() {
        return this->speed;
    }
//private:
    double score;
    int healthMax;
    int health;
    int manaMax;
    int mana;
    int level;
    int experienceCap;
    int experience;
    int weightMax;
    int weight;
    int hungerMax;
    int hunger;
    int speed;
    
    std::string name;
    std::string nickname;
    
};
