#pragma once
#include "circle.h"
#include "convexPolygon.h"
#include "border.h"

//class to generator shapes
class ShapeGenerator {
private:
	int currentID = 0; //records the current id
public:
	Circle createCircle(float radius, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration); //function to generate a circle
	ConvexPolygon createTriangle(float radius, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration); //function to generate a triangle
	ConvexPolygon createSquare(float radius, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration); //function to generate a square
	ConvexPolygon createPentagon(float radius, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration); //function to generate a pentagon
	ConvexPolygon createHexagon(float radius, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration); //function to generate a hexagon
	ConvexPolygon createCustom(int numberOfPoints, float radius, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration); //function to generate a custom polygon
};