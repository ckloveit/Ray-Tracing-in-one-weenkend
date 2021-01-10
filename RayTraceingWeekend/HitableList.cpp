#include "HitableList.h"

bool HitableList::Hit(const Ray& ray, float tMin, float tMax, HitResult& result) const
{
	HitResult tempResult;
	bool bhit = false;
	float closeSoFar = tMax;
	for (int i = 0; i < listSize; i++)
	{
		if (list[i]->Hit(ray, tMin, closeSoFar, tempResult))
		{
			bhit = true;
			closeSoFar = tempResult.t;
			result = tempResult;
		}
	}
	return bhit;
}

HitableList::~HitableList()
{
	if (list == nullptr)
		return;
	for (int i = 0; i < listSize; i++)
	{
		if (list[i])
		{
			delete list[i];
			list[i] = nullptr;
		}
	}

}