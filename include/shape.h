#pragma once
#include "coreMath.h"
#include "collisionDetail.h"
#include <vector>
#include <float.h>
#include <algorithm>
#include <string>

using namespace std;

class CollisionDetail; //forward declaration of collision detail

//shape class to represent shapes in the program
class Shape {
protected:
	int ID = -1; //shape id
	string type; //shape type
	float radius; //shape radius
	int numberOfPoints; //shapes number of points
	float inverseMass; //shapes inverse mass
	float damping; //shapes damping
	Vector2 position; //shapes position
	vector<Vector2> points; //shapes points
	Vector2 velocity; //shapes velocity
	Vector2 acceleration; //shapes acceleration
	Vector2 forceAccumulator; //shapes force accumulator

	void updateShape(); //function to update the shapes points depending on the shapes position
public:
	int getID(); //get the shapes id
	string getType(); //get the shapes type
	float getRadius(); //get the shapes radius
	float getInverseMass(); //get the shapes inverse mass
	Vector2 getPosition(); //get the shapes position
	vector<Vector2> getPoints(); //get the shapes points
	Vector2 getVelocity(); //get the shapes velocity
	Vector2 getAcceleration(); //get the shapes acceleration

	void setPosition(Vector2 position); //set the shapes position
	void setVelocity(Vector2 velocity); //set the shapes velocity

	void integrate(float duration); //function to integrate the shape
};