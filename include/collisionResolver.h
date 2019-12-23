#pragma once
#include "shape.h"

//collision resolver class to hold the functions to resolve collisions
class CollisionResolver {
private:
	float calculateSeparatingVelocity(Shape s1, Shape s2, CollisionDetail collision); //function to calculate the separating velocity
	void resolveCollision(Shape& s1, Shape& s2, CollisionDetail collision, float duration); //function to resolve the collision
	void resolvePenetration(Shape& s1, Shape& s2, CollisionDetail collision, float duration); //function to resolve the penetration
public:
	void resolveCollisions(vector<Shape>& shapes, vector<CollisionDetail> collisions, float duration); //function to resolve all collisions
};