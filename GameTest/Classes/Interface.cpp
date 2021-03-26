#include "stdafx.h"
#include "Interface.h"
#include "..\\Constants.h"

float buttonX[4] = { READY_BUTTON_X1, READY_BUTTON_X1, READY_BUTTON_X2, READY_BUTTON_X2 };
float buttonY[4] = { READY_BUTTON_Y1, READY_BUTTON_Y2, READY_BUTTON_Y2, READY_BUTTON_Y1 };

Interface::Interface(float windowW, float windowH, int* state) {
	width = windowW;
	height = windowH;
	gameState = state;
	defenders[0] = App::CreateSprite(CADE_SPRITE, 1, 1);
	defenders[1] = App::CreateSprite(HUNTER_SPRITE, 1, 1);
	defenders[2] = App::CreateSprite(LUKA_SPRITE, 1, 1);
	defenders[3] = App::CreateSprite(JARED_SPRITE, 1, 1);
	for (int i = 0; i < 4; i++) {
		defenders[i]->SetScale(2.0f);
		defenders[i]->SetPosition(width - 100.0f, height - 200.0f - (i * SIDEBAR_SPRITES_GAP));
	}
	court = App::CreateSprite(".\\TestData\\bg.bmp", 1, 1);
	court->SetPosition(300.0f, 500.0f);
}

void Interface::Update(float delta) {
	if (noMoneyPopup) {
		popupTimer += delta;
		if (popupTimer >= POPUP_TIME) {
			noMoneyPopup = false;
		}
	}
}

