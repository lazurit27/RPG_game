#include "FileSave.h"

bool FileSave::CheckFileName(const std::string filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}

void FileSave::SaveInventory(const MyArray<item*>& inventory, const std::string& filename)
    {
        std::ofstream out(filename, std::ios::binary);
        if (!out)
        {
            throw std::ios_base::failure("File cannot be open!");
            return;
        }

        int inventory_size = inventory.getSize();
        out.write(reinterpret_cast<char*>(&inventory_size), sizeof(inventory_size));

        if (!out)
        {
            throw std::ios_base::failure("Error when write inventory size to file!");
            return;
        }

        for (size_t i = 0; i < inventory_size; i++)
        {
            const item* Item = inventory[i];


            int name_size = Item->get_Name().size();
            out.write(reinterpret_cast<char*>(&name_size), sizeof(name_size));
            out.write(Item->get_Name().c_str(), name_size);

            int unit = Item->get_unit();
            out.write(reinterpret_cast<char*>(&unit), sizeof(unit));
        }

        out.close();
    }

void FileSave::Saveloccount(const size_t _loccount, const std::string& filename)
{
    std::ofstream out(filename, std::ios::binary);
    if (!out)
    {
        throw std::ios_base::failure("Error when write inventory size to file!");
        return;
    }

    size_t loccount = _loccount;
    out.write(reinterpret_cast<char*>(&loccount), sizeof(loccount));

    out.close();
}

void  FileSave::SaveMainCharacter(const Player*& player, const std::string& filename)
    {
        std::ofstream out(filename, std::ios::binary);
        if (!out)
        {
            throw std::ios_base::failure("Error when write inventory size to file!");
            return;
        }

        int player_name_size = player->get_Name().size();
        out.write(reinterpret_cast<char*>(&player_name_size), sizeof(player_name_size));
        out.write(player->get_Name().c_str(), player_name_size);

        size_t HP_CUP = player->get_HP_CUP();
        out.write(reinterpret_cast<char*>(&HP_CUP), sizeof(HP_CUP));

        int HP = player->get_HP();
        out.write(reinterpret_cast<char*>(&HP), sizeof(HP));

        size_t Damage = player->get_Damage();
        out.write(reinterpret_cast<char*>(&Damage), sizeof(Damage));

        size_t Armor = player->getArmor();
        out.write(reinterpret_cast<char*>(&Armor), sizeof(Armor));

        size_t LVL = player->getLVL();
        out.write(reinterpret_cast<char*>(&LVL), sizeof(LVL));

        int Coin = player->getCoins();
        out.write(reinterpret_cast<char*>(&Coin), sizeof(Coin));

        out.close();
        
    }

void FileSave::SaveEnemy(const MyArray<std::shared_ptr<Enemy>>& inventory, const std::string& filename)
    {
        std::ofstream out(filename, std::ios::binary);
        if (!out)
        {
            throw std::ios_base::failure("File cannot be open!");
            return;
        }

        int inventory_size = inventory.getSize();
        out.write(reinterpret_cast<char*>(&inventory_size), sizeof(inventory_size));

        if (!out)
        {
            throw std::ios_base::failure("Error when write inventory size to file!");
            return;
        }

        for (size_t i = 0; i < inventory_size; i++)
        {
            const Enemy* enemy =  inventory[i].get();


            int name_size = enemy->get_Name().size();
            out.write(reinterpret_cast<char*>(&name_size), sizeof(name_size));
            out.write(enemy->get_Name().c_str(), name_size);

            size_t HP_CUP = enemy->get_HP_CUP();
            out.write(reinterpret_cast<char*>(&HP_CUP), sizeof(HP_CUP));
            
            size_t Damage = enemy->get_Damage();
            out.write(reinterpret_cast<char*>(&Damage), sizeof(Damage));
        }

        out.close();
    }

