#include "shapeDemo.h"

ShapeDemo::ShapeDemo() { //constructor
	width = 600; //set width 
	height = 600; //set height
	nRange = 100; //set nrange

	//set up window borders and add them to world
	float margin = 0.9999;

	Border topSide = Border({ -nRange * margin, nRange * margin }, { nRange * margin, nRange * margin }, 1);
	world.addBorder(topSide);

	Border bottomSide = Border({ -nRange * margin, -nRange * margin }, { nRange * margin, -nRange * margin }, 1);
	world.addBorder(bottomSide);

	Border leftSide = Border({ -nRange * margin, nRange * margin }, { -nRange * margin, -nRange * margin }, 1);
	world.addBorder(leftSide);

	Border rightside = Border({ nRange * margin, nRange * margin }, { nRange * margin, -nRange * margin }, 1);
	world.addBorder(rightside);

	//set up shapes and add them to world
	
	Circle c1 = generator.createCircle(10, 200, 0.9, { -85,0 }, { -25,-25 }, { 0,-9.81 });
	world.addShape(c1);

	Circle c2 = generator.createCircle(5, 50, 0.9, { 50,50 }, { -60,60 }, { 0,-9.81 });
	world.addShape(c2);

	Circle c3 = generator.createCircle(30, 100, 0.9, { 65,10 }, { 0,0 }, { 0,-9.81 });
	world.addShape(c3);

	ConvexPolygon c4 = generator.createPentagon(20, 100, 0.9, { 50,-50 }, { -50,50 }, { 0,-9.81 });
	world.addShape(c4);

	ConvexPolygon c5 = generator.createSquare(10, 50, 0.9, { 15, 15 }, { 25,25 }, { 0,-9.81 });
	world.addShape(c5);

	ConvexPolygon c6 = generator.createTriangle(5, 300, 0.9, { 0, 0 }, { 50,25 }, { 0,-9.81 });
	world.addShape(c6);
}

void ShapeDemo::display() { //function to display shapes
	Application::display(); //call superclasses display function
	vector<Border> borders = world.getBorders(); //get worlds borders
	for (int index = 0; index < borders.size(); index++) { //loop through each border and draw it
		glBegin(GL_LINES);
		glColor3f(0, 1, 1);
		Vector2 start = borders[index].getPoints()[0];
		Vector2 end = borders[index].getPoints()[1];
		glVertex2f(start.x, start.y);
		glVertex2f(end.x, end.y);
		glEnd();
	}
	vector<Shape> shapes = world.getShapes(); //get worlds shapes
	for (int index = 0; index < shapes.size(); index++) { //loop through each shape and draw it
		vector<Vector2> points = shapes[index].getPoints();
		for (int edge = 0; edge < points.size(); edge++) {
			glBegin(GL_LINES);
			glColor3f(0, 1, 1);
			Vector2 start = points[edge];
			Vector2 end = points[(edge + 1) % points.size()];
			glVertex2f(start.x, start.y);
			glVertex2f(end.x, end.y);
			glEnd();
		}
	}
	glutSwapBuffers();
}

void ShapeDemo::update() {
	float duration = timeInterval / 1000;
	world.run(duration);
	Application::update();
}