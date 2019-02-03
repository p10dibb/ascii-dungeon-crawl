#include "header.h"

Shield generate_shield(Player enemy) {
	Shield gen;
	char name[20][10] = { { "Paper" },{ "Wood" },{ "Iron" },{ "steel" },{ "Diamond" } };

	strcpy(gen.name, name[enemy.level / 5]);
	gen.protection = 10 + (rand() % enemy.level * 2);
	gen.value = 5 + gen.protection + (rand() % enemy.level * 2);


	return gen;

}

Sword generate_sword(Player player1) {
	Sword gen;
	char name[20][10] = { { "Paper" },{ "Wood" },{ "Iron" },{ "steel" },{ "Diamond" } };

	strcpy(gen.name, name[player1.level / 5]);
	gen.damage = 10 + (rand() % player1.level * 2);
	gen.value = 5 + gen.damage + (rand() % player1.level * 2);
	return gen;

}

Enemy spawn_enemy(Player player1) {
	char types[][10] = { { "Goblin" },{ "Skeleton" },{ "Ghoul" },{ "Ork" },{ "Hound" },{ "Zombie" },{ "Spirit" },{ "Halfling" },{ "Bandit" },{ "Raider" } };
	Enemy enemy = { NULL,0,0,NULL };
	int set = rand() % 10;
	strcpy(enemy.name, types[set]);
	enemy.level = (player1.level - 3) + (rand() % 7);
	if (enemy.level  <1) {
		enemy.level = 1;
	}

	enemy.health = 90 + (rand() % (enemy.level)) * 10;

	enemy.shield = generate_shield(player1);
	enemy.sword = generate_sword(player1);



	return enemy;


}


Player start(void) {
	Player player1 = { "sdda",50,0,1,0,NULL,NULL };
	Sword start_sword = { "wood",10,5 };
	Shield start_shield = { "paper ",5,5 };

	player1.shield = start_shield;
	player1.sword = start_sword;
	player1.level = 1;
	player1.required_xp = 7;
	player1.health = 200;
	player1.health_cap = 200;

	printf("\ninput Name:");
	scanf("%s", &player1.name);
	player1.items[0] = 1;

	player_stats(player1);



	return player1;
}

void player_stats(Player player1) {

	//printf("Name:%s\nLevel:%d\nHealth:%d\nShmeckles:%d\nWeapon:%s\nShield:%s\n", player1.name, player1.level, player1.health, player1.money, player1.sword.name, player1.shield.name);

	printf("\nName: %s", player1.name);
	printf("\nLevel:%d\tXP:%d", player1.level, player1.xp);
	printf("\nXP till next level:%d", (player1.required_xp - player1.xp));
	printf("\nHealth:%d/%d", player1.health, player1.health_cap);
	printf("\nShmeckles:%d", player1.money);
	printf("\n\t   ITEMS\n%s sword\t%s shield""\tHealth Potion:(%d)", player1.sword.name, player1.shield.name, player1.items[0]);
	printf("\ndamage:%d\tprotection:%d\thealth:%d", player1.sword.damage, player1.shield.protection, 50 + player1.level * 5);
	printf("\nvalue:%d\t\tvalue:%d\n", player1.sword.value, player1.shield.value);

	printf("\n");
}

int level_up(Player *player1) {
	int XP = 0;

	if (player1->xp >= player1->required_xp) {

		XP = (player1->xp) - (player1->required_xp);

		player1->xp = XP;
		player1->level = player1->level + 1;
		printf("\n%s Leveled up %s is now level %d", player1->name, player1->name, player1->level);
		player1->required_xp = player1->required_xp + ((player1->required_xp) / 2) + (player1->level * 2);
		player1->health_cap = player1->health_cap + (player1->health_cap / 10);
		level_up(player1);
	}
	else {
		return 0;
	}

}

int gain_health(Player *player1) {

	if (player1->items[0] > 0) {

		//takes away a health potion
		player1->items[0]--;
		//increases health by 50 +5*LEVEL
		player1->health = player1->health + 50 + (player1->level * 5);
		//makes it so you cant exceed max health
		if (player1->health > player1->health_cap) {
			player1->health = player1->health_cap;
		}

		printf("\n%s used a health potion and got %d health", player1->name, 50 + (player1->level * 5));


	}
	else {
		printf("\n%s has no more health potions", player1->name);
	}

}