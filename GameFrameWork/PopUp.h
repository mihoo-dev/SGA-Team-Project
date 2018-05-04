#pragma once
#include "singletonBase.h"
#include <vector>

class PopUp : public singletonBase<PopUp>
{
private:
    typedef struct tagPopUp
    {
        float x, y;
        string str;
        bool inUse;
        float jumpPower;
        float gravity;

        tagPopUp() : x(0), y(0), str(""), inUse(false), jumpPower(3), gravity(0.3f)
        {}
        tagPopUp(float _x, float _y, string _str, bool _inUse)
            : x(_x), y(_y), str(_str), inUse(_inUse), jumpPower(3), gravity(0.3f)
        {}
    }PopUps;
    
    vector<PopUps>   _vPopUp;
public:
    PopUp();
    ~PopUp();

    HRESULT init();
    void release();
    void update();
    void render(HDC hdc);

    void Move();
    void Fire(float x, float y, string str);
};

