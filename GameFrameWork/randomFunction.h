#pragma once
#include "singletonBase.h"
#include <time.h>

class randomFunction : public singletonBase < randomFunction >
{
public:

	//생성자
	randomFunction()
	{
		//TickCount == 0.001 
		srand(GetTickCount());
	}
	//소멸자
	~randomFunction()
	{

	}

	//============== 정수형 난수 =================

	//지정한 숫자 범위 내에서 난수를 발생 
	inline int getInt(int num) { return rand() % num; }

	//특정 숫자 구간에서 난수를 뽑아오고 싶을때
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum) + fromNum;
	}

	//=============== 실수형 난수 ====================
	inline float getFloat(float num)
	{
		return (float)rand() / (float)num;
	}

	// from ~ to
	//4. 65535

	inline float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toNum - fromNum) + fromNum);
	}


};
