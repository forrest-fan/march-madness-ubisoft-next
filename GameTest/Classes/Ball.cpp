#include "stdafx.h"
#include "math.h"
#include "Ball.h"
#include "..\\App\\app.h"

Ball::Ball(float startX, float startY, float destX, float destY, float damageDealt, std::vector<Attacker*> attsHit, int shotResult) {
	destinationX = destX;
	destinationY = destY;
	distX = abs(destX - startX);
	distY = abs(destY - startY);
	damage = damageDealt;
	sprite = App::CreateSprite(".\\TestData\\ball.bmp", 8, 3);
	sprite->CreateAnimation(0, 1.0f/15.0f, { 0, 1, 2, 3, 4, 5, 6, 7 });
	// Create animation 1 to handle different hit results
	result = shotResult;
	switch (result) {
	case BRICK:
		sprite->CreateAnimation(1, 0.15f, { 8, 9, 10, 11 });
		break;
	case NORMAL:
		sprite->CreateAnimation(1, 1.0f / 15.0f, { 0, 1, 2, 3, 4, 5, 6, 7 });
		break;
	case SPLASH:
		sprite->CreateAnimation(1, 0.15f, { 12, 13, 14, 15 });
		break;
	case AND1:
		sprite->CreateAnimation(1, 0.15, { 16, 17, 18, 19, 20, 21 });
		break;
	}
	sprite->SetPosition(startX, startY);
	sprite->SetScale(0.7f);
	animTimer = 0.0f;
	hit = attsHit;
	state = 0;
}

int Ball::Move(float delta) {
	sprite->Update(delta);
	if (state == 0) {
		sprite->SetAnimation(0);
		float x, y;
		sprite->GetPosition(x, y);

		if (x < destinationX - 15.0f) {
			x += distX / FACTOR;
		}
		else if (x > destinationX + 15.0f) {
			x -= distX / FACTOR;
		}

		if (y < destinationY - 15.0f) {
			y += distY / FACTOR;
		}
		else if (y > destinationY - 15.0f) {
			y -= distY / FACTOR;
		}

		sprite->SetPosition(x, y);
		
		
		if (abs(x - destinationX) <= 15.0f && abs(y - destinationY) <= 15.0f) {
			sprite->SetAnimation(1);
			state = 2;
			if (result > BRICK) {
				for (auto att = hit.begin(); att != hit.end(); att++) {
					Attacker* thisAtt = *att;
					thisAtt->Hit(damage);
				}
			}
		}
	}
	else if (state == 2) {
		if (animTimer > 600.0f) {
			state = 1;
		}
		animTimer += delta;
	}
	return state;
}