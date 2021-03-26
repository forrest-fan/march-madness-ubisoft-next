#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
#include "App\\AppSettings.h"

// Player constants
#define INITIAL_MONEY 1000.0f
#define INITIAL_HEALTH 100.0f
#define PLAYER_Y ((float) APP_VIRTUAL_HEIGHT) - 50.0f
#define HEALTH_BAR_X (float) (((APP_VIRTUAL_WIDTH - 200.0f) / 2) - 200.0f)
#define HEALTH_BAR_WIDTH 400.0f
#define MONEY_X 50.0f
#define LEVEL_X 700.0f
#define LEVEL_Y 

// Level builder constants
#define ATT_SEPARATION 40.0f

// Attacker constants
#define LEVEL_INCREMENT 0.08f
#define LEVEL_INCREMENT_FREQ 5
#define BOSS_LEVEL 5
#define DEAD -1000.0f
#define ATTACKER1 0
#define BOSS 1
#define HEART 2
#define HEART_CHANCE 3

// Defender IDs and stats
#define CADE 0
#define CADE_SPRITE ".\\TestData\\cade.bmp"
#define CADE_2PT_RANGE 120.0f
#define CADE_3PT_RANGE 160.0f
#define CADE_2PT_PCT 50
#define CADE_3PT_PCT 45
#define CADE_COST 600
#define CADE_COOLDOWN 600.0f
#define CADE_SPLASH_PCT 60
#define CADE_AND1_PCT 30
#define CADE_DAMAGE 10.0f
#define HUNTER 1
#define HUNTER_SPRITE ".\\TestData\\hunter.bmp"
#define HUNTER_2PT_RANGE 60.0f
#define HUNTER_3PT_RANGE 80.0f
#define HUNTER_2PT_PCT 80
#define HUNTER_3PT_PCT 20
#define HUNTER_COST 400
#define HUNTER_COOLDOWN 300.0f
#define HUNTER_SPLASH_PCT 20
#define HUNTER_AND1_PCT 70
#define HUNTER_DAMAGE 10.0f
#define LUKA 2
#define LUKA_SPRITE ".\\TestData\\luka.bmp"
#define LUKA_2PT_RANGE 100.0f
#define LUKA_3PT_RANGE 150.0f
#define LUKA_2PT_PCT 70
#define LUKA_3PT_PCT 40
#define LUKA_COST 500
#define LUKA_COOLDOWN 400.0f
#define LUKA_SPLASH_PCT 50
#define LUKA_AND1_PCT 50
#define LUKA_DAMAGE 10.0f
#define JARED 3
#define JARED_SPRITE ".\\TestData\\jared.bmp"
#define JARED_2PT_RANGE 120.0f
#define JARED_3PT_RANGE 200.0f
#define JARED_2PT_PCT 60
#define JARED_3PT_PCT 40
#define JARED_COST 600
#define JARED_COOLDOWN 500.0f
#define JARED_SPLASH_PCT 70
#define JARED_AND1_PCT 20
#define JARED_DAMAGE 10.0f

// Game states IDs
#define IDLE 0
#define ATTACK 1
#define GAMEOVER 4

// Hit Result IDs
#define BRICK 0
#define NORMAL 1
#define SPLASH 2
#define SPLASH_RANGE 50.0f
#define AND1 3

// Ball speed factor (lower is faster)
#define FACTOR 20.0f

// Interface coordinates
#define SIDEBAR_SPRITES_GAP 150.0f
#define READY_BUTTON_X1 884.0f
#define READY_BUTTON_X2 964.0f
#define READY_BUTTON_Y1 653.0f
#define READY_BUTTON_Y2 693.0f
#define READY_BUTTON_TEXT_X 894.0f
#define READY_BUTTON_TEXT_Y 668.0f
#define VERTICAL_DIVIDER_X 824.0f
#define DEF_HOVER_X1 900.0f
#define DEF_HOVER_X2 950.0f
#define DEF_HOVER_Y1 520.0f
#define DEF_HOVER_Y2 620.0f
#define HOVER_STATS_X1 600.0f
#define HOVER_STATS_X2 800.0f
#define HOVER_STATS_Y 450.0f
#define POPUP_X 50.0f
#define POPUP_Y ((float) APP_VIRTUAL_HEIGHT) - 100.0f
#define POPUP_TIME 1500.0f
#define AGAIN_X1 APP_VIRTUAL_WIDTH / 2.0f - 75.0f
#define AGAIN_X2 APP_VIRTUAL_WIDTH / 2.0f + 75.0f
#define AGAIN_Y1 APP_VIRTUAL_HEIGHT / 2.0f - 40.0f
#define AGAIN_Y2 APP_VIRTUAL_HEIGHT / 2.0f - 80.0f
#endif
