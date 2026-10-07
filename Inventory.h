#pragma once
#include <string>
#include <iostream>
class Character;

class item
{
protected:
    std::string _Name;
    size_t _Unit_CUP;
    int _Unit;
    int _Price;
public:
    item(std::string Name, size_t Unit_CUP, int Price);
    const int get_unit() const;
    int get_price();
    const std::string get_Name() const;
    const size_t get_unit_CUP() const;
    bool add_unit(int Unit = 1);
    virtual void use(Character* target) = 0;
    virtual ~item();
};

class Mystical_Fruit : public item
{
public:
    Mystical_Fruit(std::string Name);
    Mystical_Fruit(std::string Name, int Unit);
    void use(Character* target) override;
    virtual ~Mystical_Fruit();
};

class blue_milk : public item
{
public:
    blue_milk(std::string Name);
    blue_milk(std::string Name, int Unit);
    void use(Character* target) override;
    virtual ~blue_milk();
};

class ak47 : public item
{
public:
    ak47(std::string Name);
    ak47(std::string Name, int Unit);
    void use(Character* target) override;
    virtual ~ak47();
};

class Nanomachines : public item
{
public:
    Nanomachines(std::string Name);
    Nanomachines(std::string Name, int Unit);
    void use(Character* target) override;
    virtual ~Nanomachines();
};

class Flawless_Hat : public item
{
public:
    Flawless_Hat(std::string Name);
    Flawless_Hat(std::string Name, int Unit);
    void use(Character* target) override;
    virtual ~Flawless_Hat();
};


