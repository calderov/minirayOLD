#include <algorithm>
#include <cmath>
#include "sphere.h"


Sphere::Sphere(Vector3d center, double radius, Color color, double reflection)
{
	this->center = center;
	this->radius = radius;
	this->color = color;
	this->reflection = reflection;
}

double Sphere::intersect(Vector3d rayO, Vector3d rayD)
{
	Vector3d OS = rayO - this->center;
	double r = this->radius;
	double a = rayD.dot(rayD);
	double b = 2 * rayD.dot(OS);
	double c = OS.dot(OS) - r * r;
	double d = INFTY;

	double disc = b * b - 4 * a * c;
	if (disc > 0)
	{
		double discSqrt = sqrt(disc);
		double q;
		if (b < 0)
			q = (-b - discSqrt) / 2;
		else
			q = (-b + discSqrt) / 2;
		double t0 = q / a;
		double t1 = c / q;
		t0 = std::min(t0, t1);
		t1 = std::max(t0, t1);
		if (t1 >= 0)
		{
			if (t0 < 0)
				d = t1;
			else
				d = t0;
		}
	}

	if (d < 0 || INFTY < d)
		return INFTY;

	return d;
}

Vector3d Sphere::normalize(Vector3d V)
{
	Vector3d U = V - this->center;
	U.normalize();
	return U;
}
