#pragma once

#include "typedefs.h"

class Object {
public:
	Color color;
	double reflection;
	virtual double intersect(Vector3d rayO, Vector3d rayD) = 0;
	virtual Vector3d normalize(Vector3d V) = 0;
};
