#include "application.h"

int Application::getHeight() { //gets the application height
	return height; //return the application height
}

int Application::getWidth() { //gets the application width
	return width; //return the application width
}

float Application::getTimeInterval() { //gets the time interval value
	return timeInterval; //return the time interval
}

void Application::setTimeInterval(float timeInterval) { //sets the time interval value
	this->timeInterval = timeInterval; //set the time interval
}

void Application::initGraphics() {  //function to initialise the opengl application
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //clear the color buffers
}

void Application::display() { //function for the opengl application to use as its display function
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the opengl color and depth buffers
	glMatrixMode(GL_MODELVIEW); //change the matrix mode to GL_MODELVIEW
	glLoadIdentity();
}

void Application::update() { //function for the opengl application to use as its update function
	glutPostRedisplay(); //marks the current window to be updated
}

void Application::resize(int width, int height) { //function to resize the application window
	GLfloat aspectRatio = (GLfloat)width / (GLfloat)height; //calculate the aspect ratio for the window

	//Prevent a divide by zero
	if (height == 0) height = 1;

	//Set viewport to window dimensions
	glViewport(0, 0, width, height);

	//Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Establish clipping volume
	if (width <= height) {
		this->width = nRange;
		this->height = nRange / aspectRatio;
		glOrtho(-nRange, nRange, -nRange / aspectRatio, nRange / aspectRatio, -nRange * 2.0f, nRange * 2.0f);
	}
	else {
		this->width = nRange * aspectRatio;
		this->height = nRange;
		glOrtho(-nRange * aspectRatio, nRange * aspectRatio, -nRange, nRange, -nRange * 2.0f, nRange * 2.0f);
	}

	//Reset the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}