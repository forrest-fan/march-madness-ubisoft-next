#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include "..\\App\\app.h"
#include "..\\App\\SimpleSprite.h"

class Interface
{
public:
	Interface(float windowW, float windowH, int* state);
	~Interface();
	void Draw();
	void Hover(int hoverID) { hoverState = hoverID; }
	void DisableMenu() { state = 1; }
	void EnableMenu() { state = 0; }
	void Update(float delta);
	void NoMoney();

private:
	float width;
	float height;
	int* gameState;
	int hoverState = 0;
	int state = 0;
	bool noMoneyPopup = false;
	float popupTimer = 0;
	CSimpleSprite* defenders [4];
	CSimpleSprite* court;
};

#endif