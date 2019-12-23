#include "border.h"

Border::Border(Vector2 start, Vector2 end, float restitution) { //Constructor to set up and create the border
	points.push_back(start); //push the start point onto the points vector
	points.push_back(end); //push the end point onto the points vector
	
	this->restitution = restitution; //set the value of restitution
}

vector<Vector2> Border::getPoints() { //get the points of the border
	return points; //return the points vector
}

float Border::getRestitution() { //get the value of restitution for the border
	return restitution; //return the value of restitution
}