#pragma warning (disable : 4996)
#include "camera.h"

// Camera constructor
Camera::Camera()
{
	width  = 640;
	height = 480;
	ratio = width / height;

	initializeScreenPixels();

	// Set camera plane segment coordinates (x0, y0, x1, y1)
	screen_rect.push_back(-1);
	screen_rect.push_back(-1 / ratio + 0.25);
	screen_rect.push_back(1);
	screen_rect.push_back(1 / ratio + 0.25);

	// Set camera position and target(x, y, z)
	this->position  = { 0, 0.35, -1 };
	this->rayTarget = { 0, 0, 0 };
}

Camera::Camera(int width, int height, Vector3d position)
{
	// Set render resolution and ratio
	this->width  = width;
	this->height = height;
	ratio = width / height;

	initializeScreenPixels();

	// Set camera plane segment coordinates (x0, y0, x1, y1)
	screen_rect.push_back(-1);
	screen_rect.push_back(-1 / ratio + 0.25);
	screen_rect.push_back(1);
	screen_rect.push_back(1 / ratio + 0.25);

	// Set camera position and target(x, y, z)
	this->position  = position;
	this->rayTarget = { 0, 0, 0 };
}

// Set camera to "point" a ray in the direction of the vector
// normal to the provided pair of screen coordinates.
void Camera::pointRayFromScreenCoord(int x, int y)
{
	double x0 = screen_rect[0];
	double y0 = screen_rect[1];
	double x1 = screen_rect[2];
	double y1 = screen_rect[3];

	double w = fabs(x1 - x0) / width;
	double h = fabs(y1 - y0) / height;

	if (x0 < x1)
		rayTarget.x = x0 + x * w;
	else
		rayTarget.x = x0 - x * w;

	if (y0 < y1)
		rayTarget.y = y0 + y * w;
	else
		rayTarget.y = y0 - y * w;
}

// Initialize render pixels to be all black
void Camera::initializeScreenPixels()
{
	std::vector<Pixel> blackScreen;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Pixel current_pixel;

			current_pixel.x = x;
			current_pixel.y = y;
			current_pixel.color = { 0, 0, 0 };

			blackScreen .push_back(current_pixel);
		}
	}

	this->screen = blackScreen;
}

// Transform screen to a bitmap friendly format [r,g,b, r,g,b, ... ,r,g,b]
unsigned char* Camera::getBMPData()
{
	unsigned char* image = nullptr;
	image = (unsigned char*)malloc(3 * this->width * this->height);

	int i = 0;
	for (size_t pixel_index = 0; pixel_index < this->screen.size(); pixel_index++)
	{
		image[i++] = (unsigned char)(this->screen[pixel_index].color.b * 255);
		image[i++] = (unsigned char)(this->screen[pixel_index].color.g * 255);
		image[i++] = (unsigned char)(this->screen[pixel_index].color.r * 255);
	}

	return image;
}

// Save screen to bitmap
void Camera::saveBMP(std::string filename)
{
	// Get width and height from _camera metadata
	int width = this->width;
	int height = this->height;

	// Transform image to a bitmap friendly format [r,g,b, r,g,b, ... ,r,g,b]
	unsigned char* image = this->getBMPData();

	// Define file pointer and size
	FILE* f;
	int file_size = 54 + 3 * width * height;

	// Define bitmap headers, info and padding
	unsigned char bmp_header[14] = {
		'B','M',  // Mime type
		0,0,0,0,  // Size in bytes
		0,0,0,0,  // App data 
		54,0,0,0  // Data offset start
	};
	unsigned char bmp_info[40] = {
		40,0,0,0, // Info HD size
		0,0,0,0,  // Width
		0,0,0,0,  // Height
		1,0,      // # color planes
		24,0      // Bits per pixel
	};
	unsigned char bmp_pad[3] = { 0,0,0 };

	// Set headers and info
	bmp_header[2] = (unsigned char)(file_size);
	bmp_header[3] = (unsigned char)(file_size >> 8);
	bmp_header[4] = (unsigned char)(file_size >> 16);
	bmp_header[5] = (unsigned char)(file_size >> 24);

	bmp_info[4] = (unsigned char)(width);
	bmp_info[5] = (unsigned char)(width >> 8);
	bmp_info[6] = (unsigned char)(width >> 16);
	bmp_info[7] = (unsigned char)(width >> 24);

	bmp_info[8] = (unsigned char)(height);
	bmp_info[9] = (unsigned char)(height >> 8);
	bmp_info[10] = (unsigned char)(height >> 16);
	bmp_info[11] = (unsigned char)(height >> 24);

	// Write headers and info to file
	f = fopen(filename.c_str(), "wb");
	fwrite(bmp_header, 1, 14, f);
	fwrite(bmp_info, 1, 40, f);

	// Write data to file
	for (int i = 0; i < height; i++)
	{
		fwrite(image + (width * (height - i - 1) * 3), 3, width, f);
		fwrite(bmp_pad, 1, (4 - (width * 3) % 4) % 4, f);
	}

	// Close file
	fclose(f);

	// Clean image memory
	delete[] image;
}