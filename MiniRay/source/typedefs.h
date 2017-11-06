#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include <cmath>

constexpr long   INFTY   = 999999999;
constexpr double EPSILON = 0.0000001;

typedef struct Color
{
	double r;
	double g;
	double b;

	Color operator+(Color C)
	{
		Color R = {
			std::min(r + C.r, 1.0),
			std::min(g + C.g, 1.0),
			std::min(b + C.b, 1.0)
		};
		return R;
	}

	Color operator*(double s)
	{
		Color R = { 
			std::min(r * s, 1.0),
			std::min(g * s, 1.0),
			std::min(b * s, 1.0)
		};
		return R;
	}

	std::string to_string()
	{
		std::string color_string = std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b);
		return color_string;
	}
} Color;


typedef struct Vector3d
{
	double x;
	double y;
	double z;

	Vector3d operator-(Vector3d V)
	{
		Vector3d R = { x - V.x, y - V.y, z - V.z };
		return R;
	}

	Vector3d operator+(Vector3d V)
	{
		Vector3d R = { x + V.x, y + V.y, z + V.z };
		return R;
	}

	Vector3d operator*(Vector3d V)
	{
		Vector3d R = { x * V.x, y * V.y, z * V.z };
		return R;
	}

	Vector3d operator*(double s)
	{
		Vector3d R = { x * s, y * s, z * s };
		return R;
	}

	Vector3d operator-(double s)
	{
		Vector3d R = { x - s, y - s, z - s };
		return R;
	}

	// Normalizes the current vector using the Frobenius norm
	void normalize()
	{
		// Compute Frobenius norm
		double f = sqrt((x * x) + (y * y) + (z * z));
		x = x / f;
		y = y / f;
		z = z / f;
	}

	// Computes the dot product of the current vector with the given one
	double dot(Vector3d V)
	{
		return (x * V.x) + (y * V.y) + (z * V.z);
	}

	std::string to_string()
	{
		std::string vector_string = std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
		return vector_string;
	}
} Vector3d;


typedef struct Pixel
{
	// Screen coordinates
	int x;
	int y;

	// Pixel color
	Color color;
} Pixel;


typedef struct Light
{
	// Light position
	Vector3d position;

	// Light color
	Color color;

	// Misc properties
	double diffuse;
	double ambient;
	double specular_c;
	double specular_k;
} Light;


typedef struct TraceResult
{
	// Did the ray did hit an object
	bool succeeded;

	// Index of the hit object
	int object_index;

	// Ray source and hit point
	Vector3d M;
	Vector3d N;

	// Ray color
	Color color;
} TraceResult;
