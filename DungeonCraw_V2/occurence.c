#include "header.h"


int combat(Player *player1, Enemy *enemy) {
	int player_choice = 0, enemy_choice = 0;
	//damage player recieves | damage enemy ecieves
	int player_damage = 0, enemy_damage = 0;


	while (player1->health > 0 && enemy->health > 0 && player_choice != 5) {


		printf("\n%s health:%d", enemy->name, enemy->health);
		printf("\nmake a choice Block(1),slash(2),Stab(3),Potion(4),Run(5)");
		scanf("%d", &player_choice);
		system("cls");
		player_stats(*player1);
		enemy_choice = (rand() % 3) + 1;

		//if valid attack option
		if (player_choice <= 3) {


			//gets the damages of each character
			combat_damages(*player1, *enemy, player_choice, enemy_choice, &player_damage, &enemy_damage);

			//set new health values
			player1->health = player1->health - player_damage;
			enemy->health = enemy->health - enemy_damage;

			//prints the damages
			printf("\n%s took %d damage. %s took %d damage", player1->name, player_damage, enemy->name, enemy_damage);
		}
		else if (player_choice == 4) {
			gain_health(player1);
			printf("%s's health is now %d", player1->name, player1->health);

		}
	}


	if (player1->health <= 0) {
		//printf("\nYOU DIED");
		return -1;
	}
	else if (enemy->health <= 0) {

		loot(player1, *enemy);

	}


	
}

int combat_damages(Player player1, Enemy enemy, int player_choice, int enemy_choice, int *player_damage, int *enemy_damages) {
	//block beats stab|| slash beats block || stab beats slash

	//damage done to enemy
	int  edamage = (player1.sword.damage - (player1.level * 2)) + (player1.level * 4);
	//damage done to player
	int pdamage = (enemy.sword.damage - (enemy.level * 2)) + (enemy.level * 4);


	//block vs block
	if (player_choice == 1 && enemy_choice == 1) {
		*player_damage = pdamage;
		*enemy_damages = edamage;
		printf("\n%s and %s bashed shields", player1.name, enemy.name);

	}
	//block vs slash
	else if (player_choice == 1 && enemy_choice == 2) {
		*player_damage = pdamage * 2;
		*enemy_damages = edamage / 2;
		printf("\n%s slashes around %s's shield", enemy.name, player1.name);

	}
	//block vs stab
	else if (player_choice == 1 && enemy_choice == 3) {
		*player_damage = pdamage / 2;
		*enemy_damages = edamage * 2;
		printf("\n%s deflects %s stab with thier shield.", player1.name, enemy.name);
	}
	//slash vs block
	else if (player_choice == 2 && enemy_choice == 1) {
		*player_damage = pdamage / 2;
		*enemy_damages = edamage * 2;
		printf("\n%s slashs around %s's shield", player1.name, enemy.name);


	}
	//slash vs slash
	else if (player_choice == 2 && enemy_choice == 2) {
		*player_damage = pdamage;
		*enemy_damages = edamage;
		printf("\n%s and %s's slashs clashed", player1.name, enemy.name);


	}
	//swipe vs stab
	else if (player_choice == 2 && enemy_choice == 3) {
		*player_damage = pdamage * 2;
		*enemy_damages = edamage / 2;
		printf("\n%s's stab is faster then %s's slash", enemy.name, player1.name);
	}
	//stab vs block
	else if (player_choice == 3 && enemy_choice == 1) {
		*player_damage = pdamage * 2;
		*enemy_damages = edamage / 2;
		printf("\n%s deflects %s stab with thier shield.", enemy.name, player1.name);
	}
	//stab vs slash
	else if (player_choice == 3 && enemy_choice == 2) {
		*player_damage = pdamage / 2;
		*enemy_damages = edamage * 2;
		printf("\n%s's stab is faster then %s's slash", player1.name, enemy.name);
	}
	//stab vs slash
	else if (player_choice == 3 && enemy_choice == 3) {
		*player_damage = pdamage;
		*enemy_damages = edamage;
		printf("\n%s and %s stabbed eachothe", player1.name, enemy.name);
	}


}


