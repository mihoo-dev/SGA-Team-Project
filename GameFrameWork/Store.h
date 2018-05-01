#pragma once
#include "gameNode.h"
#include "PotionItem.h"
#include "ArmorItem.h"
#include "StarPoint.h"
#include "Sword.h"
#include "StoreNPC.h"
class Store : public gameNode
{
private:
	Item* _potion;
	Item* _armor;
	Item* _starPoint;
	Item* _sword;

	StoreNPC* _NPC;

public:
	Store();
	~Store();

	HRESULT init();
	void update();
	void release();
	void render();

	void FontFunction(int r, int g, int b, const char* txt, float rcX, float rcY);
};

