#include "shapeWorld.h"

void ShapeWorld::integrate(float duration) { //function to integrate all the shapes
	for (int index = 0; index < shapes.size(); index++) { //for each shape
		shapes[index].integrate(duration); //integrate the shape
	}
}

void ShapeWorld::run(float duration) { //function to run the program
	integrate(duration); //integrate all the shapes

	collisions.clear(); //clear all the previous collisions
	tree.clear(); //clear the quadtree
	for (int i = 0; i < shapes.size(); i++) { //for each shape
		tree.insert(shapes[i]); //insert the shape into the quadtree
	}

	for (int i = 0; i < shapes.size(); i++) { //for each shape 
		vector<Shape> shapesToCheck; //vector of shapes to check
		tree.retrieve(shapesToCheck, shapes[i]); //retrieve all shapes that are likely to collide with the current shape

		if (shapesToCheck.size() > 1) { //if there are shapes to check
			vector<CollisionDetail> returnedCollisions = detector.checkShapeToShapeCollisions(shapesToCheck); //run shape to shape detection
			collisions.insert(collisions.end(), returnedCollisions.begin(), returnedCollisions.end()); //add the returned collisions to the total collisions
		}
	}

	vector<CollisionDetail> returnedCollisions = detector.checkShapeToBorderCollisions(borders, shapes); //run shape to border collision detection
	collisions.insert(collisions.end(), returnedCollisions.begin(), returnedCollisions.end()); //add the returned collisions to the total collisions

	if (collisions.size() > 0) { //if there are collisions
		resolver.resolveCollisions(shapes, collisions, duration); //resolve all the collisions
	}
}

vector<Shape> ShapeWorld::getShapes() { //gets the shapes
	return shapes; //return shapes
}

void ShapeWorld::addShape(Shape shape) { //adds a shape to the world
	shapes.push_back(shape); //add the shape to the vector
}

vector<Border> ShapeWorld::getBorders() { //gets the borders
	return borders; //return the borders
}

void ShapeWorld::addBorder(Border border) { //adds a border to the world
	borders.push_back(border); //add the border to the vector
}