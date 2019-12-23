#pragma once
#include "shape.h"

//convex polygon class to represent a polygon object in the program
class ConvexPolygon : public Shape {
public:
	ConvexPolygon(int ID, float radius, float noOfPoints, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 accereration); //convex polygon constructor
};