int loot(Player *player1, Enemy enemy) {
	int xp = 0, hp = rand() % 6, sword = rand() % 8, shield = rand() % 8, gold = rand() % 5, choice = -1, money = 0;
	xp = enemy.level + (rand() % (enemy.level * 10));



	printf("\n%s", player1->name);
	printf("\n%s killed the %s", player1->name, enemy.name);
	printf("\n%s Recieved %d XP", player1->name, xp);
	player1->xp = player1->xp + xp;

	if (hp == 0) {
		player1->items[0]++;
		printf("\n%s found a health potion", player1->name);

	}
	if (sword == 0) {
		printf("\n%s found a %s sword with %d damage and %d value\nWould you like to keep it?yes(1) No(2)", player1->name, enemy.sword.name, enemy.sword.damage, enemy.sword.value);
		choice = 0;
		scanf("%d", &choice);
		if (choice == 1) {
			printf("\nWeapon swapped");
			player1->sword = enemy.sword;
		}


	}
	if (shield == 0) {

		printf("\n%s found a %s shield with %d protection and %d value\nWould you like to swap shield? Yes(1) No(2)", player1->name, enemy.shield.name, enemy.shield.protection, enemy.shield.value);

		system("pause");
		choice = 0;
		scanf("%d", &choice);
		if (choice == 1) {
			printf("\nshields swapped");
			player1->shield = enemy.shield;
		}


	}
	if (gold <4) {

		money = ((enemy.level + player1->level) * 2) + (rand() % (enemy.level + player1->level) * 2);
		printf("\n%s found %d shmeckles", player1->name, money);
		player1->money = player1->money + money;
	}

	return 0;


}

int explore(Player player1) {
	//	char direction[2] = { '\0' };
	char direction = '\0';
	int occurence = 0;




	printf("\nwhich direction would you like to go left('a'), right('d'),or forward('w')\n\n");


	while (direction == 10 || direction == 0) {
		scanf("%c", &direction);
	}

	/*printf("---%d---", direction);
	system("pause");*/
	system("cls");
	player_stats(player1);

	if (direction == 'a') {
		printf("\n%s went left and traveled %d paces down the hall\n", player1.name, rand() % 30);
	}
	else if (direction == 'd') {
		printf("\n%s went right and traveled %d paces down the hall\n", player1.name, rand() % 30);
	}
	else if (direction == 'w') {
		printf("\n%s went traight and traveled %d paces down the hall\n", player1.name, rand() % 30);
	}
	//system("pause");
	occurence = rand() % 95;

	return occurence;

}


