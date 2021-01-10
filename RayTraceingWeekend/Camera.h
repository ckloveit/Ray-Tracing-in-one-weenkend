#pragma once
#include "Math/Vec3.h"
#include "Math/Ray.h"

class Camera
{
public:
	Camera(Vec3 lookFrom, Vec3 lookAt, Vec3 vUp, float vFovDegree, float aspect, float aperture, float focusDist)
	{
		lenRadius = aperture / 2;
		float theta = vFovDegree * M_PI / 180.0f;
		float halfHeight = tan(theta / 2);
		float halfWidth = aspect * halfHeight;
		origin = lookFrom;

		w = (lookFrom - lookAt).GetNormalize();
		u = (cross(vUp, w)).GetNormalize();
		v = (cross(w, u)).GetNormalize();

		lowerLeftCorner = Vec3(-halfWidth, -halfHeight, -1.0f);
		lowerLeftCorner = origin - halfWidth * u * focusDist - halfHeight * v * focusDist - w * focusDist;
		horizontal = 2 * halfWidth * u * focusDist;
		vertical = 2 * halfHeight * v * focusDist;
	}

	Ray GetRay(float s, float t) 
	{
		Vec3 rd = lenRadius * random_in_unit_disk();
		Vec3 offset = u * rd.x() + v * rd.y();

		return Ray(origin + offset,
			lowerLeftCorner + s * horizontal + t * vertical - origin - offset); 
	}

	Vec3 random_in_unit_disk()
	{
		Vec3 p;
		do {
			p = 2.0 * Vec3(Rand01(), Rand01(), 0) - Vec3(1, 1, 0);
		} while (dot(p, p) >= 1.0);
		return p;
	}
	Vec3 origin;
	Vec3 lowerLeftCorner;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 u, v, w;
	float lenRadius;
};