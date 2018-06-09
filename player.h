#ifndef PLAYER_H_
#define PLAYER_H_
#include "iostream"
#include "Weapon.h"
class Player {
    char* name;
    int level;
    int life;
    int strength;
    Weapon weapon;
    int position;
    static void subtructWithMin(int& number, int subtructBy, int minimum = 0);

   public:
    explicit Player(const char* name, const Weapon& weapon);
    ~Player();
    Player(const Player& other);
    Player& operator=(const Player& other);
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
    void nextLevel();
    bool isPlayer(const char* playerName) const;
    void makeStep();
    void addLife();
    void addStrength(int strengthToAdd);
    bool isAlive() const;
    bool weaponIsWeak(int weaponMinStrength) const;
    bool operator>(const Player& other) const;
    bool operator<(const Player& other) const;
    bool fight(Player& player);
};
#endif