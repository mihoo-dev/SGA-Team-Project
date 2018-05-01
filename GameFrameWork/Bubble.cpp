#include "stdafx.h"
#include "Bubble.h"


Bubble::Bubble()
{
}


Bubble::~Bubble()
{
}

HRESULT Bubble::init(float x, float y)
{
    Object::init(x, y);
    IMAGEMANAGER->addFrameImage("TutoBubble", "TutorialBubble.bmp", 170, 36, 5, 1, true, RGB(255, 0, 255), true);

    _img = IMAGEMANAGER->findImage("TutoBubble");
    _imgName = "TutoBubble";


    _state = IDLE;

    return S_OK;
}

void Bubble::release()
{
    Object::release();
}

void Bubble::update()
{
    Object::update();
    switch (_state)
    {
    case Bubble::IDLE:
        if (_isCollided)
            _state = Bubble::POP;
        break;
    case Bubble::POP:
        if (Object::Animate())
            _inUse = false;
        break;
    }
}

void Bubble::render()
{
    Object::render();
}
