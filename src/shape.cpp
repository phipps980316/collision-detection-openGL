#include "shape.h"

void Shape::updateShape() { //function to update the shapes points depending on the shapes position
	points.clear(); //clear the previous points
	float angle = 3.14159f * 2.0f / numberOfPoints; //calculate how much of an angle should be between each point
	for (int index = 0; index < numberOfPoints; index++) { //for the number of points
		Vector2 point; //create the point
		point.x = position.x + radius * sinf(angle * index); //calculate the x position of the point
		point.y = position.y + radius * cosf(angle * index); //calculate the y position of the point
		points.push_back(point); //add the point to the points vector
	}
}

int Shape::getID() { //get the shapes id
	return ID; //return the shapes id
}

string Shape::getType() { //get the shapes type
	return type; //return the shapes type 
}

float Shape::getRadius() { //get the shapes radius
	return radius; //return the shapes radius
}

float Shape::getInverseMass() { //get the shapes inverse mass
	return inverseMass; //return the shapes inverse mass
}

Vector2 Shape::getPosition() { //get the shapes position
	return position; //return the shapes position
}

vector<Vector2> Shape::getPoints() { //get the shapes points
	return points; //return the shapes points
}

Vector2 Shape::getVelocity() { //get the shapes velocity
	return velocity; //return the shapes velocity
}

Vector2 Shape::getAcceleration() { //get the shapes acceleration
	return acceleration; //return the shapes acceleration
}

void Shape::setPosition(Vector2 position) { //set the shapes position
	this->position = position;
}

void Shape::setVelocity(Vector2 velocity) { //set the shapes velocity
	this->velocity = velocity;
}

void Shape::integrate(float duration) { //function to integrate the shape
	if (inverseMass <= 0.0f) return; //if the inverse mass is below or equal to 0, return

	if (duration > 0) { //if the duration is above 0
		position.addScaledVector(velocity, duration); //add the velocity to the position

		Vector2 resultingAcceleration = acceleration;
		resultingAcceleration.addScaledVector(forceAccumulator, inverseMass); //add the force accumulator to the acceleration

		velocity.addScaledVector(resultingAcceleration, duration); //add the acceleration to the velocity

		velocity *= pow(damping, duration); //multiply the velocity by the damping

		forceAccumulator.clear(); //clear the force accumulator
	}
	updateShape(); //update the shapes points depending on the shapes position
}