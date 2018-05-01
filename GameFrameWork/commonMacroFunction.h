#pragma once
//#include "../stdafx.h" 자동으로 include됨

//============================================//
//					매크로					  //	
//============================================//

//모든 함수 앞에는 안보이지만 inline이 있음
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
    MoveToEx(hdc, x1, y1, NULL);
    LineTo(hdc, x2, y2);
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
    Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleCenterMake(HDC hdc, int x, int y, int width, int height)
{
    int widthDiv2 = width / 2;
    int heightDiv2 = height / 2;

    Rectangle(hdc, x - widthDiv2, y - heightDiv2, x + widthDiv2, y + heightDiv2);
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
    Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseCenterMake(HDC hdc, int x, int y, int width, int height)
{
    int widthDiv2 = width / 2;
    int heightDiv2 = height / 2;

    Ellipse(hdc, x - widthDiv2, y - heightDiv2, x + widthDiv2, y + heightDiv2);
}

//Rect
inline RECT RectMake(int x, int y, int width, int height)
{
    RECT rc = { x, y, x + width, y + height };

    return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
    RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

    return rc;
}

//충돌

//원과 원의 충돌(RECT 이용)
inline bool CircleCollision(RECT *rc1, RECT *rc2)
{
    float x = ((rc1->right + rc1->left) / 2) - ((rc2->right + rc2->left) / 2);
    float y = ((rc1->bottom + rc1->top) / 2) - ((rc2->bottom + rc2->top) / 2);
    float r1 = (rc1->right - rc1->left) / 2;
    float r2 = (rc2->right - rc2->left) / 2;
    float d = sqrtf(x*x + y*y);

    if (d <= r1 + r2) return TRUE;
    else return FALSE;
}

//원과 원의 충돌(중점 x, y 이용)
inline bool CircleCenterCollision(float x1, float y1, float r1, float x2, float y2, float r2)
{
    float x = x1 - x2;
    float y = y1 - y2;
    float d = sqrtf(x*x + y*y);

    if (d <= r1 + r2) return TRUE;
    else return FALSE;
}

//원과 RECT의 충돌(RECT 이용)
inline bool BoxCircleCollision(RECT * circle, RECT *rc)
{
    float x = ((circle->right + circle->left) / 2) - ((rc->right + rc->left) / 2);
    float y = ((circle->bottom + circle->top) / 2) - ((rc->bottom + rc->top) / 2);
    float r1 = (circle->right - circle->left) / 2;
    float r2 = sqrtf(((rc->right - rc->left) / 2) * ((rc->right - rc->left) / 2) +
        ((rc->bottom - rc->top) / 2) * ((rc->bottom - rc->top) / 2));
    float d = sqrtf(x*x + y*y);

    if (rc->left - r1 <= ((circle->right + circle->left) / 2) && rc->top - r1 <= ((circle->bottom + circle->top) / 2) &&
        rc->right + r1 >= ((circle->right + circle->left) / 2) && rc->bottom + r1 >= ((circle->bottom + circle->top) / 2))
    {
        if (d <= r1 + r2) return TRUE;
        else return FALSE;
    }
    else return FALSE;
}

//RECT의 X 중점
inline float GetRectCenterX(RECT * rc)
{
    return (rc->right + rc->left) / 2;
}

//RECT의 Y 중점
inline float GetRectCenterY(RECT * rc)
{
    return (rc->bottom + rc->top) / 2;
}

inline bool FadeIn(int * alpha)
{
    *alpha += 2;
    if (*alpha >= 255)
    {
        *alpha = 255;
        return true;
    }
    return false;
}

inline bool FadeOut(int * alpha)
{
    *alpha -= 2;
    if (*alpha <= 0)
    {
        *alpha = 0;
        return true;
    }
    return false;
}

}//inline POINT makePt(float x, float y)
//{
//	return { x,y };
//}