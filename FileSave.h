#pragma once
#include <iostream>
#include "MyArray.h"
#include "Inventory.h"
#include "Character.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <cstdio>

class FileSave
{
public:
    static void deleteFile(const std::string username);
    static bool CheckFileName(const std::string filename);
    static void SaveInventory(const MyArray<item*>& inventory, const std::string& filename);
    static void Saveloccount(const size_t loccount, const std::string& filename);
    static void  SaveMainCharacter(const Player*& player, const std::string& filename);
    static void SaveEnemy(const MyArray<std::shared_ptr<Enemy>>& inventory, const std::string& filename);
    static MyArray<item*> LoadInventory(const std::string filename);
    static std::shared_ptr<Player> LoadPlayer(const std::string filename);
    static MyArray<std::shared_ptr<Enemy>> LoadEnemys(const std::string filename);
    static int Loadloccount(const std::string filename);
    

    

    
};
