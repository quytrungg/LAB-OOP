#include "Header.h"


int main() {
	Game game;
	game.startGame();
	game.playGame();
	game.displayGame();
	std::cout << "\nPress enter to end the program...";
	std::cin.get();
	return 0;
}
