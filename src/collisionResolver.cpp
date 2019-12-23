#include "collisionResolver.h"

float CollisionResolver::calculateSeparatingVelocity(Shape s1, Shape s2, CollisionDetail collision) { //function to calculate the separating velocity
	Vector2 relativeVelocity = s1.getVelocity(); //get the velocity of the first shape
	if (s2.getID() >= 0) relativeVelocity -= s2.getVelocity(); //get the velocity of the second shape if a second shapes exists and subtract is from the relative velocity
	return relativeVelocity * collision.getContactNormal(); //return the relative velocity multiplied by the contact normal
}

void CollisionResolver::resolveCollision(Shape& s1, Shape& s2, CollisionDetail collision, float duration) { //function to resolve the collision
	float separatingVelocity = calculateSeparatingVelocity(s1, s2, collision); //find the separating velocity

	if (separatingVelocity < 0) { //if the separating velocity is less than 0
		float newSeperatingVelocity = -separatingVelocity * collision.getRestitution(); //calculate the separating velocity with respect to the resititution
		float deltaVelocity = newSeperatingVelocity - separatingVelocity; //find the difference in the velocity
		float totalInverseMass = s1.getInverseMass(); //get the inverse mass of shape 1
		if (s2.getID() >= 0) totalInverseMass += s2.getInverseMass(); //get the inverse mass of shape 2 if one exists and add it to the total inverse mass

		if (totalInverseMass > 0) { //if the total inverse mass is greater than 0
			float impulse = deltaVelocity / totalInverseMass; //calculate the impulse
			Vector2 impulsePerIM = collision.getContactNormal() * impulse; //calculate the impulse per inverse mass with respect to the contact normal
			s1.setVelocity(s1.getVelocity() + impulsePerIM * s1.getInverseMass()); //set the new velocity of s1
			if (s2.getID() >= 0) s2.setVelocity(s2.getVelocity() + impulsePerIM * -s2.getInverseMass()); //set the new velocity of s2 if one exists
		}
	}
}

void CollisionResolver::resolvePenetration(Shape& s1, Shape& s2, CollisionDetail collision, float duration) { //function to resolve the penetration
	Vector2 s1Movement; //hold the adjustment needed to shape 1
	Vector2 s2Movement; //hold the adjustment needed to shape 2

	if (collision.getPenetration() > 0) { //if there is a penetration 
		float totalInverseMass = s1.getInverseMass(); //get the inverse mass of shape 1
		if (s2.getID() >= 0) totalInverseMass += s2.getInverseMass(); //get the inverse mass of shape 2 if one exists and add it to the total inverse mass
		if (totalInverseMass > 0) { //if the total inverse mass is greater than 0
			Vector2 movePerIMass = collision.getContactNormal() * (collision.getPenetration() / totalInverseMass);  //calculate the movement per inverse mass with respect to the contact normal
			s1Movement = movePerIMass * s1.getInverseMass(); //calculate the movement needed by s1
			if (s2.getID() >= 0) s2Movement = movePerIMass * -s2.getInverseMass(); //if a s2 exists, calculate the movement needed by s2
			s1.setPosition(s1.getPosition() + s1Movement); //apply the adjustment to s1
			if (s2.getID() >= 0) s2.setPosition(s2.getPosition() + s2Movement); //apply the adjustment to s2 if s2 exists
		}
	}
}

void CollisionResolver::resolveCollisions(vector<Shape>& shapes, vector<CollisionDetail> collisions, float duration) { //function to resolve all collisions
	for (int index = 0; index < collisions.size(); index++) { //loop through each collision
		CollisionDetail collision = collisions[index]; //get the current collision
		Shape& s1 = shapes[collision.getP1Index()]; //get the first shape involved
		if (collisions[index].getP2Index() < 0) { //if there is no second shape
			Shape emptyShape = Shape(); //create an empty shape
			resolveCollision(s1, emptyShape, collision, duration); //resolve the collision
			resolvePenetration(s1, emptyShape, collision, duration); //resolve the penetration
		}
		else { //if a second shape exists
			Shape& s2 = shapes[collision.getP2Index()]; //gets the second shape
			resolveCollision(s1, s2, collision, duration); //resolve the collision
			resolvePenetration(s1, s2, collision, duration); //resolve the penetration
		}
	}
}