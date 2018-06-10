#include "Player.h"
#include "math.h"
#include "string.h"
Player::Player(const char* name, const Weapon& weapon)
    : name(new char[strlen(name) + 1]),
      level(1),
      life(1),
      strength(1),
      weapon(weapon),
      position(0) {
    strcpy(this->name, name);
}
Player::Player(const Player& player)
    : name(new char[strlen(player.name) + 1]),
      level(player.level),
      life(player.life),
      strength(player.strength),
      weapon(player.weapon),
      position(player.position) {
    strcpy(this->name, player.name);
}
Player& Player::operator=(const Player& player) {
    // we dont want to change anything if we are assigning to the same player
    if (this == &player) {
        return *this;
    }
    this->level = player.level;
    this->life = player.life;
    this->strength = player.strength;
    this->weapon = player.weapon;
    this->position = player.position;
    delete[] this->name;
    this->name = new char[strlen(player.name) + 1];
    strcpy(this->name, player.name);
    return *this;
}
Player::~Player() {
    delete[] this->name;
}
void Player::nextLevel() {
    this->level++;
}
bool Player::isPlayer(const char* playerName) const {
    return strcmp(this->name, playerName) == 0;
}
void Player::makeStep() {
    this->position++;
}
void Player::addLife() {
    this->life++;
}
void Player::addStrength(int strengthToAdd) {
    this->strength += strengthToAdd;
}
bool Player::isAlive() const {
    return this->level > 0 && this->life > 0 && this->strength > 0;
}

bool Player::weaponIsWeak(int weaponMinStrength) const {
    return this->weapon.getValue() < weaponMinStrength;
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    return os << "{player name: " << player.name
              << ", weapon: " << player.weapon << "}";
}
void Player::subtructWithMin(int& number, int subructBy, int minimum) {
    number -= subructBy;
    if (number < minimum) {
        number = minimum;
    }
}
bool Player::fight(Player& player) {
    if (this->position != player.position || this->weapon == player.weapon) {
        return false;
    }
    if (player.weapon > this->weapon) {
        return player.fight(*this);
    }
    int hitStrength = this->weapon.getHitStrength();
    switch (this->weapon.getTarget()) {
        case LEVEL: {
            Player::subtructWithMin(player.level, hitStrength);
            break;
        }
        case STRENGTH: {
            Player::subtructWithMin(player.strength, hitStrength);
            break;
        }
        case LIFE: {
            Player::subtructWithMin(player.life, hitStrength);
            break;
        }
    }
    return true;
}
bool operator>(const Player& player1, const Player& player2) {
    return strcmp(player1.name, player2.name) > 0;
}
bool operator<(const Player& player1, const Player& player2) {
    return player2 > player1;
}