#pragma once
#include "shape.h"

//class to represent a quadtree data structure
class QuadTree {
private:
	int MAX_SHAPES = 1; //the maximum number of shapes allowed in a quadrant before spliting
	int MAX_LEVELS = 4; //the maximum number of levels allowed
	int level; //current level
	int x; //the x position of the bottom left corner of the quadrant
	int y; //the y position of the bottom left corner of the quadrant
	int height; //the height of the quadrant
	int width; //the width of the quadrant
	QuadTree* nodes[4] = { nullptr, nullptr, nullptr, nullptr }; //pointers to the children nodes
	vector<Shape> shapes; //shapes contained in the quadrant

public:
	QuadTree(int level, int x, int y, int height, int width); //quadtree constructor
	void clear(); //function to clear the quadtree
	void split(); //function to split the quadtree
	int getIndex(Shape shape); //function to find where the shape fits
	void insert(Shape shape); //function to insert the shape
	void retrieve(vector<Shape>& shapesLikelyToCollide, Shape shape); //function to retrieve all shapes in the quadrant
};