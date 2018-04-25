#pragma once
#include "gameNode.h"

class saveLoadTest : public gameNode
{
public:
	void update();
	void save();
	void load();

	saveLoadTest();
	~saveLoadTest();
};

