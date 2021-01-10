#pragma once
#include "Vec3.h"

Vec3 RandomInUnitSphere()
{
	Vec3 p;
	do
	{
		p = 2.0 * Vec3((rand() % 10000 / 10000.0f), (rand() % 10000 / 10000.0f), (rand() % 10000 / 10000.0f)) - Vec3(1, 1, 1);
	} while (dot(p, p) >= 1.0f);
	return p;
}

inline float Rand01()
{
	return rand() % 10000 / 10000.0;
}