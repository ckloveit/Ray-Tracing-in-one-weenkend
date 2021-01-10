#include "Sphere.h"
#include "Material/Material.h"

Sphere::~Sphere()
{ 
	delete materialPtr;
	materialPtr = nullptr; 
}

bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitResult& result) const
{
	Vec3 oc = ray.Origin() - center;
	float a = dot(ray.Direction(), ray.Direction());
	float b = dot(oc, ray.Direction());

	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0)
	{
		float temp = (-b - sqrt(b * b - a * c)) / a;
		if (temp < tMax && temp > tMin)
		{
			result.t = temp;
			result.p = ray.GetPointByParameter(result.t);
			result.normal = (result.p - center) / radius;
			result.materialPtr = materialPtr;
			return true;
		}
		temp = (-b + sqrt(b * b - a * c)) / a;
		if (temp < tMax && temp > tMin)
		{
			result.t = temp;
			result.p = ray.GetPointByParameter(result.t);
			result.normal = (result.p - center) / radius;
			result.materialPtr = materialPtr;
			return true;
		}
	}
	return false;
}