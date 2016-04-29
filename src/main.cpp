#include "../src/Main/Game.h"

int main(int argc, char **argv) 
{
	auto game = Game::getInstance(argc, argv);
	return game->start(900, 1600, "Solar System");
}