int shop(Player *player1) {
	Sword sword1 = generate_sword(*player1), sword2 = generate_sword(*player1), sword3 = generate_sword(*player1);
	Shield shield1 = generate_shield(*player1), shield2 = generate_shield(*player1), shield3 = generate_shield(*player1);
	int potion_cost, player_choice = -1;


	sword1.value = sword1.value + (rand() % sword1.value);
	sword2.value = sword2.value + (rand() % sword2.value);
	sword3.value = sword3.value + (rand() % sword3.value);
	shield1.value = shield1.value + (rand() % shield1.value);
	shield2.value = shield2.value + (rand() % shield2.value);
	shield3.value = shield3.value + (rand() % shield3.value);

	potion_cost = 20 + rand() % 10;

	system("cls");
	player_stats(*player1);

	while (player_choice != 0) {
		player_choice = -1;
		printf("\nWelcome to the shop What would u like to Buy?");
		printf("\n                 Items");
		printf("\n\n                 Swords");
		printf("\n%s Sword(1)\t%s Sword(2)\t%s Sword(3)", sword1.name, sword2.name, sword3.name);
		printf("\nDamage:%d\tDamage:%d\tDamage:%d", sword1.damage, sword2.damage, sword3.damage);
		printf("\nCost:%d\t\tCost:%d\t\tCost:%d", sword1.value, sword2.value, sword3.value);
		printf("\n\n                 Shields");
		printf("\n%s shield(4)\t%s shield(5)\t%s shield(6)", shield1.name, shield2.name, shield3.name);
		printf("\nProtection:%d\tProtection:%d\tProtection:%d", shield1.protection, shield2.protection, shield3.protection);
		printf("\nCost:%d\t\tCost:%d\t\tCost:%d", shield1.value, shield2.value, shield3.value);
		printf("\n\n                  Other");
		printf("\nHealth Potion(7)");
		printf("\nCost:%d", potion_cost);
		printf("\n\n               Exit(0)");
		scanf("%d", &player_choice);


		system("cls");
		player_stats(*player1);

		if (player_choice == 1 && player1->money > sword1.value) {
			player1->money = player1->money - sword1.value;
			sword1.value = 5 + sword1.damage + (rand() % player1->level * 2);
			player1->sword = sword1;
			printf("\nThanks for buying %s Sword", sword2.name);
		}
		else if (player_choice == 2 && player1->money > sword2.value)
		{
			player1->money = player1->money - sword2.value;
			sword2.value = 5 + sword2.damage + (rand() % player1->level * 2);
			player1->sword = sword2;
			printf("\nThanks for buying %s Sword", sword2.name);
		}
		else if (player_choice == 3 && player1->money > sword3.value)
		{
			player1->money = player1->money - sword3.value;
			sword3.value = 5 + sword3.damage + (rand() % player1->level * 2);
			player1->sword = sword3;
			printf("\nThanks for buying %s Sword", sword3.name);
		}
		else if (player_choice == 4 && player1->money > shield1.value) {
			player1->money = player1->money - shield1.value;
			shield1.value = 5 + shield1.protection + (rand() % player1->level * 2);
			player1->shield = shield1;
			printf("\nThanks for buying %s Shield", shield1.name);
		}
		else if (player_choice == 5 && player1->money > shield2.value) {
			player1->money = player1->money - shield2.value;
			shield2.value = 5 + shield2.protection + (rand() % player1->level * 2);
			player1->shield = shield2;
			printf("\nThanks for buying %s Shield", shield2.name);
		}
		else if (player_choice == 6 && player1->money > shield3.value) {
			player1->money = player1->money - shield3.value;
			shield3.value = 5 + shield3.protection + (rand() % player1->level * 2);
			player1->shield = shield3;
			printf("\nThanks for buying %s Shield", shield3.name);

		}
		else if (player_choice == 7 && player1->money > potion_cost) {
			player1->money = player1->money - potion_cost;
			player1->items[0]++;
			printf("\nThanks for buying Health potion");

		}
		else if (player_choice != 0) {
			printf("\n%s cannot afford that", player1->name);
		}
		/*else if (player_choice==){
		printf("\nnot a valid option");
		}*/

	}

}

int treasure(Player *player1) {
	int option = rand() % 4, player_choice = 0;
	int gold = rand() % (20 * player1->level);
	Sword sword = generate_sword(*player1);
	Shield shield = generate_shield(*player1);

	system("cls");
	player_stats(*player1);


	printf("\n%s found %d Shmeckles", player1->name, gold);
	player1->money = player1->money + gold;

	//found sword
	if (option == 0) {
		printf("\n%s found a %s sword with %d damage and %d value", player1->name, sword.name, sword.damage, sword.value);
		printf("\nwould you like to swap your sword? Yes(1) No(2):");
		scanf("%d", &player_choice);
		if (player_choice == 1) {
			player1->sword = sword;
			printf("\nweapons swapped");
		}
	}
	//found shield
	else if (option == 1) {
		printf("\n%s found a %s shield with %d protection and %d value", player1->name, shield.name, shield.protection, shield.value);
		printf("\nwould you like to swap your shield? Yes(1) No(2):");
		scanf("%d", &player_choice);
		if (player_choice == 1) {
			player1->shield = shield;
			printf("\nshields swapped");
		}

	}
	//found both
	else if (option == 2) {
		printf("\n%s found a %s sword with %d damage and %d value", player1->name, sword.name, sword.damage, sword.value);
		printf("\n%s found a %s shield with %d protection and %d value", player1->name, shield.name, shield.protection, shield.value);
		printf("\nwould you like to swap your sword? Yes(1) No(2):");
		scanf("%d", &player_choice);
		if (player_choice == 1) {
			player1->sword = sword;
			printf("\nweapons swapped");
		}
		player_choice = 0;
		printf("\nwould you like to swap your shield? Yes(1) No(2):");
		scanf("%d", &player_choice);
		if (player_choice == 1) {
			player1->shield = shield;
			printf("\nshields swapped");
		}

	}



}
