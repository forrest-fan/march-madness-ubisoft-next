#include "stdafx.h"
#include "stdlib.h"
#include "math.h"
#include <windows.h>
#include "Defender.h"
#include "..\\App\\app.h"

Defender::Defender(int defId, float startX, float startY, Player* thePlayer) {
	if (defId == CADE) {
		sprite = App::CreateSprite(CADE_SPRITE, 1, 1);
		range2 = CADE_2PT_RANGE;
		range3 = CADE_3PT_RANGE;
		pct2 = CADE_2PT_PCT;
		pct3 = CADE_3PT_PCT;
		cost = CADE_COST;
		cooldown = CADE_COOLDOWN;
		splashRate = CADE_SPLASH_PCT;
		and1Rate = CADE_AND1_PCT;
		damage = CADE_DAMAGE;
	} else if (defId == HUNTER) {
		sprite = App::CreateSprite(HUNTER_SPRITE, 1, 1);
		range2 = HUNTER_2PT_RANGE;
		range3 = HUNTER_3PT_RANGE;
		pct2 = HUNTER_2PT_PCT;
		pct3 = HUNTER_3PT_PCT;
		cost = HUNTER_COST;
		cooldown = HUNTER_COOLDOWN;
		splashRate = HUNTER_SPLASH_PCT;
		and1Rate = HUNTER_AND1_PCT;
		damage = HUNTER_DAMAGE;
	}
	else if (defId == LUKA) {
		sprite = App::CreateSprite(LUKA_SPRITE, 1, 1);
		range2 = LUKA_2PT_RANGE;
		range3 = LUKA_3PT_RANGE;
		pct2 = LUKA_2PT_PCT;
		pct3 = LUKA_3PT_PCT;
		cost = LUKA_COST;
		cooldown = LUKA_COOLDOWN;
		splashRate = LUKA_SPLASH_PCT;
		and1Rate = LUKA_AND1_PCT;
		damage = LUKA_DAMAGE;
	}
	else if (defId == JARED) {
		sprite = App::CreateSprite(JARED_SPRITE, 1, 1);
		range2 = JARED_2PT_RANGE;
		range3 = JARED_3PT_RANGE;
		pct2 = JARED_2PT_PCT;
		pct3 = JARED_3PT_PCT;
		cost = JARED_COST;
		cooldown = JARED_COOLDOWN;
		splashRate = JARED_SPLASH_PCT;
		and1Rate = JARED_AND1_PCT;
		damage = JARED_DAMAGE;
	}
	elapsed = cooldown;
	sprite->SetPosition(startX, startY);
	sprite->SetScale(1.7f);
	player = thePlayer;
	player->Spend(cost);
}
/// <summary>
/// This method shoots balls at the attackers if it's in range. Based on the defender's stats, the shot will either be a hit, a miss, a splash, or an And-1
/// </summary>
/// <param name="target">The array of attackers to shoot at - The defender will always aim for the first one in range that hasn't been hit</param>
/// <param name="delta">The time since last update - used to implement cooldown between shots</param>
/// <param name="length">The length of the attackers array</param>
void Defender::Shoot(std::vector<Attacker *> targets, float delta, int length) {
	elapsed += delta;

	// Delete balls that have finished the sequence
	auto ball = activeBalls.begin();
	while (ball != activeBalls.end()) {
		if (ball->Move(delta) == 1) {
			ball = activeBalls.erase(ball);
		}
		else {
			ball++;
		}
	}

	// Shoot ball if cooldown over
	if (elapsed >= cooldown) {
		float x, y;
		sprite->GetPosition(x, y);
		for (auto target = targets.begin(); target != targets.end(); target++) {
			Attacker* thisTgt = *target;
			if (thisTgt->GetHealth() > 0) {
				float targetX, targetY;
				thisTgt->GetSprite()->GetPosition(targetX, targetY);
				double attDistance = sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
				if (attDistance <= range3) {
					// Random num 1-100
					int random = rand() % 100 + 1;
					int result = 0;
					std::vector<Attacker*> targetsHit;
					if (attDistance > range2) {
						// 3pt shot
						if (random <= pct3) {
							int splashRandom = rand() % 100 + 1;
							if (splashRandom <= splashRate) {
								// Splash
								result = 2;
								targetsHit.push_back(thisTgt);
								for (auto splashTgt = targets.begin(); splashTgt != targets.end(); splashTgt++) {
									float splashX, splashY;
									Attacker* splash = *splashTgt;
									splash->GetSprite()->GetPosition(splashX, splashY);
									double splashDist = sqrt(pow(targetX - splashX, 2) + pow(targetY - splashY, 2));
									if (splashDist <= SPLASH_RANGE && splash != thisTgt) {
										targetsHit.push_back(splash);
									}
								}
							}
							else {
								// normal
								result = 1;
								targetsHit.push_back(thisTgt);
							}
						}
					}
					else {
						// 2pt shot
						if (random <= pct2) {
							int and1Random = rand() % 100 + 1;
							if (and1Random <= and1Rate) {
								// And 1!
								result = 3;
								targetsHit.push_back(thisTgt);
								for (auto splashTgt = targets.begin(); splashTgt != targets.end(); splashTgt++) {
									float splashX, splashY;
									Attacker* splash = *splashTgt;
									splash->GetSprite()->GetPosition(splashX, splashY);
									double splashDist = sqrt(pow(targetX - splashX, 2) + pow(targetY - splashY, 2));
									if (splashDist <= range2 && splash != thisTgt) {
										targetsHit.push_back(splash);
									}
								}
							}
						}
					}

					if (result > 0) {
						// update state of attacker
						//thisTgt->SetState(2);
					}
					activeBalls.emplace_back(x, y, targetX, targetY, damage, targetsHit, result);
					elapsed = 0;
					break;
				}
			}
		}
	}
}

void Defender::Draw() {
	float x, y;
	sprite->GetPosition(x, y);

	// Draw the range if selected
	if (selected) {
		// Draw lines in a circle around defender
		for (int i = 0; i < 360; i += 2) {
			App::DrawLine(x, y, (x + range3 * cos(i * PI / 180)), (y + range3 * sin(i * PI / 180)), 144.0f / 255.0f, 226.0f / 255.0f, 245.0f / 255.0f); // 3pt range
			App::DrawLine(x, y, (x + range2 * cos(i * PI / 180)), (y + range2 * sin(i * PI / 180)), 245.0f / 255.0f, 159.0f / 255.0f, 144.0f / 255.0f); // 2pt range
		}
	}

	sprite->Draw(); // Draw the defender sprite

	// Draw any balls that are being shot
	for (auto i = activeBalls.begin(); i != activeBalls.end(); i++) {
		i->GetSprite()->Draw();
	}
}

Defender::~Defender() {
	// Clear memory allocated for balls
	std::vector<Ball>().swap(activeBalls);
	// Clear memory allocated for the sprite
	delete sprite;
}