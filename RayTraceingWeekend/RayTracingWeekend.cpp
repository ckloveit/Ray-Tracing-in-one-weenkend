#include <iostream>
#include <fstream>
#include "Math/Vec3.h"
#include "Math/Ray.h"
#include "Math/Random.h"
#include "HitableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material/Material.h"
#include "Material/Lambertian.h"
#include "Material/Metal.h"
#include "Material/Dielectric.h"

using namespace std;

HitableList* random_scene() {
	int n = 500;
	Hitable** list = new Hitable * [n + 1];
	list[0] = new Sphere(Vec3(0, -700, 0), 700, new Lambertian(Vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = Rand01();
			Vec3 center(a + 0.9 * Rand01(), 0.2, b + 0.9 * Rand01());
			if ((center - Vec3(4, 0.2, 0)).Length() > 0.9) {
				if (choose_mat < 0.8) {  // diffuse
					list[i++] = new Sphere(center, 0.2, new Lambertian(Vec3(Rand01() * Rand01(), Rand01() * Rand01(), Rand01() * Rand01())));
				}
				else if (choose_mat < 0.95) { // metal
					list[i++] = new Sphere(center, 0.2,
						new Metal(Vec3(0.5 * (1 + Rand01()), 0.5 * (1 + Rand01()), 0.5 * (1 + Rand01())), 0.5 * Rand01()));
				}
				else {  // glass
					list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new Sphere(Vec3(0, 1, 0), 1.0, new Dielectric(2.5));
	list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0, new Lambertian(Vec3(0.4, 0.2, 0.1)));
	list[i++] = new Sphere(Vec3(4, 1, 0), 1.0, new Metal(Vec3(1, 1, 1), 0.0));

	return new HitableList(list, i);
}

float HitSphere(const Vec3& center, float radius, const Ray& ray)
{
	Vec3 oc = ray.Origin() - center;
	float a = dot(ray.Direction(), ray.Direction());
	float b = 2.0f * dot(oc, ray.Direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return -1;
	}
	else 
	{
		return (-b - sqrt(discriminant)) / (2.0f * a);
	}
}



Vec3 ComputeColor(const Ray& ray, HitableList* world, int depth)
{
	HitResult result;
	if (world->Hit(ray, 0.001f, FLT_MAX, result))
	{
		Ray scattered;
		Vec3 attenuation;
		if (depth < 50 && result.materialPtr->Scatter(ray, result, attenuation, scattered))
		{
			return attenuation * ComputeColor(scattered, world, depth + 1);
		}
		else
		{
			return Vec3(0, 0, 0);
		}
	}
	else
	{
		Vec3 unitDirection = ray.Direction().GetNormalize();
		float t = 0.5f * (unitDirection.y() + 1.0f);
		return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
	}
}


int main()
{
	std::fstream fileStream;
	fileStream.open("OutColor.ppm", ios::out | ios::trunc);

	int nx = 200;
	int ny = 100;
	int ns = 100;

	fileStream << "P3\n" << nx << " " << ny << "\n255\n";
	Vec3 lowerLeftCorner(-2.0f, -1.0f, -1.0f);
	Vec3 horizontal(4.0f, 0.0f, 0.0f);
	Vec3 vertical(0.0f, 2.0f, 0.0f);
	Vec3 origin(0.0f, 0.0f, 0.0f);
	Hitable* list[5];
	/*
	list[0] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.8, 0.3, 0.3)));
	list[1] = new Sphere(Vec3(0, -100.5, -1), 100, new Lambertian(Vec3(0.8, 0.8, 0.0)));
	list[2] = new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.6, 0.2), 0.3));
	list[3] = new Sphere(Vec3(-1, 0, -1), 0.5, new Dielectric(1.5));
	list[4] = new Sphere(Vec3(-1, 0, -1), -0.45, new Dielectric(1.5));
	*/

	HitableList* world = random_scene();//new HitableList(list, 5);
	Vec3 lookfrom(3, 3, 2);
	Vec3 lookat(0, 0, -1);
	float dist_to_focus = (lookfrom - lookat).Length();
	float aperture = 2.0;
	Camera camera(lookfrom, lookat, Vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			Vec3 color = Vec3(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + (rand() % 10000 / 10000.0)) / float(nx);
				float v = float(j + (rand() % 10000 / 10000.0)) / float(ny);
				Ray ray = camera.GetRay(u, v);
				Vec3 col = ComputeColor(ray, world, 0);
				color += col;
			}
			color /= ns;
			// Gamma Correct
			color = Vec3(pow(color.e[0], 0.45f), pow(color.e[1], 0.45f), pow(color.e[2], 0.45f));

			int ir = int(255.99 * color.e[0]);
			int ig = int(255.99 * color.e[1]);
			int ib = int(255.99 * color.e[2]);
			fileStream << ir << " " << ig << " " << ib << "\n";
		}
	}
	fileStream.close();

	delete world; world = nullptr;
	//delete list[0]; list[0] = nullptr;
	//delete list[1]; list[1] = nullptr;
	//delete list[2]; list[2] = nullptr;
	//delete list[3]; list[3] = nullptr;
	//delete list[4]; list[4] = nullptr;

}