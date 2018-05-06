#include "stdafx.h"
#include "Bubble.h"
#include "Player.h"

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

void Bubble::Collision(Player * player)
{
    if (!_isCollided)
    {
        RECT temp;
        if (IntersectRect(&temp, &_rc, &player->GetHitRC()))
        {
            POPUP->Fire(_x, _y, player->GetInfo().atk);
            SOUNDMANAGER->play("BURST", 0.3f);
            _isCollided = true;
        }
    }
}
