#pragma once

#include "typedefs.h"

class Camera
{
public:
	// Render settings
	int width;
	int height;
	double ratio;

	// Screen pixels live here
	std::vector<Pixel> screen;

	// Camera plane segment coordinates (x0, y0, x1, y1)
	std::vector<double> screen_rect;

	// Camera position (space coordinates)
	Vector3d position;

	// Camera ray target
	Vector3d rayTarget;

	Camera();
	Camera(int width, int height, Vector3d position);
	void pointRayFromScreenCoord(int x, int y);
	void saveBMP(std::string filename);

private:
	void initializeScreenPixels();
	unsigned char* getBMPData();
};