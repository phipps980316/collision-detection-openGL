#pragma once
#include "coreMath.h"
#include "shape.h"
#include <vector>

using std::vector;

class Shape; //forward declaration of the shape class

//collision detail class to hold the details about a collision
class CollisionDetail {
private:
	int p1Index = -1; //holds the id of the first shape involved in the collision
	int p2Index = -1; //holds the id of the second shape involved in the collision
	float restitution; //holds the restitution value in the collision
	Vector2 contactNormal; //holds the contact normal of the collision
	float penetration; //holds the amount that the shapes have penetrated
public:
	CollisionDetail(int P1Index, int P2Index, Vector2 contactNormal, float restitution, float penetration); //collision detail constructor
	int getP1Index(); //get the id of the first shape
	int getP2Index(); //get the id of the second shape
	float getRestitution(); //get the value of restitution
	Vector2 getContactNormal(); //get the contact normal
	float getPenetration(); //get the amount that the shapes have penetrated
};