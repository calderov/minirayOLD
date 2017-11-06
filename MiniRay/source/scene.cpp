#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "camera.h"
#include "object.h"
#include "sphere.h"
#include "plane.h"
#include "scene.h"

// Scene Constructor
Scene::Scene(Camera camera, Light light, int max_reflections, vector<Object*>* scene_objects)
{
	this->camera = camera;
	this->light = light;
	this->max_reflections = max_reflections;
	this->objects = *scene_objects;
}

// Scene Destructor
Scene::~Scene()
{}

TraceResult Scene::traceRay(Vector3d rayO, Vector3d rayD, Light light)
{
	// Initialize ray hit result
	TraceResult ray_hit = { false, 0, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };

	// Initialize object pointer, object index and distance to object
	Object* current_object;
	int object_index;
	double d = INFTY;

	// Find distance to the nearest object in the path of the ray
	for (size_t i = 0; i < objects.size(); i++)
	{
		current_object = objects[i];
		double current_distance = current_object->intersect(rayO, rayD);
		if (current_distance < d)
		{
			d = current_distance;
			object_index = i;
		}
	}

	// Return early if the ray did not hit any object
	if (d == INFTY)
		return ray_hit;

	// Select the nearest object
	current_object = objects[object_index];

	// Find the point of intersection on the object
	Vector3d M = rayO + rayD * d;

	// Get object normal
	Vector3d N = current_object->normalize(M);

	// Get ray to light
	Vector3d ray_to_L = light.position - M;
	ray_to_L.normalize();

	// Get ray to object
	Vector3d ray_to_O = rayO - M;
	ray_to_O.normalize();

	// Get the normalized addition of both vectors
	Vector3d ray_add = ray_to_L + ray_to_O;
	ray_add.normalize();

	// Return early if the point on the object is shadowed
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (i != object_index)
		{
			bool in_shadow = objects[i]->intersect(M + N * .0001, ray_to_L) < INFTY;
			if (in_shadow)
				return ray_hit;
		}
	}

	// Set the ray initial color
	ray_hit.color = { light.ambient, light.ambient, light.ambient };

	// Compute Lambert shading
	ray_hit.color = ray_hit.color + (current_object->color * light.diffuse * std::max(N.dot(ray_to_L), 0.0));

	// Compute Blinn-Phong shading (specular)
	ray_hit.color = ray_hit.color + light.color * light.specular_c * pow(std::max(N.dot(ray_add), 0.0), light.specular_k);

	// Format the rest of the output and return
	ray_hit.succeeded = true;
	ray_hit.object_index = object_index;
	ray_hit.M = M;
	ray_hit.N = N;

	return ray_hit;
}


// Renders the 3d scene to the screen vector
void Scene::render()
{
	// Return early if the  camera screen has no pixels to render.
	// This can happen if the specified width or height for the 
	// render resolution equals zero.
	if (camera.screen.size() == 0)
	{
		return;
	}

	double reflection;
	int reflection_depth;

	Pixel* current_pixel = nullptr;
	TraceResult ray_hit;
	Vector3d rayO;
	Vector3d rayD;

	// Loop through all pixels in the screen
	for (size_t i = 0; i < camera.screen.size(); i++)
	{
		// Get a pointer to the current pixel
		current_pixel = &camera.screen[i];

		camera.pointRayFromScreenCoord(current_pixel->x, current_pixel->y);
		rayO = camera.position;
		rayD = camera.rayTarget - camera.position;
		rayD.normalize();

		reflection = 1;
		reflection_depth = 0;

		// Trace initial rays and reflections 
		while (reflection_depth < max_reflections)
		{
			// Trace ray
			ray_hit = traceRay(rayO, rayD, light);
			if (!ray_hit.succeeded)
				break;

			// Update pixel color and reflection values
			current_pixel->color = current_pixel->color + ray_hit.color * reflection;
			reflection = reflection * objects[ray_hit.object_index]->reflection;
			reflection_depth++;

			// Reflect ray
			rayO = ray_hit.M + (ray_hit.N * 0.0001);
			rayD = (rayD - 2) * rayD.dot(ray_hit.N) * ray_hit.N;
			rayD.normalize();
		}
	}

	// Correct color if needed
	if (current_pixel && current_pixel->color.r > 1) current_pixel->color.r = 1;
	if (current_pixel && current_pixel->color.g > 1) current_pixel->color.g = 1;
	if (current_pixel && current_pixel->color.b > 1) current_pixel->color.b = 1;
}

void Scene::saveBMP(string filename)
{
	camera.saveBMP(filename);
}
