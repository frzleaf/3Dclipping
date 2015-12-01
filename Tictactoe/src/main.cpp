#include <iostream>
#include "Player.h"
#include "Board.h"
#include "Game.h"
using namespace std;



static int DEFAULT_SIZE = 20;

void test();
void test1();

int main() {


	test1();

	return 0;
}

void test1(){
		Board board(DEFAULT_SIZE);
		Game game(board);
		game.welcome();
}


void test(){
		Player thanh("Thanh"), duc("Duc");
		Board game(DEFAULT_SIZE);
		game.addPlayer(thanh);
		game.addPlayer(duc);
		game.showStatus();
		game.startMatch();
		game.reset();
}



