#include "header.h"

Room *makeRoom(Interior newInter) {

	Room *newRoom = NULL;

	newRoom = (Room*)malloc(sizeof(Room));
	if (newRoom != NULL) {
		newRoom->inner = newInter;
		newRoom->aRoom = NULL;
		newRoom->sRoom = NULL;
		newRoom->dRoom = NULL;
		newRoom->wRoom = NULL;
		newRoom->direct = '\0';
		newRoom->pDirect = '\0';

	}
	return newRoom;
}

int insertatEnd(Room **map, Interior newInter) {

	Room *pMem = NULL, *pCur = NULL;

	pMem = makeRoom(newInter);
	pCur = *map;
	if (pCur != NULL) {
		if (pCur->direct == 'w') {
			pCur->wRoom = pMem;
			pMem->sRoom = pCur;
			pCur->wUsed = 1;
			pMem->sUsed = 1;
		}
		else if (pCur->direct == 's') {
			pCur->sRoom = pMem;
			pMem->wRoom = pCur;
			pCur->sUsed = 1;
			pMem->wUsed = 1;
		}
		else if (pCur->direct == 'd') {
			pCur->dRoom = pMem;
			pMem->aRoom = pCur;
			pCur->dUsed = 1;
			pMem->aUsed = 1;

		}
		else if (pCur->direct == 'a') {
			pCur->aRoom = pMem;
			pMem->dRoom = pCur;
			pCur->aUsed = 1;
			pMem->dUsed = 1;

		}



	}

}

Interior makeInterior(void) {
	static int i = 0;
	Interior newInter;

	newInter.enemy = rand() % 2;
	newInter.treasure = rand() % 7;
	newInter.shop = rand() % 12;
	newInter.num = i;
	i++;

	roomgraphic(newInter.layout,newInter);

	
	return newInter;
}
//not done
int navigate(Room **map,Player *player1) {
	char direct = '\0';
	Room *pCur = NULL;
	Enemy enemy1;
	pCur = *map;

	if (pCur != NULL) {
		while (direct != 'p') {
			printf("%d\n", pCur->inner.num);
			 move(pCur->inner.layout,pCur,player1);
			 if (player1->health > 0) {
				 printf("which direction a,s,d,w, or e to exit\n");

				 //gets direction
				 direct = getch();

				 if (direct == 'a' || direct == 's' || direct == 'd' || direct == 'w') {
					 pCur->direct = direct;

					 if (direct == 'a') {
						 if (pCur->aRoom != NULL) {
							 pCur->aRoom->pDirect = 'd';
							 navigate(&pCur->aRoom, player1);
						 }
						 else
						 {

							 insertatEnd(&pCur, makeInterior());
							 pCur->aRoom->pDirect = 'd';
							 navigate(&pCur->aRoom, player1);

						 }


					 }

					 if (direct == 'd') {
						 if (pCur->dRoom != NULL) {
							 pCur->dRoom->pDirect = 'a';
							 navigate(&pCur->dRoom, player1);
						 }
						 else
						 {

							 insertatEnd(&pCur, makeInterior());
							 pCur->dRoom->pDirect = 'a';
							 navigate(&pCur->dRoom, player1);

						 }

					 }

					 if (direct == 's') {
						 if (pCur->sRoom != NULL) {
							 pCur->sRoom->pDirect = 'w';
							 navigate(&pCur->sRoom, player1);
						 }
						 else
						 {

							 insertatEnd(&pCur, makeInterior());
							 pCur->sRoom->pDirect = 'w';
							 navigate(&pCur->sRoom, player1);

						 }

					 }

					 if (direct == 'w') {
						 if (pCur->wRoom != NULL) {
							 pCur->wRoom->pDirect = 's';
							 navigate(&pCur->wRoom, player1);
						 }
						 else
						 {

							 insertatEnd(&pCur, makeInterior());
							 pCur->wRoom->pDirect = 's';
							 navigate(&pCur->wRoom, player1);

						 }

					 }


				 }
			 }
			 else if (player1->health <= 0) {
				 printf("You died\n");
					 direct = 'p';
			 }

		}
	}
}

int roomgraphic(char layout[][10],Interior inter) {
	
	int enemyX=-1, enemyY=-1, treasureX=-1, treasureY=-1,shopX=-1,shopY=-1;

	if (inter.enemy == 0) {
		enemyX = (rand() % 5) + 2;
		enemyY = (rand() % 5) + 2;
	}
	if (inter.treasure == 0) {
		do {
			
			treasureX = (rand() % 7) + 1;
			treasureY = (rand() % 7) + 1;
		} while (treasureX == enemyX&&treasureY == enemyY);
	}
	if (inter.shop == 0) {
		do {

			shopX = (rand() % 7) + 1;
			shopY = (rand() % 7) + 1;
		} while ((shopX == enemyX&&shopY == enemyY)|| (shopX == enemyX&&shopY == enemyY));

	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {

			if (enemyX!=-1&&(i==enemyX&&j==enemyY))
			{
				layout[i][j] = 'E';
			}
			else if (treasureX != -1 && (i == treasureX&&j == treasureY)) {
				layout[i][j] = 'T';
			}
			else if (shopX != -1 && (i == shopX&&j == shopY)) {
				layout[i][j] = 'S';
			}

			else {
				layout[i][j] = ' ';
			}

		}
	}
	for (int i = 1; i < 9; i++) {
		layout[i][0] = '|';
		layout[i][9] = '|';


	}
	for (int j = 0; j < 10; j++) {
		layout[0][j] = '_';
		layout[9][j] = '-';
		
	}


	layout[0][5] = 'w';
	layout[9][5] = 's';
	layout[5][0] = 'a';
	layout[5][9] = 'd';





}

