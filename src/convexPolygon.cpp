#include "convexPolygon.h"

ConvexPolygon::ConvexPolygon(int ID, float radius, float numberOfPoints, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration) { //convex polygon constructor
	this->ID = ID; //set the polygon's id
	type = "Polygon"; //set the type of the shape to polygon
	this->radius = radius; //set the radius of the polygon
	this->numberOfPoints = numberOfPoints; //set the number of points of the polygon
	this->damping = damping; //set the damping of the polygon
	this->position = position; //set the position of the polygon
	this->velocity = velocity; //set the velocity of the polygon
	this->acceleration = acceleration; //set the acceleration of the polygon

	if (mass > 0) inverseMass = 1.0 / mass; //convert the mass to inverse mass
	else inverseMass = 0;

	updateShape(); //update where the points on the polygon are depending on the position
	forceAccumulator.clear(); //clear the force accumulator
}