#include "stdafx.h"
#include "LevelBuilder.h"
#include "..\\Constants.h"

LevelBuilder::LevelBuilder(std::vector<Attacker*>* attackers, Player* thePlayer, Path* thePath) {
	atts = attackers;
	player = thePlayer;
	path = thePath;
}

void LevelBuilder::NewLevel(int level) {
	if (level % BOSS_LEVEL == 0) {
		// Boss on lvl 10, 20, 30 ...
		int numBosses = level / BOSS_LEVEL;
		int numAtts = rand() % 5 + 1; // random 1 - 5 regular attackers
		for (int i = 0; i < numBosses + numAtts; i++) {
			float x1 = *(path->GetX());
			float y1 = *(path->GetY());
			float x2 = *(path->GetX() + 1);
			float y2 = *(path->GetY() + 1);
			float z = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
			float attX = x1 - (x2 - x1) * i * ATT_SEPARATION / z; // load atts backwards
			float attY = y1 - (y2 - y1) * i * ATT_SEPARATION / z; // load atts backwards
			if (i < numBosses) {
				atts->push_back(new Attacker(BOSS, attX, attY, level, player, path));
			}
			else {
				int attId = ATTACKER1;
				if (rand() % 100 < HEART_CHANCE) {
					attId = HEART;
				}
				atts->push_back(new Attacker(attId, attX, attY, level, player, path));
			}
		}

	}
	else {
		// Generate number of attackers this level will have
		// Random number in an increasing range
		// lvl 1, 11, 21: 10 - 20
		// lvl 2, 12, 22: 12 - 24
		// Resets every 10 lvls since attackers become stronger
		int numAtts = rand() % (10 + 2 * (level % 10)) + 10 + 2 * (level % 10);
		for (int i = 0; i < numAtts; i++) {
			float x1 = *(path->GetX());
			float y1 = *(path->GetY());
			float x2 = *(path->GetX() + 1);
			float y2 = *(path->GetY() + 1);
			float z = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
			float attX = x1 - (x2 - x1) * i * ATT_SEPARATION / z; // load atts backwards
			float attY = y1 - (y2 - y1) * i * ATT_SEPARATION / z; // load atts backwards
			int attId = ATTACKER1;
			int rng = rand() % 100;
			if (rng < HEART_CHANCE) {
				attId = HEART;
			}
			atts->push_back(new Attacker(attId, attX, attY, level, player, path));
		}
	}
}