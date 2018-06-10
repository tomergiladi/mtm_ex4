#include "Game.h"
#include <algorithm>
void Game::deletePlayers() {
    for (int i = 0; i < this->currentPlayers; i++) {
        delete this->players[i];
    }
    delete[] this->players;
}
int Game::getPlayerIndex(const char* playerName) const {
    for (int i = 0; i < this->currentPlayers; i++) {
        if ((this->players[i]->isPlayer(playerName))) {
            return i;
        }
    }
    return -1;
}
void Game::sortPlayers() const {
    // uses insertion sort to sort the players using their regular comparsion
    // operator
    for (int i = 1; i < this->currentPlayers; i++) {
        for (int j = i; j > 0 && *(this->players[j]) < *(this->players[j - 1]);
             j--) {
            std::swap(this->players[j], this->players[j - 1]);
        }
    }
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
    // we dont want to change anything if we are assigning to the same game
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
    // checks if the player is already in the game
    if (getPlayerIndex(playerName) != -1) {
        return NAME_ALREADY_EXISTS;
    }

    if (this->currentPlayers >= this->maxPlayers) {
        return GAME_FULL;
    }

    // assign the new player to the last place and advances the number of
    // players
    this->players[this->currentPlayers] =
        new Player(playerName, Weapon(weaponName, target, hit_strength));
    this->currentPlayers++;

    return SUCCESS;
}
GameStatus Game::nextLevel(const char* playerName) {
    int index = getPlayerIndex(playerName);

    // if the player is not in the game return an error
    if (index == -1) {
        return NAME_DOES_NOT_EXIST;
    }
    this->players[index]->nextLevel();
    return SUCCESS;
}
GameStatus Game::makeStep(const char* playerName) {
    int index = getPlayerIndex(playerName);

    // if the player is not in the game return an error
    if (index == -1) {
        return NAME_DOES_NOT_EXIST;
    }
    this->players[index]->makeStep();
    return SUCCESS;
}
GameStatus Game::addLife(const char* playerName) {
    int index = getPlayerIndex(playerName);

    // if the player is not in the game return an error
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
    // if the player is not in the game return an error
    if (index == -1) {
        return NAME_DOES_NOT_EXIST;
    }
    this->players[index]->addStrength(strengthToAdd);
    return SUCCESS;
}
bool Game::removeAllPlayersWithWeakWeapon(int weaponStrength) {
    int current = 0;
    int didRemove = false;
    while (current != this->currentPlayers) {
        if (this->players[current]->weaponIsWeak(weaponStrength)) {
            // if the weapon is weak, we delete the current player and move the
            // last player to its place
            delete this->players[current];
            this->currentPlayers--;
            this->players[current] = this->players[this->currentPlayers];
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

    // if either players does not exist return an erroe
    if (index1 == -1 || index2 == -1) {
        return NAME_DOES_NOT_EXIST;
    }
    // check if the fight was successfull
    bool fightSuccess = this->players[index1]->fight(*(this->players[index2]));

    // checks if either player died in the game and if so delete him
    if (!this->players[index1]->isAlive()) {
        delete this->players[index1];
        this->players[index1] = this->players[--this->currentPlayers];
    }
    if (!this->players[index2]->isAlive()) {
        delete this->players[index2];
        this->players[index2] = this->players[--this->currentPlayers];
    }
    // return if the fight was successful
    return fightSuccess ? SUCCESS : FIGHT_FAILED;
}
std::ostream& operator<<(std::ostream& os, const Game& game) {
    // sorts the game before priniting its players
    game.sortPlayers();
    for (int i = 0; i < game.currentPlayers; i++) {
        os << "player " << i << ": " << *(game.players[i]) << "," << std::endl;
    }
    return os;
}