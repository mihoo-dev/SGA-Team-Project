#pragma once
#include "gameNode.h"
class Player :
    public gameNode
{
private:
    //캐릭터 상태
    enum STATE {
        RIGHT_IDLE, LEFT_IDLE,
        RIGHT_WALK, LEFT_WALK,
        RIGHT_RUN, LEFT_RUN,
        RIGHT_JUMP, LEFT_JUMP,
        RIGHT_MID, LEFT_MID,
        RIGHT_FALL, LEFT_FALL,
        RIGHT_LAND, LEFT_LAND,
        RIGHT_LADDER_ON, LEFT_LADDER_ON,
        LADDER_UP, LADDER_DOWN,
        RIGHT_LADDER_OFF, LEFT_LADDER_OFF,
        RIGHT_DUCK, LEFT_DUCK,
        RIGHT_DUCK_KICK, LEFT_DUCK_KICK,
        RIGHT_DUCK_SLIDE, LEFT_DUCK_SLIDE,
        RIGHT_PUNCH_1, LEFT_PUNCH_1,
        RIGHT_PUNCH_2, LEFT_PUNCH_2,
        RIGHT_PUNCH_3, LEFT_PUNCH_3,
        RIGHT_JUMP_PUNCH, LEFT_JUMP_PUNCH,
        RIGHT_JAKE_PUNCH, LEFT_JAKE_PUNCH,
        RIGHT_SWORD_1, LEFT_SWORD_1,
        RIGHT_SWORD_2, LEFT_SWORD_2,
        RIGHT_JUMP_SWORD, LEFT_JUMP_SWORD,
        RIGHT_DUCK_SWORD, LEFT_DUCK_SWORD
    };
    //캐릭터 방향
    enum DIRECTION {
        LEFT, RIGHT
    };

    enum ITEM {
        DEFFAULT,
        SWORD,
        FLAMESWORD
    };

    image * _img;           //이미지
    animation * _anim;      //애니메이션

    RECT _rc;               //RECT
    RECT _colRC;
    float _x, _y;           //중점
    float _colX, _colY;
    float _speed;           //속도
    float _friction;        //마찰
    float _jumpPower;       //점프 파워
    float _gravity;         //중력
    bool _onLadder;         //사다리
    bool _onGround;         //

    DIRECTION _direction;   //캐릭터 방향
    STATE _state;           //캐릭터 상태
    ITEM _item;             //아이템 상태

    int _probeX;            //X 탐사 축
    int _probeY;            //Y 탐사 축

    bool _isCombo;
public:
    Player();
    ~Player();

    HRESULT init();
    void release();
    void update();
    void render();

    //애니메이션 변경
    void ChangeAnim(STATE state, string animKeyName);
    //마찰 적용 함수
    void Friction(string direction, float maxSpeed);
    //지형충돌
    void GroundCollision();
};

