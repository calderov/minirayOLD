#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include "scene.h"

using namespace std;

Color rgbColor(double r, double g, double b)
{
	r = (r > 255.0) ? 255.0 : std::max(r, 0.0) / 255.0;
	g = (g > 255.0) ? 255.0 : std::max(g, 0.0) / 255.0;
	b = (b > 255.0) ? 255.0 : std::max(b, 0.0) / 255.0;
	Color color = { r, g, b };
	return color;
}

int main(int argc, char const *argv[])
{
	// Set camera
	//Camera camera(1920, 1440, { 0, 0.35, -1 });
	Camera camera;

	// Set light
	Light light;
	light.position   = { 5, 5, -10 };
	light.color      = rgbColor(200, 200, 200);
	light.diffuse    = 1;
	light.ambient    = 0.05;
	light.specular_c = 1;
	light.specular_k = 50;

	// Set maximum number of light reflections to render
	int max_reflections = 4;

	// Create a vector of 3d Objects to be included in the scene
	vector<Object*> scene_objects;

	// Add scene plane Plane(position, normal, color, reflection)
	scene_objects.push_back(new Plane({ 0, -0.5, 0 }, { 0, 1, 0 }, rgbColor(33, 36, 45), 0.2));

	// Add scene spheres Sphere(center, radius, color, reflection)
	scene_objects.push_back(new Sphere({  0.75, 0.10, 1.00 }, .6, rgbColor(193, 23, 26), 0.25));
	scene_objects.push_back(new Sphere({ -0.75, 0.10, 2.25 }, .6, rgbColor(34, 152, 40), 0.30));
	scene_objects.push_back(new Sphere({ -2.75, 0.10, 3.50 }, .6, rgbColor(45, 45, 192), 0.50));

	cout << "Rendering Scene..." << endl;

	int total_frames = 240;
	for (int i = 0; i < total_frames; i++)
	{
		// Print progress
		//string filename = "renders/frame" + zeroPadInt(i) + ".bmp";
		string filename = "renders/frame" + std::to_string(i) + ".bmp";
		cout << "Frame " << i << "/" << total_frames << endl;

		// Render scene
		Scene my_scene(camera, light, max_reflections, &scene_objects);
		my_scene.render();

		// Save scene
		my_scene.saveBMP(filename.c_str());

		// Update light
		light.position.x += sin(i * 0.2);
	}

	cout << "Done! Scene saved as OutputRender.bmp" << endl;

	// Release the memory allocated to store the different objects of the scene
	for (vector<Object*>::iterator it = scene_objects.begin(); it != scene_objects.end(); it++)
		delete *it;
	scene_objects.clear();

	return 0;
}
