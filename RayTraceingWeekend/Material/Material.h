#pragma once
#include "../Math/Ray.h"
#include "../Math/Vec3.h"
#include "../Hitable.h"

class Material
{
public:
	virtual bool Scatter(const Ray& rayIn, const HitResult& result, Vec3& attenuation, Ray& scattered) const = 0;
};




