#pragma once
class timer
{
private:
	bool _isHardware;			//하드웨어가 고성능이냐?
	float _timeScale;			//FPS(Frame Per Second) 빈도
	float _timeElapsed;			

	__int64 _curTime;
	__int64 _lastTime;
	__int64 _periodFrequency;

	unsigned long _frameRate;
	unsigned long _FPSFrameRate;

	float _FPSTimeElapsed;
	float _worldTime;

public:
	timer();
	~timer();

	HRESULT init();
	void tick(float lockFPS = 0.0f);
	unsigned long getFrameRate(char* str = NULL) const;

	inline float getElapsedTime(void) const { return _timeElapsed; }
	inline float getWorldTime(void) const { return _worldTime; }
};

