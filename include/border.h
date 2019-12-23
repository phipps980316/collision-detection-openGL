#pragma once
#include "coreMath.h"
#include "collisionDetail.h"
#include <algorithm>

//Border class to represent the window borders
class Border {
private:
	vector<Vector2> points; //vector to hold the start and end points of the border
	float restitution; //holds the value of restitution for the border
public:
	Border(Vector2 start, Vector2 end, float restitution); //Constructor to set up and create the border
	vector<Vector2> getPoints(); //get the points of the border
	float getRestitution(); //get the value of restitution for the border
};