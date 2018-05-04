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

	image* _priceTagImage;
	image* _priceTagImage2;
	image* _priceTagImage3;
	image* _priceTagImage4;

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
	void RenderPrice(image* img, float x, float y, int cost);
	PurchaseBtn* getBtn(int i);


    PlayerManager * GetPlayerManager() { return _pm; }
};

