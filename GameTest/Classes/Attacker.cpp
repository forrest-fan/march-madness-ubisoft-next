#include "stdafx.h"
#include "Attacker.h"
#include ".\\Player.h"
#include "..\\App\\SimpleSprite.h"
#include "..\\App\\app.h"
#include "..\\Constants.h"

Attacker::Attacker(int attId, float posX, float posY, int level, Player* thePlayer, Path* thePath) {
	id = attId;
	if (id == ATTACKER1) {
		// Exponential stats increase every 10 levels by 8%
		speed = 1.5f;
		damage = 2.0f;
		cooldown = 1500.0f;
		hitLimit = 3;
		health = 10.0f;
		money = (float)(rand() % 10 + 5); // Random money value of 5 - 14

		// Attacker sprite setup
		sprite = App::CreateSprite(".\\TestData\\attacker1.bmp", 4, 2);
		sprite->SetScale(0.3f);
	}
	else if (id == BOSS) {
		// Exponential stats increase every 10 levels by 8%
		speed = 0.7f;
		damage = 10.0f;
		cooldown = 1500.0f;
		hitLimit = 5;
		health = 100.0f;
		money = (float)(rand() % 150 + 50); // Random money value of 50 - 199

		// Boss sprite setup
		sprite = App::CreateSprite(".\\TestData\\boss.bmp", 4, 2);
		sprite->SetScale(0.6f);
	}
	else if (id == HEART) {
		// Exponential stats increase every 10 levels by 8%
		speed = 2.0f;
		damage = 0.0f;
		cooldown = 1500.0f;
		hitLimit = 0;
		health = 10.0f;
		money = 0.0f;

		// Boss sprite setup
		sprite = App::CreateSprite(".\\TestData\\heart.bmp", 4, 2);
		sprite->SetScale(0.5f);
	}
	initHealth = health;
	elapsed = cooldown;
	speed = speed * pow(1.0f + LEVEL_INCREMENT, floor(level / LEVEL_INCREMENT_FREQ));
	damage = damage * pow(1.0f + LEVEL_INCREMENT, floor(level / LEVEL_INCREMENT_FREQ));
	cooldown = cooldown * pow(1.0f - LEVEL_INCREMENT, floor(level / LEVEL_INCREMENT_FREQ)); // Cooldown decreases instead of increases
	health = health * pow(1.0f + LEVEL_INCREMENT, floor(level / LEVEL_INCREMENT_FREQ));
	sprite->CreateAnimation(0, 0.2f, { 0, 1, 2, 3 });
	sprite->CreateAnimation(1, 0.1f, { 4, 5, 6, 7 });
	sprite->SetPosition(posX, posY);
	player = thePlayer;
	path = thePath;
}

void Attacker::Move(float delta) {
	sprite->Update(delta);
	if (health <= 0 && health != DEAD) {
		// Only runs if dies from being hit
		if (id == HEART && !healthEarned) {
			player->Hit(-5.0f);
			healthEarned = true;
			health = DEAD;
		}
		sprite->SetAnimation(1);
		popTime += delta;
	}
	else {
		sprite->SetAnimation(0);
		if (pathIndex != path->GetLength()) {
			float x, y, z;
			sprite->GetPosition(x, y);
			float nextX = *(path->GetX() + pathIndex);
			float nextY = *(path->GetY() + pathIndex);
			z = sqrt(pow(x - nextX, 2) + pow(y - nextY, 2));
			float newX = x + (nextX - x) * speed / z;
			float newY = y + (nextY - y) * speed / z;
			sprite->SetPosition(newX, newY);
			if (abs(nextX - x) <= abs(newX - x) && abs(nextY - y) <= abs(newY - y)) {
				pathIndex += 1;
			}
		}
		else {
			if (id == HEART || hitCounter > hitLimit) {
				health = DEAD;
			}
			elapsed += delta;
			if (elapsed >= cooldown) {
				player->Hit(damage);
				hitCounter += 1;
				elapsed = 0;
			}
		}
	}
	
}

void Attacker::Draw() {
	if (popTime < 400) {
		sprite->Draw(); // Draw sprite
		// Draw healthbar
		float x, y;
		sprite->GetPosition(x, y);
		for (int i = 0; i < 3; i++) {
			App::DrawLine(x - 25.0f, y + 20.0f + i, x + 25.0f, y + 20.0f + i, 1.0f, 0.0f, 0.0f); // Damage portion
			if (health > 0) {
				// Prevents drawing green line the wrong way if health is negative
				App::DrawLine(x - 25.0f, y + 20.0f + i, x - 25.0f + 50 * (health / initHealth), y + 20.0f + i, 0.0f, 1.0f, 0.0f); // Health portion
			}
		}
		
	}
	else {
		if (!moneyEarned) {
			player->Earn(money);
			moneyEarned = true;
			health = DEAD; // Set health to -1000, can be erased
		}
	}
	
}

Attacker::~Attacker() {
	// Clear memory allocated for sprite
	delete sprite;
}