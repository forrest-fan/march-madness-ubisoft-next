#ifndef _LEVEL_BUILDER_H
#define _LEVEL_BUILDER_H

#include <vector>
#include ".\\Attacker.h"

class LevelBuilder
{
public:
	LevelBuilder(std::vector<Attacker*>* attackers, Player* thePlayer, Path* thePath);
	void NewLevel(int level);
private:
	std::vector<Attacker*>* atts;
	Player* player;
	Path* path;
};

#endif