#pragma once
#include "Material.h"
#include "../Math/Random.h"

class Lambertian : public Material
{
public:
	Lambertian(const Vec3& inAlbedo) : albedo(inAlbedo) {}

	virtual bool Scatter(const Ray& rayIn, const HitResult& result, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 target = result.p + result.normal + RandomInUnitSphere();
		scattered = Ray(result.p, target - result.p);
		attenuation = albedo;
		return true;
	}

	Vec3 albedo;
};

