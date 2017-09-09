#include "game/Game.h"

int main() {
	if ( Game::INSTANCE->init() ) Game::INSTANCE->run();
	else return -1;
	return 0;
}