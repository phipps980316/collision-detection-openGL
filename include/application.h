#pragma once
#include <gl/glut.h>

//Application class to hold the basic opengl functions for the application window
class Application {
protected:
	int height; //holds the height of the application window
	int width; //holds the width of the application window
	float timeInterval; //holds the value for the time interval
	float nRange = 100; //holds the value for the nRange
public:
	int getHeight(); //gets the application height
	int getWidth(); //gets the application width
	float getTimeInterval(); //gets the time interval value
	void setTimeInterval(float timeInterval); //sets the time interval value
	virtual void initGraphics(); //function to initialise the opengl application
	virtual void display(); //function for the opengl application to use as its display function
	virtual void update(); //function for the opengl application to use as its update function
	virtual void resize(int width, int height); //function to resize the application window
};