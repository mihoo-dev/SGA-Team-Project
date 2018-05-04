#include "stdafx.h"
#include "PopUp.h"


PopUp::PopUp()
{
}


PopUp::~PopUp()
{
}

HRESULT PopUp::init()
{
    for (int i = 0; i < 10; i++)
    {
        PopUps popUp = PopUps();

        _vPopUp.push_back(popUp);
    }
    return S_OK;
}

void PopUp::release()
{
    _vPopUp.clear();
}

void PopUp::update()
{
    Move();
}

void PopUp::render(HDC hdc)
{
    for (int i = 0; i < _vPopUp.size(); i++)
    {
        if (!_vPopUp[i].inUse) continue;

        HFONT hFont = CreateFont(20, 0, 0, 0, 100, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, "±Ã¼­Ã¼");
        HFONT hOFont = (HFONT)SelectObject(hdc, hFont);
        SetTextColor(hdc, RGB(255, 0, 0));
        TextOut(hdc, _vPopUp[i].x, _vPopUp[i].y, _vPopUp[i].str.c_str(), _vPopUp[i].str.size());
        SetTextColor(hdc, RGB(0, 0, 0));
        SelectObject(hdc, hOFont);
        DeleteObject(hFont);
    }
}

void PopUp::Move()
{
    for (int i = 0; i < _vPopUp.size(); i++)
    {
        if (!_vPopUp[i].inUse) continue;

        _vPopUp[i].y -= _vPopUp[i].jumpPower;
        _vPopUp[i].jumpPower -= _vPopUp[i].gravity;

        if (_vPopUp[i].jumpPower <= 0)
            _vPopUp[i] = PopUps();
    }
}

void PopUp::Fire(float x, float y, string str)
{
    for (int i = 0; i < _vPopUp.size(); i++)
    {
        if (_vPopUp[i].inUse) continue;

        _vPopUp[i] = PopUps(x, y, str, true);
    }
}
