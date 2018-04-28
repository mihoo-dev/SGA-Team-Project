#include "stdafx.h"
#include "utils.h"

namespace NONA_UTIL
{
	//거리 구하는 함수
	float getDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return sqrtf(x * x + y * y);
	}

	//각도 구하는 함수
	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		float angle = acosf(x / distance);

		if (y2 > y1)
		{
			angle = 2 * PI - angle;
			if (angle >= 2 * PI) angle -= 2 * PI;
		}

		return angle;
	}

const char* fileName(string fileName)
	{
		string folder = "image\\";
		folder.append(fileName);
		folder.append(".bmp");

		return folder.c_str();
	}
	
string filePath(string filePath)
	{
		string folder = "image\\";
		string extension = ".bmp";
	
		folder.append(filePath);
		folder.append(extension);

		return folder;
	}
}
