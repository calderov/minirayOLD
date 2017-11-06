#pragma once

#include "typedefs.h"

#include <vector>

class Camera
{
public:
	// Render settings
	int width;
	int height;
	double ratio;

	// Screen pixels live here
	std::vector<Pixel> screen;

	// Camera position (space coordinates)
	Vector3d position;

	// Camera ray target
	Vector3d rayTarget;

	Camera();
	Camera(int width, int height, Vector3d position);
	void pointRayFromScreenCoord(int x, int y);
	void saveBMP(std::string filename);

private:
	// Camera plane segment coordinates (x0, y0, x1, y1)
	std::vector<double> screen_rect;

	void initializeScreenPixels();
	void cameraInit(int width, int height, Vector3d position);
	std::vector<unsigned char> getBMPData();
};