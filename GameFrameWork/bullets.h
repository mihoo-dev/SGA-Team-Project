#pragma once
#include "gameNode.h"
#include <vector>		//이거 기억나죠 여러부우운

struct tagBullet
{
	image* bulletImage;		//총알 이미지
	RECT rc;				//총알 충돌박스
	float x, y;				//총알 좌표
	float angle;			//총알 각도
	float speed;
	float radius;			
	float fireX, fireY;		//총알 발사위치
	bool isFire;			//발사여부
	int count;
};

//공용(너도나도) 사용할 총알
class bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	bullet();
	~bullet();

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle, float speed);

	void move();

	void removeBullet(int arrNum);

	//접근자
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }
	
};


//만들어놓고 발사하는 미쏴일
class missile : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
public:
	missile();
	~missile();

	virtual HRESULT init(int bulletMax, float range);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void fire(float x, float y);

	void move(void);


};

//발사할때 생성해서 쏘는 미쏴일
class piccolo : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _bulletMax;

public:
	piccolo();
	~piccolo();

	HRESULT init(int missileMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y);

	void move();

	void removeMissile(int arrNum);

	//접근자
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

};