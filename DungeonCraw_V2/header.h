#ifndef HEADER_H
#define HEADER_H

#define _CRT_SECURE_NO_WARNINGS
#define  _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "struct.h"

//main
int main(void);

//Room
Room *makeRoom(Interior newInter);
int insertatEnd(Room **map, Interior newInter);
Interior makeInterior(void); 
int navigate(Room **map,Player *player1);
int printMap(char layout[][10]);
int move(char layout[][10], Room *map,Player *player1);

//occurence
int loot(Player *player1, Enemy enemy);
int combat_damages(Player player1, Enemy enemy, int player_choice, int enemy_choice, int *player_damage, int *enemy_damages);
int combat(Player *player1, Enemy *enemy);
int treasure(Player *player1);
int shop(Player *player1);
int treasure(Player *player1);

//crawl
Enemy spawn_enemy(Player player1);
Sword generate_sword(Player player1);
Shield generate_shield(Player enemy);
Player start(void);
void player_stats(Player player1);
int level_up(Player *player1);
int gain_health(Player *player1);


#endif