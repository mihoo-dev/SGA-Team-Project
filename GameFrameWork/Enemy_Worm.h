#pragma once
#include <vector>

class Player;
class Enemy_Worm
{
	enum WORM_STATE
	{
		IDLE_LEFT,
		IDLE_RIGHT,
		MOVE_LEFT,
		MOVE_RIGHT,
		ATTACK_LEFT,
		ATTACK_RIGHT,
		HIT_LEFT,
		HIT_RIGHT,
		DIE,
		DEFAULT
	};

	enum PHASE
	{
		IDLE,
		LEFT,
		RIGHT,
		ATTACK
	};

	struct KeyInfo
	{
		KeyInfo() {};
		KeyInfo(int x) { FrameX = x; FrameY = 0; };
		int FrameX;
		int FrameY;
	};


	struct AnimKeyFrame
	{
		AnimKeyFrame()
			: Name(DEFAULT), Frame(nullptr), FrameSize(0)
		{};
		AnimKeyFrame(WORM_STATE name, KeyInfo* key, UINT Size)
			:Name(name), FrameSize(Size - 1)
		{
			Frame = new KeyInfo[Size];
			memcpy_s(Frame, sizeof(KeyInfo)*Size, key, sizeof(KeyInfo)*Size);
		};

		WORM_STATE Name;
		KeyInfo* Frame;
		UINT FrameSize;
	};

	std::vector<AnimKeyFrame*> vKeyFrame;

private:
	image* img_Idle;
	image* img_Move;
	image* img_Attack;
	image* img_Hit;
	float x, y;
	float wSpeed;
	float wPower;
	int hp;
	int atk;
	RECT hitRect;
	float range;
	RECT rc;
	int count;
	int phase;
	bool isAttack;
	bool isHit;

private:
	float playerX;
	float playerY;
	RECT _playerRect;
	RECT _playerAtkRect;


private:
	WORM_STATE Status;
	AnimKeyFrame CurrentFrame;
	UINT CurrentFrameIndex;

	int FrameSpeed;
	int FramePerCount;
	KeyInfo RenderFrame;

public:
	Enemy_Worm();
	~Enemy_Worm();

	HRESULT init(int x, int y);
	void AddAnimation(WORM_STATE FrameName, KeyInfo key[], UINT ArraySize);
	void release(void);
	void update(void);
	void render(HDC mDC);

	void ChangeAnimationFrame(WORM_STATE value);
	void WormAnimationUpdate(void);
	void LoopAnimation(UINT value = 0);

	void WormController(void);

	void SetHp(int _hp) { hp = _hp; }
	int GetHp() { return hp; }

};

