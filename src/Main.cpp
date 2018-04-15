#include "game/Game.h"

int main() {
	//std::vector<std::thread> threads;
	//
	//for (int i = 0; i < 16; i++) {
	//	threads.push_back(std::thread([] {
	//		printf("Test\n");
	//	}));
	//}
	//
	////for (int chunk_x = start.x; chunk_x < end.x; chunk_x++) {
	////	for (int chunk_y = start.y; chunk_y < end.y; chunk_y++) {
	////		threads.push_back(std::thread([] {
	////			std::cout << "TEST" << std::endl;
	////		}));
	////	}
	////}
	//
	//for (int i = 0; i < threads.size(); i++) {
	//	threads[i].join();
	//}

	if ( Game::INSTANCE->init() ) Game::INSTANCE->run();
	else return -1;
	return 0;
}