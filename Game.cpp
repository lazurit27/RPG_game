#include "Game.h"
int Game::randint(int max, int min)
{
    return min + rand() % (max - min + 1);
}

void Game::SaveAllParametrs(std::string username)
{
    std::string bin = ".bin";
    std::string filename = username + bin;

    MyArray<std::shared_ptr<Enemy>> enemies;
    enemies.pushBack(Monster);
    enemies.pushBack(Boss);

    const Player* main_c = Main_character.get();
    FileSave::SaveMainCharacter(main_c ,  filename);
    FileSave::SaveInventory(inventory, "I" + filename);
    FileSave::SaveEnemy(enemies, "E" + filename);
    FileSave::Saveloccount(currentLocation, "L"+ filename);
}

void Game::LoadAllParametrs(std::string file)
{
    Main_character = FileSave::LoadPlayer(file);
    inventory = FileSave::LoadInventory("I" + file);
    MyArray<std::shared_ptr<Enemy>> enemies = FileSave::LoadEnemys( "E" +file);
    currentLocation = FileSave::Loadloccount("L"+ file);
    Monster = std::move(enemies[0]);
    Boss = std::move(enemies[1]);
}

void Game::newParametrs(std::string name)
{
    Main_character = std::make_shared<Player>(name);
    currentLocation = 0;
    Monster = std::make_shared<Enemy>("Jaffa.jr", 85, 10);
    Boss = std::make_shared<Enemy>("JAFFA", 200, 20);
}

void Game::waitForKey()
{
    std::cout << "\n\nPress any key";
    _getch();
}

void Game::start()
{
    std::string username;
    std::string bin = ".bin";
    bool done = false;
    while (true)
    {
        bool isRunning = true;
        std::cout << "===GAME MENU===\nHello! pls enter ur username: ";
        std::cin >> username;

        if (FileSave::CheckFileName(username + bin))
        {
            while (isRunning)
            {
                std::cout << "\n This player already exists on this device.\nIts you? \n1.yes \n2.no\n";
                char key = _getch();
                switch (key)
                {
                case '1':
                    LoadAllParametrs(username + bin);
                    isRunning =false;
                    done = true;
                    break;
                case '2':
                    isRunning =false;
                    break;
                default:
                    system("cls");
                    std::cout << "WRONG KEY!\n";
                    
                }
            }
            
        }
        else
        {
            newParametrs(username);
            done = true;
        }
        if (done)
        {
            break;
        }
    }
    
    system("cls");
    std::cout << "Wellcome!, " << Main_character->get_Name() << "!\n" << *Main_character;

    waitForKey();

    while (!gameOver)
        next();

    std::cout << "Game Over.\n";
}


void Game::next()
{
    currentLocation++;
    system("cls");

    int type;
    if (currentLocation % 20 == 0)
       type = 10;
    else
        type = randint(9);

    std::cout << "\n=== Location " << currentLocation << " ===\n";
    Main_character->heal(10);
    switch (type)
    {
    case 1:
        LocNormal();
        break;
    case 2:
        LocEnemy();
        break;
    case 3:
        LocChest();
        break;
    case 4:
        LocQuest();
        break;
    case 5:
        LocShop();
        break;
    case 6:
        LocNormal();
        break;
    case 7:
        LocEnemy();
        break;
    case 8:
        LocChest();
        break;
    case 9:
        LocNormal();
        break;
    case 10:
        LocBoss();
        break;
    }
}

void Game::ItemChoise(int type)
{
    int index;
    
    while (true)
    {
        std::cout << "Enter item number(if you want exit enter 0): ";
        std::cin >> index;
        
        if (index == 0)
        {
            break;
        }
        else if (index > inventory.getSize())
        {
            std::cout << "Invalid item number!\n";
            continue;
        }

        if (inventory[index - 1]->get_Name() != "ak47" && inventory[index - 1]->get_Name() != "Gold_Coin")
        {
            inventory[index - 1]->use(Main_character.get());
            if(inventory[index - 1]->get_unit() == 0)
            {
                delete inventory[index - 1];
                inventory.erase(index - 1);
            }
            return;
        }
        else
        {
            if (type == 3)
            {
                inventory[index - 1]->use(Monster.get());
                if(inventory[index - 1]->get_unit() == 0)
                {
                    delete inventory[index - 1];
                    inventory.erase(index - 1);
                }
                return;
            }
            else if (type == 4)
            {
                inventory[index - 1]->use(Boss.get());
                if(inventory[index - 1]->get_unit() == 0)
                {
                    delete inventory[index - 1];
                    inventory.erase(index - 1);
                }
                return;
            }
            else
            {
                std::cout << "You cannot use this item without enemy!\n";
            }
            
        }
        
        
    }
    
}

