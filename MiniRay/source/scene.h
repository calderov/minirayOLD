#pragma once

#include <vector>
#include <string>

#include "typedefs.h"
#include "camera.h"
#include "object.h"
#include "sphere.h"
#include "plane.h"

using namespace std;

class Scene {
private:
	// Light
	Light _light;

	// Renderer reflections limit
	int _max_reflections;

	// Camera
	Camera _camera;

	// Scene Components (spheres and planes)
	vector<Object*> _objects;

	// Trace ray function (ray origin, ray direction, light source)
	TraceResult traceRay(Vector3d rayO, Vector3d rayD, Light light);

public:
	// Constructor and destructor
	Scene(Camera camera, Light light, int max_reflections, vector<Object*> *scene_objects);
	~Scene();

	void render();
	void saveBMP(string filename);
};
