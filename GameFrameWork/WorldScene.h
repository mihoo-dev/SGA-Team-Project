#pragma once
#include "gameNode.h"

class World;

class WorldScene : public gameNode
{
private:
	World* _world;

	//페이드 화면
	int					_alpha;
	BOOL				_sceneStart;
public:
	WorldScene();
	~WorldScene();

	HRESULT init();
	void release();
	void update();
	void render();

	//씬 스타트
	void SceneStart();
};

