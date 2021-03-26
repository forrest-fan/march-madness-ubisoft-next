#include "stdafx.h"
#include "Player.h"
#include "..\\App\\app.h"
#include "..\\Constants.h"

Player::Player() {
	money = 1000.0f;
	health = 100.0f;
}

void Player::Draw() {
	// Health bar
	for (int i = 0; i < 15; i++) {
		App::DrawLine(HEALTH_BAR_X, PLAYER_Y + i, HEALTH_BAR_X + HEALTH_BAR_WIDTH, PLAYER_Y + i, 1.0f, 0.0f, 0.0f); // Damage portion, bottom layer
		App::DrawLine(HEALTH_BAR_X, PLAYER_Y + i, HEALTH_BAR_X + (HEALTH_BAR_WIDTH * health / INITIAL_HEALTH), PLAYER_Y + i, 0.0f, 1.0f, 0.0f); // Health portion, top layer
	}
	// Formatted money amount
	char moneyTxt[16] = { "$" };
	snprintf(moneyTxt + 1, sizeof(moneyTxt) - 1, "%.2f", money);
	App::Print(MONEY_X, PLAYER_Y, moneyTxt);

	// Formatted level amount
	char levelTxt[12] = { "Level " };
	snprintf(levelTxt + 6, sizeof(levelTxt) - 6, "%d", level);
	App::Print(LEVEL_X, PLAYER_Y, levelTxt);
}

int Player::NextLevel() {
	level += 1;
	return level;
}

void Player::Hit(float damage) {
	if (health - damage < 0.0f) {
		health = 0;
	}
	else if (health - damage > 100.0f) {
		health = 100;
	}
	else {
		health -= damage;
	}
}

void Player::Reset() {
	health = INITIAL_HEALTH;
	money = INITIAL_MONEY;
	level = 0;
}