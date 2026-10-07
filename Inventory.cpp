#include "Inventory.h"
#include "Character.h"

item::item(std::string Name, size_t Unit_CUP, int Price) : _Name(Name), _Unit_CUP(Unit_CUP), _Price(Price)
{
    _Unit = 1;
}

const int item::get_unit() const
{
    return _Unit;
}

int item::get_price()
{
    return _Price;
}

const std::string item::get_Name() const
{
    return _Name;
}

const size_t item::get_unit_CUP() const
{
    return _Unit_CUP;
}

bool item::add_unit(int Unit)
{
    if (_Unit + Unit <= _Unit_CUP)
    {
        _Unit = _Unit + Unit;
        return true;
    }
    return false;
}

item::~item() {}

Mystical_Fruit::Mystical_Fruit(std::string Name) : item(Name, 25, 5) {}

Mystical_Fruit::Mystical_Fruit(std::string Name, int Unit) : item(Name, 25, 5)
{
    _Unit_CUP = Unit;
}

void Mystical_Fruit::use(Character* target)
{
    if (auto* player = dynamic_cast<Player*>(target))
    {
        if (player->get_HP() < player->get_HP_CUP())
        {
            player->heal(25);
            _Unit--;
        }
    }
}

Mystical_Fruit::~Mystical_Fruit() {}

blue_milk::blue_milk(std::string Name) : item(Name, 15, 10) {}

blue_milk::blue_milk(std::string Name, int Unit) : item(Name, 15, 10)
{
    _Unit = Unit;
}

void blue_milk::use(Character* target)
{
    if (auto* player = dynamic_cast<Player*>(target))
    {
        player->powerUP(5);
        _Unit--;
    }
}

blue_milk::~blue_milk() {}

ak47::ak47(std::string Name) : item(Name, 1, 100) {}
ak47::ak47(std::string Name, int Unit) : item(Name, 1, 100)
{
    _Unit = Unit;
}
    

void ak47::use(Character* target)
{
    if (auto* enemy = dynamic_cast<Enemy*>(target))
    {
        enemy->Take_away_HP(100);
        _Unit--;
    }
}

ak47::~ak47() {}

Nanomachines::Nanomachines(std::string Name) : item(Name, 5, 15) {}
Nanomachines::Nanomachines(std::string Name, int Unit) : item(Name, 5, 15)
{
    _Unit = Unit;
}

void Nanomachines::use(Character* target)
{
    if (auto* player = dynamic_cast<Player*>(target))
    {
        player->AddArmor(50);
        _Unit--;
    }
}

Nanomachines::~Nanomachines() {}

Flawless_Hat::Flawless_Hat(std::string Name) : item(Name, 15, 50) {}
Flawless_Hat::Flawless_Hat(std::string Name, int Unit) : item(Name, 15, 50)
{
    _Unit = Unit;
}

void Flawless_Hat::use(Character* target)
{
    if (auto* player = dynamic_cast<Player*>(target))
    {
        player->AddLVL(1);
        _Unit--;
    }
}

Flawless_Hat::~Flawless_Hat() {}

