#include "../src/Main/Game.h"

int main(int argc, char **argv) 
{
	auto game = Game::getInstance(argc, argv);
	return game->start(600, 800, "800x600:32");
    //return game->start(600, 800, "A game! tho");
}