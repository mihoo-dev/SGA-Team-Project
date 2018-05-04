#pragma once
#include "singletonBase.h"

class WorldXY : public singletonBase<WorldXY>
{
private:
	float _worldX;
	float _worldY;
public:
	WorldXY();
	~WorldXY();

	float GetWorldX() { return _worldX; }
	float GetWorldY() { return _worldY; }
	void SetWorldX(float x) { _worldX = x; }
	void SetWorldY(float y) { _worldY = y; }
};

