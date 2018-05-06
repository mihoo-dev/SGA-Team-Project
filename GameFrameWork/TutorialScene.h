#pragma once
#include "gameNode.h"
#include "PlayerManager.h"
#include "Bubble.h"
#include "Door.h"
#include <vector>

class TutorialScene : public gameNode
{
private:
    PlayerManager * _pm;

    int _alpha;

    vector<Object*> _vObject;
public:
    TutorialScene();
    ~TutorialScene();

    HRESULT init();
    void release();
    void update();
    void render();

	void TestText();
};

