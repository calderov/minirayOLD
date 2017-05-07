#include <cmath>
#include "plane.h"

Plane::Plane(Vector3d position, Vector3d normal, Color color, double reflection)
{
	this->position = position;
	this->normal = normal;
	this->color = color;
	this->reflection = reflection;
}

double Plane::intersect(Vector3d rayO, Vector3d rayD)
{
	double denom = rayD.dot(this->normal);
	if (fabs(denom) < EPSILON)
		return INFTY;

	double d = (this->position - rayO).dot(this->normal) / denom;
	if (d < 0 || INFTY < d)
		return INFTY;

	return d;
}

Vector3d Plane::normalize(Vector3d V)
{
	return normal;
}
