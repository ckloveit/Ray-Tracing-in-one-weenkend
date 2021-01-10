#pragma once
#include "Material.h"

class Metal : public Material
{
public:
	Metal(const Vec3& inAlbedo, float inRoughness) : albedo(inAlbedo), roughness(inRoughness) {}

	virtual bool Scatter(const Ray& ray, const HitResult& result, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 reflected = Reflect(ray.Direction().GetNormalize(), result.normal);
		scattered = Ray(result.p, reflected + roughness * RandomInUnitSphere());
		attenuation = albedo;
		return dot(scattered.Direction(), result.normal) > 0;
	}

	Vec3 albedo;
	float roughness;
};


