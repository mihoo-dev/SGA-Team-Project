#pragma once
#include "gameNode.h"
class Object :
    public gameNode
{
protected:
    image * _img;           //이미지

    string _imgName;        //이미지 이름

    float _x, _y;           //좌표
    RECT _rc;               //RECT

    bool _inUse;            //사용중인지
    bool _isCollided;       //충돌여부

    int _frameX;
    float _frameCount;
public:
    Object();
    ~Object();

    virtual HRESULT init(float x, float y);
    virtual void release();
    virtual void update();
    virtual void render();

    bool Animate();
    void Collision(RECT rc);
    inline bool GetInUse() { return _inUse; }
};

