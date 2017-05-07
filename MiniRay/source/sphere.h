#pragma once

#include "object.h"


class Sphere: public Object {
protected:
	Vector3d center;
	double radius;

public:
	Sphere(Vector3d center, double radius, Color color, double reflection);
	
	double intersect(Vector3d rayO, Vector3d rayD);
	Vector3d normalize(Vector3d V);
};
