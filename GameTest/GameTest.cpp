#include "stdafx.h"
#include <windows.h> 
#include <math.h>  
#include <ctime>
#include <cstdlib>
#include "app\app.h"
#include ".\\Classes\\Attacker.h"
#include ".\\Classes\\Defender.h"
#include ".\\Classes\\Interface.h"
#include ".\\Classes\\Player.h"
#include ".\\Classes\\LevelBuilder.h"
#include ".\\Classes\\Path.h"
#include ".\\Constants.h"

std::vector<Attacker *> atts;
std::vector<Defender *> defs;
Defender* selected;
Interface* ui;
Player* player;
LevelBuilder* builder;
Path* path;
int gameState = IDLE;
bool addingDef = false;

//float pathX[5] = { 100.0f, 100.0f, 800.0f, 800.0f, 600.0f };
//float pathY[5] = { 0.0f, 200.0f, 200.0f, 500.0f, 500.0f };
float pathX[5] = { 100.0f, 400.0f, 800.0f, 800.0f, 600.0f };
float pathY[5] = { 0.0f, 200.0f, 400.0f, 800.0f, 500.0f };
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	srand((unsigned int)time(NULL));
	ui = new Interface((float) APP_VIRTUAL_WIDTH, (float) APP_VIRTUAL_HEIGHT, &gameState); //remove &game state if not used
	player = new Player();
	path = new Path(&pathX[0], &pathY[0], 5);
	builder = new LevelBuilder(&atts, player, path);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	if (player->GetHealth() > 0) {
		if (gameState == IDLE) {
			float mouseX, mouseY;
			App::GetMousePos(mouseX, mouseY);

			// Update UI
			ui->Update(deltaTime);

			// Check if hovering over defenders on sidebar, if so, call hover function
			if (mouseX >= DEF_HOVER_X1 && mouseX <= DEF_HOVER_X2 && mouseY >= DEF_HOVER_Y1 - CADE * SIDEBAR_SPRITES_GAP && mouseY <= DEF_HOVER_Y2 - CADE * SIDEBAR_SPRITES_GAP) {
				ui->Hover(CADE + 1);
			}
			else if (mouseX >= DEF_HOVER_X1 && mouseX <= DEF_HOVER_X2 && mouseY >= DEF_HOVER_Y1 - HUNTER * SIDEBAR_SPRITES_GAP && mouseY <= DEF_HOVER_Y2 - HUNTER * SIDEBAR_SPRITES_GAP) {
				ui->Hover(HUNTER + 1);
			}
			else if (mouseX >= DEF_HOVER_X1 && mouseX <= DEF_HOVER_X2 && mouseY >= DEF_HOVER_Y1 - LUKA * SIDEBAR_SPRITES_GAP && mouseY <= DEF_HOVER_Y2 - LUKA * SIDEBAR_SPRITES_GAP) {
				ui->Hover(LUKA + 1);
			}
			else if (mouseX >= DEF_HOVER_X1 && mouseX <= DEF_HOVER_X2 && mouseY >= DEF_HOVER_Y1 - JARED * SIDEBAR_SPRITES_GAP && mouseY <= DEF_HOVER_Y2 - JARED * SIDEBAR_SPRITES_GAP) {
				ui->Hover(JARED + 1);
			}
			else {
				ui->Hover(0);
			}

			if (addingDef) {
				ui->DisableMenu();
				float x, y;
				selected->GetSprite()->GetPosition(x, y);
				// Update new defender location using arrow keys
				if (App::IsKeyPressed(VK_LEFT)) {
					selected->GetSprite()->SetPosition(x - 5.0f, y);
				}
				if (App::IsKeyPressed(VK_RIGHT)) {
					selected->GetSprite()->SetPosition(x + 5.0f, y);
				}
				if (App::IsKeyPressed(VK_UP)) {
					selected->GetSprite()->SetPosition(x, y + 5.0f);
				}
				if (App::IsKeyPressed(VK_DOWN)) {
					selected->GetSprite()->SetPosition(x, y - 5.0f);
				}

				// Press enter to confirm position
				if (App::IsKeyPressed(VK_RETURN)) {
					addingDef = false;
					ui->EnableMenu();
					for (auto def = defs.begin(); def != defs.end(); def++) {
						Defender* thisDef = *def;
						thisDef->Deselect();
					}
				}
			}

			if (App::IsKeyPressed(VK_LBUTTON)) {
				if (!addingDef) {
					if (mouseX >= READY_BUTTON_X1 && mouseX <= READY_BUTTON_X2 && mouseY >= READY_BUTTON_Y1 && mouseY <= READY_BUTTON_Y2) {
						// CLICKED READY, generate level, change game state
						/*for (int i = 0; i < 20; i++) {
							atts.push_back(new Attacker(100, 20.0f - (float)i * 40.0f, player));
						}*/
						builder->NewLevel(player->NextLevel());
						gameState = ATTACK;
					}
					else if (mouseX >= DEF_HOVER_X1 && mouseX <= DEF_HOVER_X2 && mouseY >= DEF_HOVER_Y1 - CADE * SIDEBAR_SPRITES_GAP && mouseY <= DEF_HOVER_Y2 - CADE * SIDEBAR_SPRITES_GAP) {
						if (player->GetMoney() >= 600.0f) {
							defs.push_back(new Defender(CADE, APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f, player));
							selected = defs.back();
							addingDef = true;
						}
						else {
							ui->NoMoney();
						}
					}
					else if (mouseX >= DEF_HOVER_X1 && mouseX <= DEF_HOVER_X2 && mouseY >= DEF_HOVER_Y1 - HUNTER * SIDEBAR_SPRITES_GAP && mouseY <= DEF_HOVER_Y2 - HUNTER * SIDEBAR_SPRITES_GAP) {
						if (player->GetMoney() >= 400.0f) {
							defs.push_back(new Defender(HUNTER, APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f, player));
							selected = defs.back();
							addingDef = true;
						}
						else {
							ui->NoMoney();
						}
					}
					else if (mouseX >= DEF_HOVER_X1 && mouseX <= DEF_HOVER_X2 && mouseY >= DEF_HOVER_Y1 - LUKA * SIDEBAR_SPRITES_GAP && mouseY <= DEF_HOVER_Y2 - LUKA * SIDEBAR_SPRITES_GAP) {
						if (player->GetMoney() >= 500.0f) {
							defs.push_back(new Defender(LUKA, APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f, player));
							selected = defs.back();
							addingDef = true;
						}
						else {
							ui->NoMoney();
						}
					}
					else if (mouseX >= DEF_HOVER_X1 && mouseX <= DEF_HOVER_X2 && mouseY >= DEF_HOVER_Y1 - JARED * SIDEBAR_SPRITES_GAP && mouseY <= DEF_HOVER_Y2 - JARED * SIDEBAR_SPRITES_GAP) {
						if (player->GetMoney() >= 600.0f) {
							defs.push_back(new Defender(JARED, APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f, player));
							selected = defs.back();
							addingDef = true;
						}
						else {
							ui->NoMoney();
						}
					}

					for (auto def = defs.begin(); def != defs.end(); def++) {
						Defender* thisDef = *def;
						float defX, defY;
						thisDef->GetSprite()->GetPosition(defX, defY);
						if (mouseX >= defX - 20.0f && mouseX <= defX + 20.0f && mouseY >= defY - 60.0f && mouseY <= defY + 60.0f) {
							thisDef->Select();
							selected = thisDef;
							addingDef = true;
						}
					}
				}
			}
		}
		else if (gameState == ATTACK) {
			if (atts.size() > 0) {
				auto att = atts.begin();
				while (att != atts.end()) {
					Attacker* thisAtt = *att;
					if (thisAtt->GetHealth() == DEAD) {
						att = atts.erase(att);
					}
					else {
						thisAtt->Move(deltaTime);
						att++;
					}
				}
			}
			else {
				gameState = IDLE;
			}
		}
		for (auto def = defs.begin(); def != defs.end(); def++) {
			Defender* thisDef = *def;
			thisDef->Shoot(atts, deltaTime, atts.size());
		}
	}
	else {
		gameState = GAMEOVER;
		if (App::IsKeyPressed(VK_LBUTTON)) {
			float mouseX, mouseY;
			App::GetMousePos(mouseX, mouseY);
			if (mouseX >= AGAIN_X1 && mouseX <= AGAIN_X2 && mouseY <= AGAIN_Y1 && mouseY >= AGAIN_Y2) {
				// Clicked play again button
				// Delete existing defenders
				for (auto def = defs.begin(); def != defs.end(); def++) {
					delete* def;
				}
				defs.clear();
				// Delete existing attackers
				for (auto att = atts.begin(); att != atts.end(); att++) {
					delete* att;
				}
				atts.clear();
				// Reset Player class
				player->Reset();
				// Reset game state
				gameState = IDLE;
			}
		}
	}
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	

	ui->Draw();
	if (gameState != GAMEOVER) {
		path->Draw();
		for (auto def = defs.begin(); def != defs.end(); def++) {
			Defender* thisDef = *def;
			thisDef->Draw();
		}
		for (auto att = atts.begin(); att != atts.end(); att++) {
			Attacker* thisAtt = *att;
			thisAtt->Draw();
		}
	}
	player->Draw();
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	// Free memory from Defender vector
	for (auto def = defs.begin(); def != defs.end(); def++) {
		// Call destructor on each instance of Defender
		delete *def;
	}
	std::vector<Defender *>().swap(defs);

	// Free memory from Attacker vector
	for (auto att = atts.begin(); att != atts.end(); att++) {
		// Call destructor on each instance of Attacker
		delete* att;
	}
	std::vector<Attacker*>().swap(atts);

	// Free memory from other classes
	delete ui;
	delete player;
	delete builder;
	delete path;
}