#pragma once
#include "shape.h"
#include "border.h"
#include "circle.h"
#include "convexPolygon.h"

//collision detector class to hold the collision detection functions
class CollisionDetector {
private:
	void checkCircleToCircleCollision(Circle* c1, Circle* c2, vector<CollisionDetail>& collisions); //collision detection for 2 circles
	void checkCircleToPolygonCollision(Circle* c, ConvexPolygon* p, vector<CollisionDetail>& collisions); //collision detection for a circle and a polygon
	void checkPolygonToPolygonCollision(ConvexPolygon* p1, ConvexPolygon* p2, vector<CollisionDetail>& collisions); //collision detection for 2 polygon
	void checkCircleToBorderCollision(Circle* c, Border b, vector<CollisionDetail>& collisions); //collision detection for a circle and a border
	void checkPolygonToBorderCollision(ConvexPolygon* p, Border b, vector<CollisionDetail>& collisions); //collision detection for a polygon and a border
	Vector2 findNormalForce(Shape* s1, Shape* s2); //find the contact normal for 2 shapes
	Vector2 findNormalForce(Shape* s, Border b); //find the contact normal for a shape and a border
public:
	vector<CollisionDetail> checkShapeToShapeCollisions(vector<Shape> shapes); //checks collisions between shapes
	vector<CollisionDetail> checkShapeToBorderCollisions(vector<Border> borders, vector<Shape> shapes); //checks collisions between the shapes and the borders
};