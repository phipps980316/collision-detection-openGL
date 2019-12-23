#include "application.h"
#include "shapeDemo.h"

Application* app; //object of application

void display(void) { //opengl display function
	app->display(); //use the applications display function
}

void createWindow(const char* title, int h, int w) { //opengl create window function
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //initialise the display
	glutInitWindowSize(w, h); //set the window size
	glutCreateWindow(title); //create the window with the title
}

void timerFunc(int value) { //opengl timer func
	app->update(); //call the application update function
	float timeInterval = app->getTimeInterval(); //get the time interval
	glutTimerFunc(timeInterval, timerFunc, 1); //call the opengl timer function
}

void resize(int width, int height) { //opengl resize function
	app->resize(width, height); //use the applications resize function
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv); //initalise glut
	app = new ShapeDemo(); //create a new shape demo object
	app->setTimeInterval(10); //set the time interval
	createWindow("Particle Demo", app->getHeight(), app->getWidth()); //create the window
	glutReshapeFunc(resize); //set the resize function
	glutDisplayFunc(display); //set the display function
	glutTimerFunc(app->getTimeInterval(), timerFunc, 1); //call the opengl timer function
	app->initGraphics(); //initialise the graphics
	glutMainLoop(); //call the glut main loop
	return 0;
}