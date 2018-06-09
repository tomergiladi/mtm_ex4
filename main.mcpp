#include <assert.h>
#include <iostream>
#include <vector>
#include "Game.h"
using namespace std;

void simpleTest() {
    Game game = Game(5);
    assert(game.addPlayer("Linoy", "lazer gun", LEVEL, 5) == SUCCESS);
    assert(game.addPlayer("Denis", "light saver", LIFE, 7) == SUCCESS);
    assert(game.addPlayer("Gal", "pirate sword", STRENGTH, 6) == SUCCESS);
    cout << game << endl;
    assert(game.fight("Linoy", "Denis") == SUCCESS);
    cout << game << endl;
    assert(game.addPlayer("Alon", "lazer gun", STRENGTH, 5) == SUCCESS);
    assert(game.addStrength("Alon", 10) == SUCCESS);
    assert(game.fight("Alon", "Gal") == SUCCESS);
    cout << game << endl;
    assert(game.removeAllPlayersWIthWeakWeapon(13) == true);
    cout << game << endl;
}
int main() {
    cout << "Sfasd";
    simpleTest();
    // std::vector<B> v;
    // v.push_back(B());
    // std::vector<A> v11dsfsdfdsfsafd111;
    // std::vector<A> v132;
}