void Game::addItem(item* newItem)
{
    if (inventory.getSize() <= 9)
    {
        for (int i = 0; i < inventory.getSize(); i++)
        {
            if (inventory[i]->get_Name() == newItem->get_Name())
            {
                if (inventory[i]->add_unit(newItem->get_unit()))
                {
                    std::cout << "Add unit! [" << inventory[i]->get_Name() << "]\n";
                    delete newItem;
                    return;
                }
            }
        }
    }
    else
    {
        std::cout << "You got full inventory!!\n";
        delete newItem;
        return;
    }

    inventory.pushBack(newItem);
    std::cout << "Item [" << newItem->get_Name() << "] Add in inventory.\n";
}

void Game::showInventory(int type)
{

    if (inventory.getSize() == 0)
    {
        system("cls");
        std::cout << "Enventory empty.\n";
        return;
    }
    else
    {
        std::cout << "--- Your Inventory ---\n";
        for (int i = 0; i < inventory.getSize(); ++i)
        {
            std::cout << i + 1 << ") " << inventory[i]->get_Name()<< " | " << inventory[i]->get_unit() << "/" << inventory[i]->get_unit_CUP() << "\n";
        }
    }

    std::cout << "\n1. Use item\n2. Return\n> ";
    bool isRunning = true;
    while (isRunning)
    {
        char key = _getch();
        switch (key)
        {
            case '1':
            ItemChoise(type);
            isRunning =false;
            break;
            case '2':
            isRunning = false;
            break;
            default:
            std::cout << "WRONG KEY!\n";
            
            break;
            
        }
    }
    waitForKey();
}

item* Game::getRandomItem(int type)
{
    int roll = randint(5);
    item* newItem = nullptr;

    if (type == 1)
    {
        switch (roll)
        {
        case 1:
            newItem = new Mystical_Fruit("Mystical_Fruit");
            break;
        case 2:
            newItem = new blue_milk("blue_milk");
            break;
        case 3:
            newItem = new Nanomachines("Nanomachines");
            break;
        case 4:
            newItem = new Flawless_Hat("Flawless_Hat");
            break;
        case 5:
            break;
        }
        return newItem;
    }
    else if (type == 2)
    {
            switch (roll)
            {
            case 1:
                newItem = new Mystical_Fruit("Mystical_Fruit");
                break;
            case 2:
                newItem = new blue_milk("blue_milk");
                break;
            case 3:
                newItem = new Nanomachines("Nanomachines");
                break;
            case 4:
                newItem = new Flawless_Hat("Flawless_Hat");
                break;
            case 5:
                newItem = new ak47("ak47");
                break;
            }
            return newItem;
    }
}

void Game::LocNormal()
{
    if (Main_character->get_HP() < Main_character->get_HP_CUP())
    {
        std::cout << "You got heal!\n";
        Main_character->heal(15);
    }
    bool isRunning = true;
    while (isRunning)
    {
        std::cout << "you are walking through a quiet area.\n";
        std::cout << *Main_character;
    
        
        std::cout << "\n1. next\n2. Open Inventory\n3. Exit\n> ";
        char key = _getch();
    
        switch (key)
        {
        case '1':
            isRunning = false;
            break;
        case '2':
            system("cls");
            showInventory(1);
            break;
        case '3':
            gameOver = true;
            isRunning = false;
            SaveAllParametrs(Main_character->get_Name());
            break;
        default:
            system("cls");
            std::cout << "WRONG KEY!\n";
            break;
        }
    }
}

