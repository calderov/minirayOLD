#pragma once

#include "object.h"

class Plane : public Object {
protected:
	Vector3d position;
	Vector3d normal;

public:
	Plane(Vector3d position, Vector3d normal, Color color, double reflection);

	double intersect(Vector3d rayO, Vector3d rayD);
	Vector3d normalize(Vector3d V);
};
