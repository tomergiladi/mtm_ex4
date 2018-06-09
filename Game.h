#ifndef GAME_H_
#define GAME_H_
#include "Player.h"
#include "iostream"
enum GameStatus {
    INVALID_PARAM,
    NAME_ALREADY_EXISTS,
    GAME_FULL,
    NAME_DOES_NOT_EXIST,
    FIGHT_FAILED,
    SUCCESS
};
class Game {
    int maxPlayers;
    int currentPlayers;
    Player** players;
    void deletePlayers();
    int getPlayerIndex(const char* playerName);

   public:
    explicit Game(int maxPlayers);
    Game(const Game& game);
    Game& operator=(const Game& game);
    ~Game();
    GameStatus addPlayer(const char* playerName,
                         const char* weaponName,
                         Target target,
                         int hit_strength);
    GameStatus nextLevel(const char* playerName);
    GameStatus makeStep(const char* playerName);
    GameStatus addLife(const char* playerName);
    GameStatus addStrength(const char* playerName, int strengthToAdd);
    bool removeAllPlayersWIthWeakWeapon(int weaponStrength);
    GameStatus fight(const char* playerName1, const char* playerName2);
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
};
#endif