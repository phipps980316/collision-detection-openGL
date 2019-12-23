#pragma once
#include "border.h"
#include "shape.h"
#include "circle.h"
#include "convexPolygon.h"
#include "collisionResolver.h"
#include "collisionDetector.h"
#include "quadTree.h"

//class to represent the world
class ShapeWorld {
private:
	vector<CollisionDetail> collisions; //vector to hold all the collisions
	CollisionResolver resolver; //object of collision resolver
	CollisionDetector detector; //object of collision detector
	QuadTree tree = QuadTree(0, -100, -100, 2 * 100, 2 * 100); //creation of a quadtree
protected:
	vector<Shape> shapes; //vector to hold all the shapes
	vector<Border> borders; //vector to hold all the borders
public:
	void integrate(float duration); //function to integrate all the shapes
	void run(float duration); //function to run the program
	vector<Shape> getShapes(); //gets the shapes
	void addShape(Shape shape); //adds a shape to the world
	vector<Border> getBorders(); //gets the borders
	void addBorder(Border border); //adds a border to the world
};