void Interface::Draw() {
	if (*gameState != GAMEOVER) {
		// MM court background
		court->Draw();

		// Side menu
		for (int i = (int)VERTICAL_DIVIDER_X; i <= (int)APP_VIRTUAL_WIDTH; i++) {
			App::DrawLine(i, height, i, 0.0f, 51.0f / 255.0f, 153.0f / 255.0f, 1.0f); // Sidebar background
		}
		App::Print(width - 125.0f, height - 30.0f, "MENU");

		if (state == 0) {
			// Ready button
			for (int i = 0; i < 4; i++) {
				App::DrawLine(buttonX[i], buttonY[i], buttonX[(i + 1) % 4], buttonY[(i + 1) % 4]);
			}
			App::Print(READY_BUTTON_TEXT_X, READY_BUTTON_TEXT_Y, "READY");

			// Defenders
			for (int i = 0; i < 4; i++) {
				defenders[i]->Draw();
			}

			if (hoverState > 0) {
				for (int i = 0; i < 300; i++) {
					App::DrawLine(HOVER_STATS_X1, HOVER_STATS_Y + i, HOVER_STATS_X2, HOVER_STATS_Y + i);
				}
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 200.0f, "2Pt %", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_10);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 200.0f, "3Pt %", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_10);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 150.0f, "2Pt Range", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_10);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 150.0f, "3Pt Range", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_10);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 100.0f, "Splash %", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_10);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 100.0f, "And-1 %", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_10);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 50.0f, "Damage", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_10);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 50.0f, "Cooldown", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_10);
				App::Print(HOVER_STATS_X1 + 75.0f, HOVER_STATS_Y + 10.0f, "Cost", 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_12);
				
			}
			switch (hoverState) {
			case 1:
				App::Print(610.0f, HOVER_STATS_Y + 270.0f, "CADE CUNNINGHAM", 222.0f / 255.0f, 96.0f / 255.0f, 0.0f / 255.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 220.0f, &std::to_string(CADE_2PT_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 220.0f, &std::to_string(CADE_3PT_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 170.0f, &std::to_string((int) CADE_2PT_RANGE)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 170.0f, &std::to_string((int) CADE_3PT_RANGE)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 120.0f, &std::to_string(CADE_SPLASH_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 120.0f, &std::to_string(CADE_AND1_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 70.0f, &std::to_string((int)CADE_DAMAGE)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 70.0f, &std::to_string((int)CADE_COOLDOWN)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 10.0f, &std::to_string((int)CADE_COST)[0], 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_12);
				break;
			case 2:
				App::Print(610.0f, HOVER_STATS_Y + 270.0f, "HUNTER DICKINSON", 27.0f / 255.0f, 42.0f / 255.0f, 87.0f / 255.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 220.0f, &std::to_string(HUNTER_2PT_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 220.0f, &std::to_string(HUNTER_3PT_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 170.0f, &std::to_string((int)HUNTER_2PT_RANGE)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 170.0f, &std::to_string((int)HUNTER_3PT_RANGE)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 120.0f, &std::to_string(HUNTER_SPLASH_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 120.0f, &std::to_string(HUNTER_AND1_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 70.0f, &std::to_string((int)HUNTER_DAMAGE)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 70.0f, &std::to_string((int)HUNTER_COOLDOWN)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 10.0f, &std::to_string((int)HUNTER_COST)[0], 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_12);
				break;
			case 3:
				App::Print(640.0f, HOVER_STATS_Y + 270.0f, "LUKA GARZA", 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 220.0f, &std::to_string(LUKA_2PT_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 220.0f, &std::to_string(LUKA_3PT_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 170.0f, &std::to_string((int)LUKA_2PT_RANGE)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 170.0f, &std::to_string((int)LUKA_3PT_RANGE)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 120.0f, &std::to_string(LUKA_SPLASH_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 120.0f, &std::to_string(LUKA_AND1_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 70.0f, &std::to_string((int)LUKA_DAMAGE)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 70.0f, &std::to_string((int)LUKA_COOLDOWN)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 10.0f, &std::to_string((int)LUKA_COST)[0], 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_12);
				break;
			case 4:
				App::Print(635.0f, HOVER_STATS_Y + 270.0f, "JARED BUTLER", 26.0f / 255.0f, 112.0f / 255.0f, 33.0f / 255.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 220.0f, &std::to_string(JARED_2PT_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 220.0f, &std::to_string(JARED_3PT_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 170.0f, &std::to_string((int)JARED_2PT_RANGE)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 170.0f, &std::to_string((int)JARED_3PT_RANGE)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 120.0f, &std::to_string(JARED_SPLASH_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 120.0f, &std::to_string(JARED_AND1_PCT)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 10.0f, HOVER_STATS_Y + 70.0f, &std::to_string((int)JARED_DAMAGE)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 70.0f, &std::to_string((int)JARED_COOLDOWN)[0], 0.0f, 0.0f, 0.0f);
				App::Print(HOVER_STATS_X1 + 110.0f, HOVER_STATS_Y + 10.0f, &std::to_string((int)JARED_COST)[0], 0.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_12);
				break;
			}
		}
		else {
			// Print instructions and disable menu
			App::Print(850.0f, 380.0f, "USE ARROW KEYS");
			App::Print(830.0f, 350.0f, "TO MOVE DEFENDER");

			App::Print(850.0f, 300.0f, "PRESS ENTER TO");
			App::Print(880.0f, 270.0f, "CONFIRM");
		}

		// Popup for insufficient funds scenario
		if (noMoneyPopup && popupTimer < POPUP_TIME) {
			App::Print(POPUP_X, POPUP_Y, "You don't have enough", 1.0f, 0.0f, 0.0f);
			App::Print(POPUP_X, POPUP_Y - 30, "money to afford this", 1.0f, 0.0f, 0.0f);
		}
	}
	else {
		App::Print(width / 2 - 50.0f, height / 2, "GAME OVER!");
		for (int i = 0; i < 40; i++) {
			App::DrawLine(width / 2.0f - 75.0f, height / 2.0f - 40.0f - i, width / 2.0f + 75.0f, height / 2.0f - 40.0f - i);
		}
		App::Print(width / 2 - 50.0f, height / 2 - 70.0f, "PLAY AGAIN", 0.0f, 0.0f, 0.0f);
	}
	
}

void Interface::NoMoney() {
	noMoneyPopup = true;
	popupTimer = 0;
}

Interface::~Interface() {
	// Clear memory allocated for the 4 sprites
	for (int i = 0; i < 4; i++) {
		delete defenders[i];
	}
}