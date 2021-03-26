#ifndef _ATTACKER_H_
#define _ATTACKER_H_

#include "..\\App\\SimpleSprite.h"
#include ".\\Player.h"
#include ".\\Path.h"
//-----------------------------------------------------------------------------
// Attacker
//-----------------------------------------------------------------------------
class Attacker
{
	// This class will represent COVID cells trying to infiltrate the tournament
public:
	Attacker(int attId, float posX, float posY, int level, Player* thePlayer, Path* thePath);
	~Attacker();
	CSimpleSprite* GetSprite() { return sprite; }
	void Hit(float damage) { health -= damage; }
	float GetHealth() { return health; }

	// Function to move attacker along path
	void Move(float delta);
	void Draw();

private:
	// Speed of the attacker, how many pixels does it move each update
	int id;
	float speed;
	float damage;
	float cooldown;
	float elapsed;
	int hitCounter = 0;
	int hitLimit;
	float money;
	bool moneyEarned = false;
	bool healthEarned = false;
	float health;
	float initHealth;
	float popTime = 0;
	int pathIndex = 1;
	Path* path;
	
	// Reference to player
	Player* player;
	// Sprite of the attacker
	CSimpleSprite* sprite;

};

#endif