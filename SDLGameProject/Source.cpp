#include <iostream>
// using game class
#include "Game.h"

int main(int argc, char** argv) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// allocate the object of the game class
	Game* game = new Game();
	// runs the game
	game->Run("Hello SDL", 800, 600, false);
	// deallocates the game object
	delete game;

	return 0;
}