MyArray<item*> FileSave::LoadInventory(const std::string filename)
    {
        MyArray<item*> inventory;

        std::ifstream in(filename, std::ios::binary);
        if (!in)
        {
            throw std::ios_base::failure("File cannot be open!");
            return {};
        }

        int inventory_size = 0;
        in.read(reinterpret_cast<char*>(&inventory_size), sizeof(inventory_size));
        if (!in)
        {
            throw std::ios_base::failure("File cannot be open!");
            return {};
        }

        if (inventory_size < 0)
        {
            throw std::runtime_error("Inventory size cannot be less than zero");
            return {};
        }

        for (size_t i = 0; i < inventory_size; i++)
        {
            int name_size;
            in.read(reinterpret_cast<char*>(&name_size), sizeof(name_size));

            std::string name(name_size, '\0');
            in.read(&name[0], name_size);
            

            int unit;
            in.read(reinterpret_cast<char*>(&unit), sizeof(unit));

            item* Item = nullptr;
            if (name == "Mystical_Fruit")
            {
                Item = new Mystical_Fruit(name,unit);

            }
            else if (name == "blue_milk")
            {
                Item = new blue_milk(name, unit);

            }
            else if (name == "Nanomachines")
            {
                Item = new Nanomachines(name, unit);
            }
            else if (name == "Flawless_Hat")
            {
                Item = new Flawless_Hat(name, unit);
            }
            else if (name == "ak47")
            {
                Item = new ak47(name, unit);
            }

            if (Item != nullptr)
            {
                inventory.pushBack(Item);
            }
        }
        in.close();
        return inventory;
    }

std::shared_ptr<Player> FileSave::LoadPlayer(const std::string filename)
    {
        std::ifstream in(filename, std::ios::binary);
        if (!in)
        {
            throw std::ios_base::failure("File cannot be open!");
            return {};
        }

        int player_name_size;
        in.read(reinterpret_cast<char*>(&player_name_size), sizeof(player_name_size));

        std::string name(player_name_size, '\0');
        in.read(&name[0], player_name_size);
            

        size_t HP_CUP;
        in.read(reinterpret_cast<char*>(&HP_CUP), sizeof(HP_CUP));
        int HP;
        in.read(reinterpret_cast<char*>(&HP), sizeof(HP));
        size_t Damage;
        in.read(reinterpret_cast<char*>(&Damage), sizeof(Damage));
        size_t Armor;
        in.read(reinterpret_cast<char*>(&Armor), sizeof(Armor));
        size_t LVL;
        in.read(reinterpret_cast<char*>(&LVL), sizeof(LVL));
        int Coin;
        in.read(reinterpret_cast<char*>(&Coin), sizeof(Coin));

        std::shared_ptr<Player> Main_Character = std::make_shared<Player>(name,HP_CUP,HP,Damage,LVL,Armor,Coin);
        
        in.close();
        return Main_Character;
    }

MyArray<std::shared_ptr<Enemy>> FileSave::LoadEnemys(const std::string filename)
    {
        MyArray<std::shared_ptr<Enemy>> Enemys;

        std::ifstream in(filename, std::ios::binary);
        if (!in)
        {
            throw std::ios_base::failure("File cannot be open!");
            return {};
        }

        int Enemy_size = 0;
        in.read(reinterpret_cast<char*>(&Enemy_size), sizeof(Enemy_size));
        if (!in)
        {
            throw std::ios_base::failure("File cannot be open!");
            return {};
        }

        if (Enemy_size < 0)
        {
            throw std::runtime_error("enemy size cannot be less than zero");
            return {};
        }

        for (size_t i = 0; i < Enemy_size; i++)
        {
            int name_size;
            in.read(reinterpret_cast<char*>(&name_size), sizeof(name_size));

            std::string name(name_size, '\0');
            in.read(&name[0], name_size);
            

            size_t HP_CUP;
            in.read(reinterpret_cast<char*>(&HP_CUP), sizeof(HP_CUP));
            size_t Damage;
            in.read(reinterpret_cast<char*>(&Damage), sizeof(Damage));
            
            std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(name,HP_CUP,Damage);

            if (enemy != nullptr)
            {
                Enemys.pushBack(std::move(enemy));
            }
        }
        in.close();
        return Enemys;
    }

int FileSave::Loadloccount(const std::string filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in)
    {
        throw std::ios_base::failure("File cannot be open!");
        return {};
    }

    int loccount = 0;
    in.read(reinterpret_cast<char*>(&loccount), sizeof(loccount));

    if (loccount < 0)
    {
        throw std::runtime_error("Location coubnt cannot be less than zero");
        return {};
    }

    in.close();
    return loccount;
    
}

void FileSave::deleteFile(const std::string username)
{
    std::string bin = ".bin";
    std::string filename = username + bin;
        if (remove(filename.c_str()) != 0)
        {
            throw std::ios_base::failure("File cannot be deleted!");
        }
        if (remove(("I" + filename).c_str()) != 0)
        {
            throw std::ios_base::failure("File cannot be deleted!");
        }
        if (remove(("L" + filename).c_str()) != 0)
        {
            throw std::ios_base::failure("File cannot be deleted!");
        }
        if (remove(("E" + filename).c_str()) != 0)
        {
            throw std::ios_base::failure("File cannot be deleted!");
        }
        
}