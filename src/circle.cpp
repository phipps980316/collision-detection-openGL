#include "circle.h"

Circle::Circle(int ID, float radius, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration) { //circle constructor
	this->ID = ID; //set the circle's id
	type = "Circle"; //set the type of the shape to circle
	this->radius = radius; //set the radius of the circle
	numberOfPoints = 30; //set the number of points in the circle
	this->damping = damping; //set the damping value of the circle
	this->position = position; //set the position of the circle
	this->velocity = velocity; //set the velocity of the circle
	this->acceleration = acceleration; //set the acceleration of the circle

	if (mass > 0) inverseMass = 1.0 / mass; //convert the mass to the inverse mass
	else inverseMass = 0;

	updateShape(); //update where the points on the circle are depending on the position
	forceAccumulator.clear(); //clear the force accumulator
}