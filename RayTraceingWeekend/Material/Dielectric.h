#pragma once
#include "Material.h"
#include "../Math/Vec3.h"
#include "../Math/Ray.h"
#include "../Math/Random.h"

class Dielectric : public Material {
public:
	Dielectric(float ri) : ref_idx(ri) {}

	virtual bool Scatter(const Ray& r_in, const HitResult& rec, Vec3& attenuation, Ray& scattered) const {
		Vec3 outward_normal;
		Vec3 reflected = Reflect(r_in.Direction(), rec.normal);
		float ni_over_nt;
		attenuation = Vec3(1.0, 1.0, 1.0);
		Vec3 refracted;
		float reflect_prob;
		float cosine;
		if (dot(r_in.Direction(), rec.normal) > 0) {
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			//         cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
			cosine = dot(r_in.Direction(), rec.normal) / r_in.Direction().Length();
			cosine = sqrt(1 - ref_idx * ref_idx * (1 - cosine * cosine));
		}
		else {
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -dot(r_in.Direction(), rec.normal) / r_in.Direction().Length();
		}
		if (Refract(r_in.Direction(), outward_normal, ni_over_nt, refracted))
			reflect_prob = Schlick(cosine, ref_idx);
		else
			reflect_prob = 1.0;

		if (Rand01() < reflect_prob)
			scattered = Ray(rec.p, reflected);
		else
			scattered = Ray(rec.p, refracted);
		return true;
	}

	float ref_idx;
};