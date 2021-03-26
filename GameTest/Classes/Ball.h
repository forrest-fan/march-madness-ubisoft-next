#ifndef _BALL_H_
#define _BALL_H_

#include "..\\App\\SimpleSprite.h"
#include ".\\Attacker.h"
#include "..\\Constants.h"

class Ball
{
	// This is class for the ball that defenders shoot at attackers
public:
	Ball(float startX, float startY, float destX, float destY, float damageDealt, std::vector<Attacker*> attsHit, int shotResult);
	CSimpleSprite* GetSprite() { return sprite; }
	int Move(float delta);

private:
	float destinationX;
	float destinationY;
	float distX;
	float distY;
	float damage;
	int animTimer;
	std::vector<Attacker*> hit;
	CSimpleSprite* sprite;
	int state;
	int result;
};

#endif

