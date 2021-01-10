#pragma once
#include "Hitable.h"

class Material;

class Sphere : public Hitable
{
public:
	Sphere()
	{
		center = Vec3(0, 0, 0); radius = 0; materialPtr = nullptr;
	}
	~Sphere();

	Sphere(Vec3 inCenter, float inRadius, Material* material) : center(inCenter), radius(inRadius) , materialPtr(material) {}
	virtual bool Hit(const Ray& ray, float tMin, float tMax, HitResult& result) const;

	Vec3 center;
	float radius;
	Material* materialPtr;
};