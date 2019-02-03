#include "header.h"

int main(void) {
	srand(time(NULL));
	Room *map = makeRoom(makeInterior());

	Player player1 = start();

	navigate(&map,&player1);

	system("pause");


	return 0;
}

