#ifndef _DEFENDER_H_
#define _DEFENDER_H_

#include "..\\App\\SimpleSprite.h"
#include ".\\Attacker.h"
#include ".\\Ball.h"
#include <vector>
class Defender
{
public:
	Defender(int defId, float startX, float startY, Player* thePlayer);
	~Defender();
	CSimpleSprite* GetSprite() { return sprite; };
	void Shoot(std::vector<Attacker *> targets, float delta, int length);
	void Draw();
	void Select() { selected = true; }
	void Deselect() { selected = false; }
private:
	float range2;
	float range3;
	int pct2;
	int pct3;
	int splashRate;
	int and1Rate;
	float damage;
	float cost;
	float cooldown;
	float elapsed;
	bool selected = true;
	CSimpleSprite* sprite;
	std::vector<Ball> activeBalls;
	Player* player;
};

#endif