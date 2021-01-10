#pragma once
#include "Math/Ray.h"
class Material;

struct HitResult
{
	float t;
	Vec3 p;
	Vec3 normal;
	Material* materialPtr;
};

class Hitable
{
public:
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitResult& result) const = 0;
	virtual ~Hitable() {}
};

