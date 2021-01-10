#pragma once
#include "Hitable.h"

class HitableList : public Hitable
{
public:
	HitableList() = default;
	~HitableList();
	HitableList(Hitable** hits, int n) { list = hits; listSize = n; }
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitResult& result) const;

	Hitable** list;
	int listSize;
};
