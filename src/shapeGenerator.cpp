#include "shapeGenerator.h"

Circle ShapeGenerator::createCircle(float radius, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration) { //function to generate a circle
	Circle generatedCircle = Circle(currentID, radius, mass, damping, position, velocity, acceleration); //create a circle object
	currentID++; //imcrement id
	return generatedCircle; //return circle
}

ConvexPolygon ShapeGenerator::createTriangle(float radius, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration) { //function to generate a triangle
	ConvexPolygon generatedTriangle = ConvexPolygon(currentID, radius, 3, mass, damping, position, velocity, acceleration); //create a triangle
	currentID++; //imcrement id
	return generatedTriangle; //return triangle
}

ConvexPolygon ShapeGenerator::createSquare(float radius, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration) { //function to generate a square
	ConvexPolygon generatedSquare = ConvexPolygon(currentID, radius, 4, mass, damping, position, velocity, acceleration); //create a square
	currentID++; //imcrement id
	return generatedSquare; //return square
}

ConvexPolygon ShapeGenerator::createPentagon(float radius, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration) { //function to generate a pentagon
	ConvexPolygon generatedPentagon = ConvexPolygon(currentID, radius, 5, mass, damping, position, velocity, acceleration); //create a pentagon
	currentID++; //imcrement id
	return generatedPentagon; //return pentagon
}

ConvexPolygon ShapeGenerator::createHexagon(float radius, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration) { //function to generate a hexagon
	ConvexPolygon generatedHexagon = ConvexPolygon(currentID, radius, 6, mass, damping, position, velocity, acceleration); //create a hexagon
	currentID++; //imcrement id
	return generatedHexagon; //return hexagon
}

ConvexPolygon ShapeGenerator::createCustom(int numberOfPoints, float radius, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration) { //function to generate a custom polygon
	ConvexPolygon generatedShape = ConvexPolygon(currentID, radius, numberOfPoints, mass, damping, position, velocity, acceleration); //create a shape
	currentID++; //imcrement id
	return generatedShape; //return shape
}