void Game::LocChest()
{
    std::cout << "You found chest!\n";
    item* newItem = getRandomItem();
    
    bool isRunning = true;
    while (isRunning)
    {
        if (newItem != nullptr)
        {
            std::cout << "In chest: " << newItem->get_Name() << "\n";
            std::cout << "\n1. Take\n2. Next\n> ";
            char key = _getch();

            switch (key)
            {
            case '1':
                addItem(newItem);
                isRunning = false;
                break;
            case '2':
                delete newItem;
                isRunning = false;
                break;
            default:
                system("cls");
                std::cout << "WRONG KEY!\n";
            }
        }
        else
        {
            std::cout << "In chest: Nothing?! srsly?";
            delete newItem;
            isRunning = false;
            waitForKey();
            break;
        }
    }
}

void Game::LocEnemy()
{

    std::cout << "YOU SEE ENEMY!\n";

    while (Monster->get_HP() > 0 && Main_character->get_HP() > 0)
    {
        if (Monster->get_HP() <= 0)
        {
            break;
        }
        bool isRunning = true;
        while (isRunning )
        {
        std::cout << *Main_character << *Monster << "\n";
        std::cout << "\n1. Attack\n2.parry\n3. Inventory\n> ";
            char key = _getch();
            int chance = randint(Main_character->get_HP_CUP());
            switch (key)
            {
            case '1':
                Main_character->attack(Monster.get());
                if (Monster->get_HP() > 0)
                {
                    Monster->attack(Main_character.get());
                }
                system("cls");
                isRunning = false;
                break;
            case '2':
                if (chance > Main_character->get_HP())
                {
                    Main_character->heal(15);
                }
                else
                {
                    Monster->attack(Main_character.get());
                }
                system("cls");
                isRunning = false;
                break;
            case '3':
                showInventory(3);
                break;
            default:
                system("cls");
                std::cout << "WRONG KEY!\n";
            }
        }
        

        if (Main_character->get_HP() <= 0)
        {
            std::cout << "You Died!\n";
            if (FileSave::CheckFileName(Main_character->get_Name() + ".bin"))
            {
                FileSave::deleteFile(Main_character->get_Name());
            }
            gameOver = true;
            return;
        }
    }
    int unit = randint(30);
    
    Main_character->changeCoins(unit);
    std::cout << "ENEMY DIED!\n";
    Monster->betterenemy();
    std::cout << "YOU GOT LVL UP!!" << Main_character->getLVL();
    Main_character->AddLVL(randint(3,1));
    std::cout << "->" << Main_character->getLVL() << "\n";
    std::cout << "and u got " << unit << " Gold Coins! ";

    waitForKey();
    system("cls");
}

void Game::LocBoss()
{
    std::cout << "You see HUGRY JAFFA!!\n";
    while (Boss->get_HP() > 0 && Main_character->get_HP() > 0)
    {
        if (Boss->get_HP() <= 0)
        {
            break;
        }
        bool isRunning = true;
        while (isRunning )
            while (isRunning )
            {
                std::cout << *Main_character << *Boss << "\n";
                std::cout << "\n\n1. Attack\n2.Parry\n3. Inventory\n> ";
                int chance = randint(Main_character->get_HP_CUP());
                char key = _getch();

                switch (key)
                {
                case '1':
                    Main_character->attack(Boss.get());
                    if (Boss->get_HP() > 0)
                    {
                        Boss->attack(Main_character.get());
                    }
                    system("cls");
                    isRunning = false;
                    break;
                case '2':
                    if (chance > Main_character->get_HP())
                    {
                        Main_character->heal(15);
                    }
                    else
                    {
                        Monster->attack(Main_character.get());
                    }
                    system("cls");
                    isRunning = false;
                    break;
                case '3':
                    showInventory(3);
                    break;
                default:
                    system("cls");
                    std::cout << "WRONG KEY!\n";
                }
            }
    }
        
    if (Main_character->get_HP() <= 0)
    {
        std::cout << "Jaffa eat you...\n";
        if (FileSave::CheckFileName(Main_character->get_Name() + ".bin"))
        {
            FileSave::deleteFile(Main_character->get_Name());
        }
        gameOver = true;
        return;
            
    }
    

    int unit = randint(70, 30);
    Boss->betterenemy(4);
    Main_character->changeCoins(unit);
    std::cout << "JAFFA rolled away, but u can see him again...\n";
    std::cout << "YOU GOT LVL UP!!" << Main_character->getLVL();
    Main_character->AddLVL(randint(8,4));
    std::cout << "->" << Main_character->getLVL() << "\n";
    std::cout << "and u got " << unit << " Gold coins!";

    waitForKey();
}

