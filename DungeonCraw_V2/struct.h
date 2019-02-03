#include"header.h"
typedef struct sword {
	char name[20];
	int damage;
	int value;
}Sword;

typedef struct shield {
	char name[20];
	int protection;
	int value;
}Shield;

typedef struct player
{
	char name[20];
	int health;
	int health_cap;
	int money;
	int level;
	//[0]=health potion
	int items[5];
	int xp;
	int required_xp;
	Sword sword;
	Shield shield;



}Player;

typedef struct enemy {
	//char state;//'d'=dead, 'a'=alive, 'n'=no exists;
	char name[20];
	int health;
	int level;

	Shield shield;
	Sword sword;
}Enemy;

typedef struct inter {
	char layout[12][12];
	int num;
	//Enemy enemy;
	int treasure;//0=exists Exist,1=exists;
	int shop;//0==no exist, 1=Exist;
	int enemy;


}Interior;

typedef struct room {
	Interior inner;
	struct room *dRoom;
	int dUsed;
	struct room *wRoom;
	int wUsed;
	struct room *sRoom;
	int sUsed;
	struct room *aRoom;
	int aUsed;
	char direct;
	char pDirect;

}Room;

