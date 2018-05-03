#pragma once
#include "gameNode.h"
#include "PotionItem.h"
#include "ArmorItem.h"
#include "StarPoint.h"
#include "Sword.h"
#include "HotSauce.h"
#include "StoreNPC.h"
#include "PlayerManager.h"
#include "PurchaseBtn.h"
class Store : public gameNode
{
private:
	PlayerManager* _pm;

	image* img;

	Item* _potion;
	Item* _hotsauce;
	//Item* _armor;
	Item* _starPoint;
	Item* _sword;

	StoreNPC* _NPC;

	RECT _rc[4];

	PurchaseBtn* _btn;
	PurchaseBtn* _btn2;
	PurchaseBtn* _btn3;
	PurchaseBtn* _btn4;

public:
	Store();
	~Store();

	HRESULT init();
	void update();
	void release();
	void render();

	void FontFunction(int r, int g, int b, const char* txt, float rcX, float rcY);
	void checkCollision();
	PurchaseBtn* getBtn(int i);
};

