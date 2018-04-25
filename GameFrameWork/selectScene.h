#pragma once
#include "gameNode.h"
#include "button.h"
#include "action.h"

class selectScene : public gameNode
{
private:
	button* _btnSceneChange;

	action* _action;
	image* _actionImage;

public:
	selectScene();
	~selectScene();

	HRESULT init();
	void release();
	void update();
	void render();

	static void cbSceneChange();
};

