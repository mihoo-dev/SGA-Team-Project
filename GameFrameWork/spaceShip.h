#pragma once
#include "gameNode.h"
#include "bullets.h"
#include "progressBar.h"

//클래스 전방선언
//헤더파일 무한루프를 빠져나오기 위한 방편이기도 하지만
//실제 컴파일 속도가 엄청 빨라지므로 실무에선 좀 남발함
class enemyManager;

class spaceShip : public gameNode
{
private:
	image* _ship;
	missile* _missile;
	piccolo* _piccolo;

	enemyManager* _em;

	progressBar* _hpBar;

	float _currentHP, _maxHP;

	int _alphaValue;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void collision(void);

	void hitDamage(float damage);

	image* getShipImage() { return _ship; }
	
	//실제로 피콜로 미사일에 대한 접근자
	piccolo* getPiccoloMissile() { return _piccolo; }

	void setEmMemoryAddressLink(enemyManager* em) { _em = em; }

	spaceShip();
	~spaceShip();
};

