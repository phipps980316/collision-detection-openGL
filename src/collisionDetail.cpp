#include "collisionDetail.h"
CollisionDetail::CollisionDetail(int p1Index, int p2Index, Vector2 contactNormal, float restitution, float penetration) { //collision detail constructor
	this->p1Index = p1Index; //set the id of the first shape involved
	this->p2Index = p2Index; //set the id of the second shape involved
	this->contactNormal = contactNormal; //set the contact normal of the collision
	this->restitution = restitution; //set the restitution value of the collision
	this->penetration = penetration; //set the penetration value
}

int CollisionDetail::getP1Index() { //get the id of the first shape
	return p1Index; //return the first shapes id
}

int CollisionDetail::getP2Index() { //get the id of the second shape
	return p2Index; //return thr second shapes id
}

float CollisionDetail::getRestitution() { //get the value of restitution
	return restitution; //return the value of restitution
}

Vector2 CollisionDetail::getContactNormal() { //get the contact normal
	return contactNormal; //return the contact normal
}

float CollisionDetail::getPenetration() { //get the amount that the shapes have penetrated
	return penetration; //return the penetration value
}