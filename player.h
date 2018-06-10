#ifndef PLAYER_H_
#define PLAYER_H_
#include "Weapon.h"
#include "iostream"

// a class that defines a player object and its methods
// a player has a name, level, life, strength,weapon, and a position
// a player dies when either his level,life or strength reach zero
// a player can fight another player on the same position and lower one of his
// other fields
class Player {
    // the player's private fields
    char* name;
    int level;
    int life;
    int strength;
    Weapon weapon;
    int position;

    // an helper function to subtruct from a value but making sure it does not
    // go below a certain value, can be used with the default 0 for convenience
    static void subtructWithMin(int& number, int subtructBy, int minimum = 0);

   public:
    // player constructor, takes a given name and weapon and copies them
    // to create a player, position is initialized to 0 and its other fields are
    // initialized to 1
    explicit Player(const char* name, const Weapon& weapon);

    // destroys all players's resources
    ~Player();

    // creates a copy of a given player, copies the name and the weapon memory
    // errors
    Player(const Player& player);

    // assignment operator, deletes the player's resources and reassign them to
    // copies of the given player
    Player& operator=(const Player& player);

    // prints the player to the ostream given,
    // format: {player name: name, weapon: weapon}
    friend std::ostream& operator<<(std::ostream& os, const Player& player);

    // advances the current player level by one
    void nextLevel();

    // checks if the given string is the players name
    bool isPlayer(const char* playerName) const;

    // advances the current player position by one
    void makeStep();

    // advances the current player life by one
    void addLife();

    // adds the given int to the players strength, should only be positive
    void addStrength(int strengthToAdd);

    // returns if a player is alive, all of its fields are above 0
    bool isAlive() const;

    // returns if the player's weapon is weaker than the given value
    bool weaponIsWeak(int weaponMinStrength) const;

    // if both players are on the same position and their weapon's value differ,
    // then the one with the stronger weapon attacks the other, and subtruct a
    // value from one of his fields based on the attacker's weapon's target
    bool fight(Player& player);

    // comapares two players and return if the first is greater than the second
    // lexicographically
    friend bool operator>(const Player& player1, const Player& player2);
};

// comapares two players and return if the first is greater than the second
// lexicographically
bool operator<(const Player& player1, const Player& player2);
#endif