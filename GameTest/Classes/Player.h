#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player
{
public:
	Player();
	float GetHealth() { return health; }
	void Hit(float damage);
	void Spend(float amount) { money -= amount; }
	void Earn(float amount) { money += amount; }
	float GetMoney() { return money; }
	void Draw();
	int NextLevel();
	void Reset();

private:
	float health;
	float money;
	int level = 0;
};

#endif