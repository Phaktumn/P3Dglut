#include "../src/Main/Game.h"

int main(int argc, char **argv) 
{
	auto game = Game::getInstance(argc, argv);
    return game->start(600, 800, "A game! tho");
}