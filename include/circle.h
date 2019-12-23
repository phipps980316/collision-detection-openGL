#pragma once
#include "shape.h"

//circle class to represent a circle object in the program
class Circle : public Shape{
public:
	Circle(int ID, float radius, float mass, float damping, Vector2 position, Vector2 velocity, Vector2 acceleration); //circle constructor
};