int printMap(char layout[][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf(" %c", layout[i][j]);
		}
		printf("\n");
	}



}


int move(char layout[][10], Room *map,Player *player1) {
	int pX=5, pY=5;
	char nextChar = '\0';
	char nextPlace = '\0';
	Enemy enemy;

	if (map->pDirect == 'a') {
		layout[5][1] = 'P';
		pX = 5;
		pY = 1;
	}
	else if (map->pDirect == 'd') {
		layout[5][8] = 'P';
		pX = 5;
		pY = 8;

	}
	else if (map->pDirect == 'w') {
		layout[1][5] = 'P';
		pX = 1;
		pY = 5;
	}
	else if (map->pDirect == 's') {
		layout[8][5] = 'P';
		pX = 8;
		pY = 5;
	}

	while (nextChar != 'w' && nextChar != 's' && nextChar != 'a' && nextChar != 'd'&&player1->health>0)
	{
		printf("pick a direction\n");
		nextPlace = getch();

		if (nextPlace == 'w') {
			nextChar = layout[pX - 1][pY];

			if (nextChar == 'E') {
				enemy = spawn_enemy(*player1);
				combat(player1, &enemy);
				level_up(player1);
				if (enemy.health <= 0) {
					layout[pX - 1][pY] = 'X';
				}

			}
			else if (nextChar == 'S') {
				shop(player1);
			}
			else if (nextChar == 'T') {
				treasure(player1);
					layout[pX - 1][pY] = 'X';

			}
			else if (nextChar != '|' && nextChar != '_' && nextChar != '-'&&  nextChar != 'd'&& nextChar != 'X') {
				layout[pX][pY] = ' ';
				pX--;
				layout[pX][pY] = 'P';
			}
		

		}
		else if (nextPlace == 's') {
			nextChar = layout[pX + 1][pY];		
			if (nextChar == 'E') {
				enemy = spawn_enemy(*player1);
				combat(player1, &enemy);
				level_up(player1);
				if (enemy.health <= 0) {
					layout[pX + 1][pY] = 'X';
				}
			}
			else if (nextChar == 'S') {
				shop(player1);
			}
			else if (nextChar == 'T') {
				treasure(player1);
				layout[pX + 1][pY] = 'X';
			}
			else if (nextChar != '|' && nextChar != '_' && nextChar != '-'&&  nextChar != 'd'&& nextChar != 'X') {
				layout[pX][pY] = ' ';
				pX++;
				layout[pX][pY] = 'P';
			}
			
		}
		else if (nextPlace == 'a') {
			nextChar = layout[pX][pY - 1];
			if (nextChar == 'E') {
				enemy = spawn_enemy(*player1);
				combat(player1, &enemy);
				level_up(player1);
				if (enemy.health <= 0) {

					layout[pX][pY - 1] = 'X';
				}
			}
			else if (nextChar == 'S') {
				 shop(player1);
			}
			else if (nextChar == 'T') {
				treasure(player1);
				layout[pX][pY - 1] = 'X';
			}
			else if (nextChar != '|' && nextChar != '_' && nextChar != '-'&&  nextChar != 'd'&& nextChar != 'X') {
				layout[pX][pY] = ' ';
				pY--;
				layout[pX][pY] = 'P';
			}
			
		

		}
		else if (nextPlace == 'd') {
			nextChar = layout[pX][pY + 1];
			if (nextChar == 'E') {
				enemy = spawn_enemy(*player1);
				combat(player1, &enemy);
				level_up(player1);
				if (enemy.health <= 0) {
					layout[pX][pY + 1] = 'X';
				}
			}
			else if (nextChar == 'S') {
				shop(player1);
			}
			else if (nextChar == 'T') {
				treasure(player1);
				layout[pX][pY + 1] = 'X';

			}
			else if (nextChar != '|' && nextChar != '_' && nextChar != '-'&&  nextChar != 'd'&& nextChar != 'X') {
				layout[pX][pY] = ' ';
				pY++;
				layout[pX][pY] = 'P';
			}
			
		}

		system("cls");
		player_stats(*player1);
		printf("%d", map->inner.num);
		printMap(layout);
	}
}