void Game::LocQuest()
{
    bool isRunning = true;
    std::cout << "You see Mysterius Human!!\n";
    std::cout << "Hello traveler, if you answer my example you will receive a reward, if you don’t answer you will suffer\nYOU ARE READY??";
    while (isRunning)
    {
        std::cout << "\n1. Yes\n2. no";
        char key = _getch();
        int num1 = randint(100);
        int num2 = randint(100);
        int oper = randint(3);
        switch (key)
        {
        case '1':
            std::cout << "\nI SEE YOU ARE READY!!\n";
            int answer;
            switch (oper)
            {
            case 1:
                std::cout << "answer for me, how many \n" << num1 << " + " << num2 << "\n";
                std::cin >> answer;
                if (answer == num1 + num2)
                {
                    std::cout << "You are right! your reward!\n";
                    int chance = randint(3);
                    if (chance == 1)
                    {
                        item* newItem = getRandomItem();
                        addItem(newItem);
                        isRunning = false;
                        break;
                    }
                    else if (chance == 2)
                    {
                        std::cout << "YOU GOT LVL UP!!" << Main_character->getLVL();
                        Main_character->AddLVL(randint(8,4));
                        std::cout << "->" << Main_character->getLVL() << "\n";
                        isRunning = false;
                        break;
                    }
                    else if (chance == 3)
                    {
                        int unit = randint(100, 1);
                        Main_character->changeCoins(unit);
                        std::cout << "U got " << unit << " Gold coins!";
                    }
                    else
                    {
                        std::cout << "error";
                        break;
                    }
                }
                else
                {
                    std::cout << "WRONG ANSWER! you will pay!\n||You take damage||";
                    Main_character->Take_away_HP(randint(Main_character->get_HP()));
                    isRunning = false;
                    break;
                }
                

            case 2:
                std::cout << "answer for me, how many \n" << num1 << " - " << num2 << "\n";
                std::cin >> answer;
                if (answer == num1 - num2)
                {
                    std::cout << "You are right! your reward!\n";
                    int chance = randint(3);
                    if (chance == 1)
                    {
                        item* newItem = getRandomItem();
                        addItem(newItem);
                        isRunning = false;
                        break;
                    }
                    else if (chance == 2)
                    {
                        std::cout << "YOU GOT LVL UP!!" << Main_character->getLVL();
                        Main_character->AddLVL(randint(8,4));
                        std::cout << "->" << Main_character->getLVL() << "\n";
                        isRunning = false;
                        break;
                    }
                    else if (chance == 3)
                    {
                        int unit = randint(100, 1);
                        Main_character->changeCoins(unit);
                        std::cout << "U got " << unit << " Gold coins!";
                    }
                    else
                    {
                        std::cout << "error";
                        break;
                    }
                }
                else
                {
                    std::cout << "WRONG ANSWER! you will pay!\n||You take damage||";
                    Main_character->Take_away_HP(randint(Main_character->get_HP()));
                    isRunning = false;
                    break;
                }
            case 3:
                std::cout << "answer for me, how many \n" << num1 << " * " << num2 << "\n";
                std::cin >> answer;
                if (answer == num1 * num2)
                {
                    std::cout << "You are right! your reward!\n";
                    int chance = randint(3);
                    if (chance == 1)
                    {
                        item* newItem = getRandomItem();
                        addItem(newItem);
                        isRunning = false;
                        break;
                    }
                    else if (chance == 2)
                    {
                        std::cout << "YOU GOT LVL UP!!" << Main_character->getLVL();
                        Main_character->AddLVL(randint(8,4));
                        std::cout << "->" << Main_character->getLVL() << "\n";
                        isRunning = false;
                        break;
                    }
                    else if (chance == 3)
                    {
                        int unit = randint(100, 1);
                        Main_character->changeCoins(unit);
                        std::cout << "U got " << unit << " Gold coins!";
                    }
                    else
                    {
                        std::cout << "error";
                        break;
                    }
                }
                else
                {
                    std::cout << "WRONG ANSWER! you will pay!\n||You take damage||";
                    Main_character->Take_away_HP(randint(Main_character->get_HP()));
                    isRunning = false;
                    break;
                }
            }
            if (Main_character->get_HP() == 0 && FileSave::CheckFileName(Main_character->get_Name() + ".bin"))
            {
                std::cout << "Mysterius Human kill you\n";
                FileSave::deleteFile(Main_character->get_Name());
                gameOver = true;
                return;
            }
            waitForKey();
            
            break;
            
        case '2':
            system("cls");
            std::cout << "ok... bye";
            isRunning = false;
            break;
        default:
            system("cls");
            std::cout << "WRONG KEY!\n";
        }
    }
}

