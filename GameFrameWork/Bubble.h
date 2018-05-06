#pragma once
#include "Object.h"

class Bubble :
    public Object
{
private:
    enum STATE {
        IDLE, POP
    };

    STATE _state;
public:
    Bubble();
    ~Bubble();

    HRESULT init(float x, float y);
    void release();
    void update();
    void render();

    void Collision(Player * player);
};

