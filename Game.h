#ifndef GAME_H_
#define GAME_H_
#include "Player.h"
#include "iostream"

// enum that defines the possible error types returned from the game class
enum GameStatus {
    INVALID_PARAM,
    NAME_ALREADY_EXISTS,
    GAME_FULL,
    NAME_DOES_NOT_EXIST,
    FIGHT_FAILED,
    SUCCESS
};
class Game {
    // the game private fields
    int maxPlayers;      // the maximum nuber of players int the game
    int currentPlayers;  // the amount of players currently in the game
    Player** players;  // players array where all players of the game are stored

    // deletes all players from the current game
    void deletePlayers();

    // gets a player name and returns the index in the array that matches the
    // player returns -1 if no player of that name exist
    int getPlayerIndex(const char* playerName) const;

    // sorts lexicographically the current players array based on the players
    // name
    // note it is a const function since the array order is not important to the
    // game, it only matters in the printing of the game
    void sortPlayers() const;

   public:
    // creates a new game with initial max players
    explicit Game(int maxPlayers);

    // copies an existing game with all of its fields and resources
    Game(const Game& game);

    // assignment operator. deletes all of the game resources and copies the new
    // game resources and fields.
    Game& operator=(const Game& game);

    // destroys the game resources
    ~Game();

    // add a new player to the game, needs a player name and  a weapon name,
    // target, strength to create the player and t-he weapon and store them
    // return SUCCESS if no error were encountered
    // return NAME_ALREADY_EXISTS if the player is already in the game and
    // GAME_FULL if there is no room left for new players
    GameStatus addPlayer(const char* playerName,
                         const char* weaponName,
                         Target target,
                         int hit_strength);

    // recieves a players name and if that player exist advances its level
    // return SUCCESS if no error were encountered
    // return NAME_DOES_NOT_EXIST if the player is not in the current game
    GameStatus nextLevel(const char* playerName);

    // recieves a players name and if that player exist advances its position
    // return SUCCESS if no error were encountered
    // return NAME_DOES_NOT_EXIST if the player is not in the current game
    GameStatus makeStep(const char* playerName);

    // recieves a players name and if that player exist advances its life by one
    // return SUCCESS if no error were encountered
    // return NAME_DOES_NOT_EXIST if the player is not in the current game
    GameStatus addLife(const char* playerName);

    // recieves a players name and if that player exist adds the given positive
    // int to its stength
    // return SUCCESS if no error were encountered
    // return NAME_DOES_NOT_EXIST if the player is not in the current game
    // return INVALID_PARAM if strengthToAdd is not positive
    GameStatus addStrength(const char* playerName, int strengthToAdd);

    // removes all players with weak weapon value from the game
    // return true if atleast one player was removed and false otherwise
    bool removeAllPlayersWithWeakWeapon(int weaponStrength);

    // calls the fight method between the two players and if one of them dies,
    // removes him from teh game
    // return NAME_DOES_NOT_EXIST if one of the players is not in the current
    // game
    // returns FIGHT_FAILED if the fight was not taken( the players are not in
    // the same position or their weapons value are the same)
    // return SUCCESS if the fight was successful
    GameStatus fight(const char* playerName1, const char* playerName2);

    // prints the game to the ostream given,
    // prints each player in a row the format player i :{player}
    friend std::ostream& operator<<(std::ostream& os, const Game& game);
};
#endif