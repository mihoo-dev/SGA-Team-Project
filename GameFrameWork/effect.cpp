#include "stdafx.h"
#include "effect.h"
#include "animation.h"

effect::effect()
	: _effectImage(NULL),
	_effectAnimation(NULL),
	_isRunning(false), _x(0), _y(0)
{
}


effect::~effect()
{
}

HRESULT effect::init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime)
{
	//이미지가 없다면 실패처리
	if (!effectImage) return E_FAIL;

	_isRunning = false;
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;

	if (!_effectAnimation) _effectAnimation = new animation;

	_effectAnimation->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAnimation->setDefPlayFrame(false, false);
	_effectAnimation->setFPS(fps);
	_effectAnimation->stop();


	return S_OK;
}

void effect::release()
{
	_effectImage = NULL;
	SAFE_DELETE(_effectAnimation);
}

void effect::update() 
{
	//실행중이지 않다면 돌아가거라
	if (!_isRunning) return;
	//여기까지 프로세스가 왔다면 실행중이니 실행
	_effectAnimation->frameUpdate(_elapsedTime);

	if (!_effectAnimation->isPlay()) killEffect();
}

void effect::render() 
{
	if (!_isRunning) return;

	_effectImage->aniRender(getMemDC(), _x, _y, _effectAnimation);
}


void effect::startEffect(int x, int y)
{
	if (!_effectAnimation || !_effectImage) return;

	//중점으로 보정한다
	_x = x - (_effectAnimation->getFrameWidth() / 2);
	_y = y - (_effectAnimation->getFrameHeight() / 2);

	_isRunning = true;
	_effectAnimation->start();
}


void effect::killEffect()
{
	_isRunning = false;
}
