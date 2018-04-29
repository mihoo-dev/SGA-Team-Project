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
        RIGHT_RUN,  LEFT_RUN,
        RIGHT_JUMP, LEFT_JUMP,
        RIGHT_MID,  LEFT_MID,
        RIGHT_FALL, LEFT_FALL,
        RIGHT_LAND, LEFT_LAND,
        RIGHT_LADDER_ON, LEFT_LADDER_ON,
        LADDER_UP, LADDER_DOWN,
        RIGHT_LADDER_OFF, LEFT_LADDER_OFF,
        RIGHT_DUCK, LEFT_DUCK,
        RIGHT_DUCK_KICK, LEFT_DUCK_KICK,
        RIGHT_ATTACK_1, LEFT_ATTACK_1,
        RIGHT_ATTACK_2, LEFT_ATTACK_2,
        RIGHT_ATTACK_3, LEFT_ATTACK_3,
        RIGHT_JUMP_ATTACK, LEFT_JUMP_ATTACK
    };
    //캐릭터 방향
    enum DIRECTION {
        LEFT, RIGHT
    };

    image * _img;           //이미지
    animation * _anim;      //애니메이션

    RECT _rc;               //RECT
    float _x, _y;           //중점
    float _speed;           //속도
    float _friction;        //마찰
    float _jumpPower;       //점프 파워
    float _gravity;         //중력
    bool _onLadder;         //사다리
    bool _onGround;         //

    DIRECTION _direction;   //방향
    STATE _state;           //상태

    int _probeX;            //X 탐사 축
    int _probeY;            //Y 탐사 축
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

