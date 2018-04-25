#pragma once
#include "gameNode.h"

//콜백함수 -> 함수포인터
typedef void(*CALLBACK_FUNCTION)(void);

//성인요로분은~
//콜백함수가 전역으로 선언으로 선언이 되어있어서
//static을 붙이지 않으면 사용할수가 없다
//매개변수를 사용할수가 있을까?!?!?!?!?!

//<Functional>
//bind, move, 

//객체 & 객체의 변수도 매개변수로 넣어서 사용할 수 있게
//변형시켜보기!
//의외로 쉽다는게 함정인데, 의외로 감도안오는것도 함정


enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;

	const char* _imageName;
	image* _image;
	RECT _rc;
	float _x, _y;

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	CALLBACK_FUNCTION _callbackFunction;

public:
	button();
	~button();

	HRESULT init(const char* imageName,
		int x, int y, POINT btnDownFramePoint,
		POINT btnUpFramePoint, CALLBACK_FUNCTION cbFunction);

	void release(void);
	void update(void);
	void render(void);

};

