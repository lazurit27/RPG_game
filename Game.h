#pragma once
#include <random>
#include <cstdlib>
#include "Character.h"
#include "Inventory.h"
#include "MyArray.h"
#include <conio.h>
#include "FileSave.h"



class Game
{
private:
    bool gameOver = false;
    std::shared_ptr<Player> Main_character;
    std::shared_ptr<Enemy> Monster;
    std::shared_ptr<Enemy> Boss;
    MyArray<item*> inventory;
    size_t currentLocation;
    int randint(int max, int min = 1);

    void SaveAllParametrs(std::string username);
    void LoadAllParametrs(std::string file);
    void newParametrs(std::string name);
    
    void next();
    void waitForKey();
    
    void showInventory(int type);
    void ItemChoise(int type);
    void addItem(item* newItem);
    item* getRandomItem(int type = 1);
    
    void LocNormal();
    void LocEnemy();
    void LocChest();
    void LocQuest();
    void LocShop();
    void LocBoss();

    
public:

    Game();
    Game(std::string name);
    void start();

    
    
    
    
    
    
};
