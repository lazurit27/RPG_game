#pragma once
#include <string>
#include <iostream>
#include "MyArray.h"
#include "Inventory.h"


class Character
{
protected:
    std::string _Name;
    size_t _HP_CUP;
    int _HP;
    size_t _Damage;
public:
    Character(std::string name);
    virtual void attack(Character* enemy) = 0;

    //getters
    const size_t get_HP_CUP() const;
    const int get_HP() const;
    const std::string get_Name() const;
    const size_t get_Damage() const;
    //setter
    void set_HP(size_t HP);
    void Take_away_HP(size_t Damage);
    void powerUP(size_t power);
    void heal(size_t heal);
    
    
    virtual ~Character();
};

class Player : public Character
{
    private:
    size_t _Armor;
    size_t _LVL;
    int _Coins;
    void LVLBuff(size_t lvl);
    public:
    Player(std::string name, size_t HP_CUP = 100,int HP = 100, size_t Damage = 15, size_t LVL = 0, size_t Armor = 0,int Coins = 0);
    Player(Player& other);
    void attack(Character* enemy) override;
    //getters
    const size_t    getLVL()    const;
    const size_t    getArmor()  const;
    const int       getCoins()  const;
    //setters
    void AddArmor(size_t Armor);
    void AddLVL(size_t lvl);
    void Take_away_Armor(size_t Damage);
    void changeCoins(int change);
    friend std::ostream& operator<<(std::ostream& os, const Player& other);
    ~Player();
};

class Enemy :public Character
{
    public:
    Enemy(std::string name, size_t HP_CUP, size_t _Damage);
    Enemy(Enemy& other);
    void attack(Character* enemy) override;
    void betterenemy(size_t boss = 1);
    
    friend std::ostream& operator<<(std::ostream& os, const Enemy& other);
    ~Enemy();
    
};
