#pragma once
#include "singletonBase.h"

class WorldXY : public singletonBase<WorldXY>
{
private:
	float	_worldX;
	float	_worldY;
	BOOL	_canMakeBridge;
	BOOL	_meetDog;
public:
	WorldXY();
	~WorldXY();

	float GetWorldX() { return _worldX; }
	float GetWorldY() { return _worldY; }
	BOOL GetCanMakeBridge() { return _canMakeBridge; }
	BOOL GetMeetDog() { return _meetDog; }

	void SetWorldX(float x) { _worldX = x; }
	void SetWorldY(float y) { _worldY = y; }
	void SetCanMakeBridge(BOOL can) { _canMakeBridge = can; }
	void SetMeetDog(BOOL dog) { _meetDog = dog; }


};

