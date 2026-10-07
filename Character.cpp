#include "Character.h"

Character::Character(std::string name)
{
    _Name = name;
}

const int Character::get_HP() const
{
    return _HP;
}

const size_t Character::get_HP_CUP() const
{
    return _HP_CUP;
}

const std::string Character::get_Name() const
{
    return _Name;
}

const size_t Character::get_Damage() const
{
    return _Damage;
}

void Character::set_HP(size_t HP)
{
    if (HP > _HP_CUP)
    _HP = _HP_CUP;
    else
    {
        _HP = HP;
    }
}

void Character::Take_away_HP(size_t Damage)
{
    if (_HP - Damage > 0)
    {
        _HP -= Damage;
    }
    else
    {
        _HP = 0;
    }
}

void Character::powerUP(size_t power)
{
    _Damage += power;
}

Character::~Character(){}

Player::Player(std::string name, size_t HP_CUP,int HP, size_t Damage, size_t LVL, size_t Armor,int Coins) : Character(name)
{
    _HP_CUP = HP_CUP;
    _HP = HP;
    _Damage = Damage;
    _LVL = LVL;
    _Armor = Armor;
    _Coins = Coins;
}

Player::Player(Player& other) : Character(other._Name)
{
    _HP_CUP = other._HP_CUP;
    _HP = other._HP;
    _Damage = other._Damage;
    _LVL = other._LVL;
    _Armor = other._Armor;
    _Coins = other._Coins;
}

void Player::attack(Character* enemy) 
{
    if (enemy->get_HP() > _Damage)
    {
        enemy->Take_away_HP(_Damage);
    }
    else
    {
        enemy->set_HP(0);
    }
}

const size_t Player::getLVL() const
{
    return _LVL;
}

const size_t Player::getArmor() const
{
    return _Armor;
}

const int Player::getCoins() const
{
    return _Coins;
}

void Character::heal(size_t heal)
{
    if (_HP + heal > _HP_CUP)
    {
        _HP = _HP_CUP;
    }
    else
    {
        _HP += heal;
    }
}

void Player::AddArmor(size_t Armor)
{
    if (_Armor + Armor > 100)
    {
        _Armor = 100;
    }
    else
    {
        _Armor += Armor;
    }
}

void Player::AddLVL(size_t lvl)
{
    _LVL += lvl;
    LVLBuff(lvl);
}

void Player::Take_away_Armor(size_t Damage)
{
    if (Damage > _Armor)
    {
        _Armor = 0;
    }
    else
    {
        _Armor -= Damage;
    }
}

void Player::changeCoins(int change)
{
    _Coins += change;
}


void Player::LVLBuff(size_t lvl)
{
    _HP_CUP += 5 * lvl;
    _Damage += 2 * lvl;
}


std::ostream& operator<<(std::ostream& os, const Player& other)
{
    os <<"===Your Stats===\nName:" << other._Name << "\nHP:" << other._HP << "/" << other._HP_CUP << "\nArmor:" << other._Armor << "/100" << "\nBase damage:" << other._Damage << "\nGold_Coins:" << other._Coins <<"\nLVL:" << other._LVL<< "\n";
    return os;
}

Player::~Player() {}

Enemy::Enemy(std::string name, size_t HP_CUP, size_t Damage) : Character(name)
{
    _HP = HP_CUP;
    _HP_CUP = HP_CUP;
    _Damage = Damage;
}


Enemy::Enemy(Enemy& other) : Character(other._Name)
{
    _HP =       other._HP_CUP;
    _HP_CUP =   other._HP_CUP;
    _Damage =   other._Damage;
}

void Enemy::attack(Character* enemy) 
{
    auto* hero_enemy = static_cast<Player*>(enemy);

    if (hero_enemy->getArmor() != 0)
    {
        hero_enemy->Take_away_Armor(_Damage);
    }
    else
    {
        hero_enemy->Take_away_HP(_Damage);
    }
    
}

void Enemy::betterenemy(size_t boss)
{
    _HP_CUP += 15  * boss;
    _HP = _HP_CUP;
    _Damage += 6  * boss;
}

std::ostream& operator<<(std::ostream& os, const Enemy& other)
{
    os <<"===Enemy Stats===\nName:" << other._Name << "\nHP:" << other._HP << "/" << other._HP_CUP << "\nBase damage:" << other._Damage << "\n";
    return os;
}

Enemy::~Enemy(){}

