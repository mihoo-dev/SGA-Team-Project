#include "stdafx.h"
#include "animationTest.h"


animationTest::animationTest()
{
}


animationTest::~animationTest()
{

}

HRESULT animationTest::init()
{
	_camel = IMAGEMANAGER->addFrameImage("³«Å¸", "camel.bmp", 300, 267, 4, 3, true, RGB(255, 0, 255));

	_ani1 = new animation;
	_ani1->init(_camel->getWidth(), _camel->getHeight(), _camel->getFrameWidth(), _camel->getFrameHeight());
	_ani1->setDefPlayFrame(false, true);
	_ani1->setFPS(1);


	int arrAni[] = { 5, 2, 1, 4, 3, 7 };
	_ani2 = new animation;
	_ani2->init(_camel->getWidth(), _camel->getHeight(), _camel->getFrameWidth(), _camel->getFrameHeight());
	_ani2->setPlayFrame(arrAni, 6, true);
	_ani2->setFPS(1);

	_ani3 = new animation;
	_ani3->init(_camel->getWidth(), _camel->getHeight(), _camel->getFrameWidth(), _camel->getFrameHeight());
	_ani3->setPlayFrame(2, 10, false, true);
	_ani3->setFPS(1);

	IMAGEMANAGER->addImage("explosion", "explosion.bmp", 832, 62, true, RGB(255, 0, 255));

	_effect = new effect;
	_effect->init(IMAGEMANAGER->findImage("explosion"), 32, 62, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("explosion", "explosion.bmp", 832, 62, 32, 62, 1.0f, 1.0f, 30);

	return S_OK;
}

void animationTest::release()
{

}

void animationTest::update() 
{
	if (KEYMANAGER->isOnceKeyDown('Q')) _ani1->start();
	if(KEYMANAGER->isOnceKeyDown('W'))_ani2->start();
	if(KEYMANAGER->isOnceKeyDown('E'))_ani3->start();

	_ani1->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	_ani2->frameUpdate(TIMEMANAGER->getElapsedTime() * 5);
	_ani3->frameUpdate(TIMEMANAGER->getElapsedTime() * 20);

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_effect->startEffect(_ptMouse.x, _ptMouse.y);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		//EFFECTMANAGER->play("explosion", _ptMouse.x, _ptMouse.y);
		
	}
	EFFECTMANAGER->play("explosion", RND->getFromIntTo(100, 200), RND->getFromIntTo(100, 200));

	_effect->update();
	EFFECTMANAGER->update();

}

void animationTest::render() 
{
	_camel->aniRender(getMemDC(), 100, 100, _ani1);
	_camel->aniRender(getMemDC(), 100, 200, _ani2);
	_camel->aniRender(getMemDC(), 100, 300, _ani3);

	_effect->render();
	EFFECTMANAGER->render();
}
