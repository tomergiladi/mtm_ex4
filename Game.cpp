#include "Game.h"
#include <algorithm>
void Game::deletePlayers() {
    for (int i = 0; i < this->currentPlayers; i++) {
        delete this->players[i];
    }
    delete[] this->players;
}
int Game::getPlayerIndex(const char* playerName) {
    for (int i = 0; i < this->currentPlayers; i++) {
        if ((this->players[i]->isPlayer(playerName))) {
            return i;
        }
    }
    return -1;
}
Game::Game(int maxPlayers)
    : maxPlayers(maxPlayers),
      currentPlayers(0),
      players(new Player*[maxPlayers]) {
}
Game::Game(const Game& game)
    : maxPlayers(game.maxPlayers),
      currentPlayers(game.currentPlayers),
      players(new Player*[game.maxPlayers]) {
    for (int i = 0; i < game.currentPlayers; i++) {
        this->players[i] = new Player(*(game.players[i]));
    }
}
Game& Game::operator=(const Game& game) {
    if (this == &game) {
        return *this;
    }
    this->deletePlayers();
    this->currentPlayers = game.currentPlayers;
    this->maxPlayers = game.maxPlayers;
    this->players = new Player*[this->maxPlayers];
    for (int i = 0; i < game.currentPlayers; i++) {
        this->players[i] = new Player(*(game.players[i]));
    }
    return *this;
}
Game::~Game() {
    this->deletePlayers();
}
GameStatus Game::addPlayer(const char* playerName,
                           const char* weaponName,
                           Target target,
                           int hit_strength) {
    if (getPlayerIndex(playerName) != -1) {
        return NAME_ALREADY_EXISTS;
    }
    if (this->currentPlayers >= this->maxPlayers) {
        return GAME_FULL;
    }
    this->players[this->currentPlayers] =
        new Player(playerName, Weapon(weaponName, target, hit_strength));
    this->currentPlayers++;
    return SUCCESS;
}
GameStatus Game::nextLevel(const char* playerName) {
    int index = getPlayerIndex(playerName);
    if (index == -1) {
        return NAME_DOES_NOT_EXIST;
    }
    this->players[index]->nextLevel();
    return SUCCESS;
}
GameStatus Game::makeStep(const char* playerName) {
    int index = getPlayerIndex(playerName);
    if (index == -1) {
        return NAME_DOES_NOT_EXIST;
    }
    this->players[index]->makeStep();
    return SUCCESS;
}
GameStatus Game::addLife(const char* playerName) {
    int index = getPlayerIndex(playerName);
    if (index == -1) {
        return NAME_DOES_NOT_EXIST;
    }
    this->players[index]->addLife();
    return SUCCESS;
}
GameStatus Game::addStrength(const char* playerName, int strengthToAdd) {
    if (strengthToAdd < 0) {
        return INVALID_PARAM;
    }
    int index = getPlayerIndex(playerName);
    if (index == -1) {
        return NAME_DOES_NOT_EXIST;
    }
    this->players[index]->addStrength(strengthToAdd);
    return SUCCESS;
}
bool Game::removeAllPlayersWIthWeakWeapon(int weaponStrength) {
    int current = 0;
    int didRemove = false;
    while (current != this->currentPlayers) {
        if (this->players[current]->weaponIsWeak(weaponStrength)) {
            delete this->players[current];
            this->players[current] = this->players[--this->currentPlayers];
            didRemove = true;
        } else {
            current++;
        }
    }
    return didRemove;
}
GameStatus Game::fight(const char* playerName1, const char* playerName2) {
    int index1 = getPlayerIndex(playerName1);
    int index2 = getPlayerIndex(playerName2);
    if (index1 == -1 || index2 == -1) {
        return NAME_DOES_NOT_EXIST;
    }
    bool fightSuccess = this->players[index1]->fight(*(this->players[index2]));
    if (!this->players[index1]->isAlive()) {
        delete this->players[index1];
        this->players[index1] = this->players[--this->currentPlayers];
    }
    if (!this->players[index2]->isAlive()) {
        delete this->players[index2];
        this->players[index2] = this->players[--this->currentPlayers];
    }
    return fightSuccess ? SUCCESS : FIGHT_FAILED;
}
std::ostream& operator<<(std::ostream& os, const Game& game) {
    std::sort(game.players, game.players + game.currentPlayers,
              [](Player* playerPtr1, Player* playerPtr2) -> bool {
                  return *playerPtr1 < *playerPtr2;
              });
    for (int i = 0; i < game.currentPlayers; i++) {
        std::cout << "player " << i << ": " << *(game.players[i]) << ","
                  << std::endl;
    }
    return os;
}