void Game::LocShop()
{
    bool isRunning = true;
    while (isRunning)
    {
        int Shopcount = randint(5, 3);
        bool shopMenu = true;
        MyArray<item*> Shop;
        for (int i = 0; i < Shopcount; i++)
        {
            item* newItem = getRandomItem(2);
            Shop.pushBack(newItem);
        }
        
        std::cout << "||you see a huge strange vehicle with the sign <Shop>||\n Do you want join? \n 1.yes \n 2.no";
        char key = _getch();
        switch (key)
        {
        case '1':
            std::cout << "\n||You saw the strange appearance of the salesman||\nstrange salesman: Hello, dear friend!";
            while (shopMenu)
            {
                std::cout << "What do you wish to buy or sell?\n 1.Buy\n 2.exit";
                char key2 = _getch();
                switch (key2)
                {
                case '1':
                    std::cout << "\nGood choise! See what i got: \n";
                    int index;
                    while (true)
                    {
                        std::cout << "=== Shop Inventory ===\n";
                        for (int i = 0; i < Shop.getSize(); ++i)
                        {
                            std::cout << i + 1 << ") " << Shop[i]->get_Name()<< " | " << Shop[i]->get_unit() << "/" << Shop[i]->get_unit_CUP() << "Price: "<< Shop[i]->get_price() <<" Gold coins\n";
                        }
                        std::cout << "What you want?\nYour capital: " << Main_character->getCoins() << " Gold coins\nEnter item index for buying it, enter 0 if you want leave: ";
                        std::cin >> index;
    
                        if (index <= -1 || index > Shop.getSize())
                        {
                            std::cout << "Invalid index!\n";
                            continue;
                        }

                        if (index == 0)
                        {
                            break;
                        }
                        
                        if (Shop[index - 1]->get_price() > Main_character->getCoins())
                        {
                            system("cls");
                            std::cout << "\nSorry, but you dont gave coins for it :[\n maybe something else?\n";
                            continue;
                        }
                        
                        std::cout << "Okie Dokie!\n";
                        Main_character->changeCoins(-Shop[index - 1]->get_price());
                        addItem(Shop[index - 1]);
                        Shop.erase(index - 1);
                        std::cout << "\nPurchase successful!\n";
                        waitForKey();
                    
                        
                    }
                    break;
                case '2':
                    std::cout << "\nGood bye! see you again!";
                    shopMenu = false;
                    isRunning = false;
                    break;
                default:
                    system("cls");
                    std::cout << "WRONG KEY!\n";
                }
            }
            break;
            
        case '2':
            std::cout << "\nYou ignore the shop and continue your journey.\n";
            waitForKey();
            isRunning = false;
            break;

        default:
            std::cout << "Wrong key!\n";
            waitForKey();
            break;
        }
    }
}

Game::Game()
{
    srand(static_cast<unsigned>(time(NULL)));
    
}


