#pragma once

#define PI 3.141592654f
#define PI2 PI * 2

#define PI4 float(PI / 4.0f)
#define PI8 float(PI / 8.0f)
#define PI16 float(PI / 16.0f)
#define PI32 float(PI / 32.0f)
#define PI64 float(PI / 64.0f)
#define PI128 float(PI / 128.0f)

namespace NONA_UTIL
{
	//거리 구하는 함수
	float getDistance(float x1, float y1, float x2, float y2);

	//각도 구하는 함수
	float getAngle(float x1, float y1, float x2, float y2);

	//이미지 저장폴더 입력해주는 함수
	const char* fileName(string fileName);
	string filePath(string filePath);
}