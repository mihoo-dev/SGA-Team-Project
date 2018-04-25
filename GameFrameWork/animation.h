#pragma once
#include <vector>

//void* - 보이드 포인터
//텅빈곳을 가르킨다 -> (자료형에 구애받지않고 가르킬수있음)
//보이드포인터는 쉽게말하면 무엇이든 가르킬 수 있고
//대신에 캐스팅(형변환)을 꼭! 선언하고 사용해야한다

typedef void(*CALLBACK_FUNCTION)(void);
typedef void(*CALLBACK_FUNCTION_PARAMETER)(void*);


class animation
{
public:
	typedef vector<POINT>	vFrameList;
	typedef vector<int>		vPlayList;

	//퍼블릭에다 선언한 이유는 접근이 자유롭게 하기위함

private:
	int				_frameNum;		//프레임 장 수
	vFrameList		_frameList;		//프레임 리스트
	vPlayList		_playList;		//플레이(애니메이션) 리스트

	int				_frameWidth;	//프레임 가로크기
	int				_frameHeight;	//프레임 세로크기
		
	BOOL			_loop;			//루프 여부

	float			_frameUpdateSec;
	float			_elapsedSec;

	DWORD			_nowPlayIndex;
	BOOL			_play;

	void*						_obj;						//보포
	CALLBACK_FUNCTION			_callbackFunction;			//콜백
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;	//파있콜
	

public:
	animation();
	~animation();

	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release();

	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setDefPlayFrame(BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int* playArr, int arrLen, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION cbFunction);
	void setPlayFrame(int start, int end, BOOL reverse, BOOL loop, CALLBACK_FUNCTION_PARAMETER cbFunction, void* obj);

	void setFPS(int framePerSec);

	void frameUpdate(float elpasedTime);

	void start(void);
	void stop(void);
	void pause(void);
	void resume(void);

	inline BOOL isPlay() { return _play; }
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }
};

