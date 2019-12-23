#pragma once
#include "application.h"
#include "shapeWorld.h"
#include "shapeGenerator.h"

//shape demo class to represent the program
class ShapeDemo : public Application {
private: 
	ShapeWorld world; //object of shape world 
	ShapeGenerator generator; //object of shape generator
public:
	ShapeDemo(); //constructor
	virtual void display(); //function to display shapes
	virtual void update(); //function to update displays
};