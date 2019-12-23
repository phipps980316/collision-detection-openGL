#include "quadTree.h"

QuadTree::QuadTree(int level, int x, int y, int height, int width) { //quadtree constructor
	this->level = level; //set the quadtree level
	this->x = x; //set the x position of the quadrant
	this->y = y; //set the y position of the quadrant
	this->height = height; //set the height of the quadrant
	this->width = width; //set the width of the quadrant
}

void QuadTree::clear() { //function to clear the quadtree
	shapes.clear(); //clear the shapes vector
	for (int index = 0; index < 4; index++) { //for each child node
		if (nodes[index] != nullptr) { //if the node is not null
			nodes[index]->clear(); //call the clear function on the node
			nodes[index] = nullptr; //set the node to null pointer
		}
	}
}

void QuadTree::split() { //function to split the quadtree
	int splitWidth = width / 2; //width of the new quadrant
	int splitHeight = height / 2; //height of the new quadrant

	nodes[0] = new QuadTree(level + 1, x + splitWidth, y, splitHeight, splitWidth); //set up top right quadrant
	nodes[1] = new QuadTree(level + 1, x, y, splitHeight, splitWidth); //set up top left quadrant
	nodes[2] = new QuadTree(level + 1, x, y + splitHeight, splitHeight, splitWidth); //set up bottom left quadrant
	nodes[3] = new QuadTree(level + 1, x + splitWidth, y + splitHeight, splitHeight, splitWidth); //set up bottom right quadrant
}

int QuadTree::getIndex(Shape shape) { //function to find where the shape fits
	int index = -1; //index to return
	double widthMidPoint = x + (width / 2); //find the midpoint of the width
	double heightMidPoint = y + (height / 2); //find the midpoint of the height

	float shapeMinX = shape.getPosition().x - shape.getRadius(); //find the minimum x of the shape
	float shapeMaxX = shape.getPosition().x + shape.getRadius(); //find the maximum x of the shape
	float shapeMinY = shape.getPosition().y - shape.getRadius(); //find the minimum y of the shape
	float shapeMaxY = shape.getPosition().y + shape.getRadius(); //find the maximum y of the shape

	bool topQuadrant = shapeMinY > heightMidPoint; //shape is in the top if the min y of the shape is above the height midpoint
	bool bottomQuadrant = shapeMaxY < heightMidPoint; //shape is in the bottom if the max y of the shape is below the height midpoint
	bool leftQuadrant = shapeMaxX < widthMidPoint; //shape is in the left if the max x of the shape is less than the width midpoint
	bool rightQuadrant = shapeMinX > widthMidPoint; //shape is in the right if the max x of the shape is more than the width midpoint

	if (topQuadrant) { //if top quadrant
		if (leftQuadrant) index = 1; //and left quadrant, set index to 1
		else if (rightQuadrant) index = 0; //or right quadrant, set index to 0
	}
	else if (bottomQuadrant) { //else bottom quadrant
		if (leftQuadrant) index = 2; //and left quadrant, set index to 2
		else if (rightQuadrant) index = 3; //or right quadrant, set index to 3
	}

	return index; //return index
}

void QuadTree::insert(Shape shape) { //function to insert the shape
	if (nodes[0] != nullptr) { //if the child nodes are not null
		int index = getIndex(shape); //find the index that the shape belongs in
		if (index >= 0) { //if the index is greater than 0
			nodes[index]->insert(shape); //insert the shape into the quadrant
			return; 
		}
	}

	shapes.push_back(shape); //add the shape to the shapes vector

	if ((shapes.size() > MAX_SHAPES) && (level < MAX_LEVELS)) { //if the quadrant contains more than the max shapes and can be extended by a level
		if (nodes[0] == nullptr) split(); //split the quadrant 
		
		int position = 0; 
		while (position < shapes.size()) { // loop through the shapes in the quadrant
			int index = getIndex(shapes[position]); //find the index of the shape
			if (index != -1) { //if the index is not -1
				nodes[index]->insert(shapes[position]); //insert the shape into its new quadrant
				shapes.erase(shapes.begin() + position); //erase the shape from the original vector
			}
			else position++; //increment position
		}
	}
}

void QuadTree::retrieve(vector<Shape>& shapesLikelyToCollide, Shape shape) { //function to retrieve all shapes in the quadrant
	int index = getIndex(shape); //find the quadrant that the shape belongs in
	if (index != -1 && nodes[0] != nullptr) nodes[index]->retrieve(shapesLikelyToCollide, shape); //retrieve the shapes for the given quadrant
	shapesLikelyToCollide.insert(shapesLikelyToCollide.end(), shapes.begin(), shapes.end()); //add the retrieved shapes to the shapes likely to collide vector
}