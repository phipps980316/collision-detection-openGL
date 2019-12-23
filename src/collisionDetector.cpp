#include "collisionDetector.h"

void CollisionDetector::checkCircleToCircleCollision(Circle* c1, Circle* c2, vector<CollisionDetail>& collisions) { //collision detection for 2 circles
	Vector2 c1Position = c1->getPosition(); //get the position of the first circle
	Vector2 c2Position = c2->getPosition(); //get the position of the second circle
	float c1Radius = c1->getRadius(); //get the radius of the first circle
	float c2Radius = c2->getRadius(); //get the radius of the second circle

	Vector2 axisProjection = {c2->getPosition() - c1->getPosition()}; //get the axis projection which in this case is the vector that connects the centers of the circles
	axisProjection.normalise(); //normalise the vector

	float c1CenterProjection = c1Position.scalarProduct(axisProjection); //project the center of the first circle
	float c1MaxProjection = c1CenterProjection + c1Radius; //project the rightmost point of the first circle onto the axis
	float c1MinProjection = c1CenterProjection - c1Radius; //project the leftmost point of the first circle onto the axis

	float c2CenterProjection = c2Position.scalarProduct(axisProjection); //project the center of the second circle
	float c2MaxProjection = c2CenterProjection + c2Radius; //project the rightmost point of the second circle onto the axis
	float c2MinProjection = c2CenterProjection - c2Radius; //project the leftmost point of the second circle onto the axis

	float penetration = min(c1MaxProjection, c2MaxProjection) - max(c1MinProjection, c2MinProjection); //calculate the amount that the 2 projections overlap

	if (!(c2MaxProjection >= c1MinProjection && c1MaxProjection >= c2MinProjection)) return; //if there is no overlap in the projection, return 

	Vector2 contactNormal = c1->getPosition() - c2->getPosition(); //otherwise get the contact normal which is the vector linking the 2 circles
	contactNormal.normalise(); //normalise the contact normal
	collisions.push_back(CollisionDetail(c1->getID(), c2->getID(), contactNormal, 1.0, penetration)); //compile the collision and add it to the collision vector
}

void CollisionDetector::checkCircleToPolygonCollision(Circle* c, ConvexPolygon* p, vector<CollisionDetail>& collisions) { //collision detection for a circle and a polygon
	vector<Vector2> polygonPoints = p->getPoints(); //get the points of the polygon
	vector<Vector2> axisProjections; //vector of axis to projected onto
	float penetration = INFINITY; //variable to hold the value for penetration

	for (int edgeStart = 0; edgeStart < polygonPoints.size(); edgeStart++) { //loop through every point in the polygon points vector
		int edgeEnd = (edgeStart + 1) % polygonPoints.size(); //get the end point of the edge
		axisProjections.push_back({ polygonPoints[edgeStart].x - c->getPosition().x, polygonPoints[edgeStart].y - c->getPosition().y }); //find an axis from the start point to the circle center
		axisProjections.push_back({ polygonPoints[edgeStart].x - polygonPoints[edgeEnd].x, polygonPoints[edgeStart].y - polygonPoints[edgeEnd].y }); //find an axis aligned to the edge
	}

	for (int axisIndex = 0; axisIndex < axisProjections.size(); axisIndex++) { //loop through each projection axis
		Vector2 axisProjection = axisProjections[axisIndex]; //get the current axis to project along
		axisProjection.normalise(); //normalise the axis
		float minPolygonProjection = INFINITY; //hold the value of the minimum projection
		float maxPolygonProjection = -INFINITY; //hold the value of the maximum projection
		for (int s1Point = 0; s1Point < polygonPoints.size(); s1Point++) { //loop through each point in the polygon points vector
			float projection = polygonPoints[s1Point].scalarProduct(axisProjection); //project the point onto the axis
			minPolygonProjection = min(minPolygonProjection, projection); //if the point it less than the minimum, set it as the minimum projection
			maxPolygonProjection = max(maxPolygonProjection, projection); //if the point it more than the maximum, set it as the maximum projection
		}

		float circleCenterProjection = c->getPosition().scalarProduct(axisProjection); //project the center of the circle onto the axis
		float minCircleProjection = circleCenterProjection - c->getRadius(); //project the leftmost point of circle onto the axis
		float maxCircleProjection = circleCenterProjection + c->getRadius(); //project the rightmost point of circle onto the axis

		penetration = min(min(maxPolygonProjection, maxCircleProjection) - max(minPolygonProjection, minPolygonProjection), penetration); //calculate the amount that the 2 projections overlap and if its lower than the current value, replace it

		if (!(maxCircleProjection >= minPolygonProjection && maxPolygonProjection >= minCircleProjection)) return; //if there is no overlap in the projection, return 
	}

	Vector2 contactNormal = findNormalForce(c, p); //find the contact normal 
	contactNormal.normalise(); //normalise the contact normal
	collisions.push_back(CollisionDetail(c->getID(), p->getID(), contactNormal, 1.0, penetration)); //compile the collision and add it to the collision vector
}

void CollisionDetector::checkPolygonToPolygonCollision(ConvexPolygon* p1, ConvexPolygon* p2, vector<CollisionDetail>& collisions) { //collision detection for 2 polygon
	vector<Vector2> s1 = p1->getPoints(); //get the points of the first polygon
	vector<Vector2> s2 = p2->getPoints(); //get the points of the second polygon
	vector<Vector2> temp; //temporary space to swap s1 and s2 on second pass
	float penetration = INFINITY; //variable to hold the value for penetration
	for (int shape = 0; shape < 2; shape++) { //for 2 passthroughs
		if (shape == 1) { //if on the 2nd pass, swap s1 and s2
			temp = s1;
			s1 = s2;
			s2 = temp;
		}

		for (int edgeStart = 0; edgeStart < s1.size(); edgeStart++) { //loop through each point in s1
			int edgeEnd = (edgeStart + 1) % s1.size(); //find the end point of the edge
			Vector2 axisProjection = { -(s1[edgeEnd].y - s1[edgeStart].y), s1[edgeEnd].x - s1[edgeStart].x }; //find a vector perpendicular to the edge
			axisProjection.normalise(); //normalise the projection axis

			float minS1Projection = INFINITY; //hold the value of the minimum projection of s1
			float maxS1Projection = -INFINITY; //hold the value of the maximum projection of s1
			for (int s1Point = 0; s1Point < s1.size(); s1Point++) { //loop through each point in the s1 vector
				float projection = s1[s1Point].scalarProduct(axisProjection); //project the point onto the axis
				minS1Projection = min(minS1Projection, projection); //if the point it less than the minimum, set it as the minimum projection
				maxS1Projection = max(maxS1Projection, projection); //if the point it more than the maximum, set it as the maximum projection
			}

			float minS2Projection = INFINITY; //hold the value of the minimum projection of s2
			float maxS2Projection = -INFINITY; //hold the value of the maximum projection of s2
			for (int s2Point = 0; s2Point < s2.size(); s2Point++) { //loop through each point in the s2 vector
				float projection = s2[s2Point].scalarProduct(axisProjection); //project the point onto the axis
				minS2Projection = min(minS2Projection, projection); //if the point it less than the minimum, set it as the minimum projection
				maxS2Projection = max(maxS2Projection, projection); //if the point it more than the maximum, set it as the maximum projection
			}

			penetration = min(min(maxS1Projection, maxS2Projection) - max(minS1Projection, minS2Projection), penetration); //calculate the amount that the 2 projections overlap and if its lower than the current value, replace it

			if (!(maxS2Projection >= minS1Projection && maxS1Projection >= minS2Projection)) return; //if there is no overlap in the projection, return 
		
		}
	}

	Vector2 contactNormal = findNormalForce(p1, p2); //find the contact normal 
	contactNormal.normalise(); //normalise the contact normal
	collisions.push_back(CollisionDetail(p1->getID(), p2->getID(), contactNormal, 1.0, penetration)); //compile the collision and add it to the collision vector
}

void CollisionDetector::checkCircleToBorderCollision(Circle* c, Border b, vector<CollisionDetail>& collisions) { //collision detection for a circle and a border
	vector<Vector2> borderPoints = b.getPoints(); //get the border points
	vector<Vector2> axisProjections; //vector for the projection axis
	float penetration = INFINITY; //variable to hold the value for penetration

	for (int borderStart = 0; borderStart < borderPoints.size(); borderStart++) { //loop through each border point
		int borderEnd = (borderStart + 1) % borderPoints.size(); //find the end of the edge
		axisProjections.push_back({ borderPoints[borderStart].x - c->getPosition().x, borderPoints[borderStart].y - c->getPosition().y }); //find an axis from the start point to the circle center
		axisProjections.push_back({ -(borderPoints[borderStart].y - borderPoints[borderEnd].y), borderPoints[borderStart].x - borderPoints[borderEnd].x }); //find an axis perpendicular to the border
	}

	for (int axisIndex = 0; axisIndex < axisProjections.size(); axisIndex++) { //loop through each projection axis
		Vector2 axisProjection = axisProjections[axisIndex]; //get the current axis to project along
		axisProjection.normalise(); //normalise the axis

		float minBorderProjection = INFINITY; //hold the value of the minimum projection
		float maxBorderProjection = -INFINITY; //hold the value of the maximum projection
		for (int point = 0; point < borderPoints.size(); point++) { //loop through each point in the border points vector
			float projection = borderPoints[point].scalarProduct(axisProjection); //project the point onto the axis
			minBorderProjection = min(minBorderProjection, projection); //if the point it less than the minimum, set it as the minimum projection
			maxBorderProjection = max(maxBorderProjection, projection); //if the point it more than the maximum, set it as the maximum projection
		}

		float circleCenterProjection = c->getPosition().scalarProduct(axisProjection); //project the center of the circle onto the axis
		float minCircleProjection = circleCenterProjection - c->getRadius(); //project the leftmost point of circle onto the axis
		float maxCircleProjection = circleCenterProjection + c->getRadius(); //project the rightmost point of circle onto the axis

		penetration = min(min(maxBorderProjection, maxCircleProjection) - max(minBorderProjection, minCircleProjection), penetration); //calculate the amount that the 2 projections overlap and if its lower than the current value, replace it

		if (!(maxCircleProjection >= minBorderProjection && maxBorderProjection >= minCircleProjection)) return; //if there is no overlap in the projection, return 
	}

	Vector2 contactNormal = findNormalForce(c, b); //find the contact normal 
	contactNormal.normalise(); //normalise the contact normal
	collisions.push_back(CollisionDetail(c->getID(), -1, contactNormal, b.getRestitution(), penetration)); //compile the collision and add it to the collision vector
}

void  CollisionDetector::checkPolygonToBorderCollision(ConvexPolygon* p, Border b, vector<CollisionDetail>& collisions) { //collision detection for a polygon and a border
	vector<Vector2> points = b.getPoints(); //get the border points
	float penetration = INFINITY; //variable to hold the value for penetration
	for (int borderStart = 0; borderStart < points.size(); borderStart++) { //loop through each border point
		int borderEnd = (borderStart + 1) % points.size(); //find the end of the edge
		Vector2 axisProjection = { -(points[borderEnd].y - points[borderStart].y), points[borderEnd].x - points[borderStart].x }; //find an axis perpendicular to the border
		axisProjection.normalise(); //normalise the axis

		float minBorderProjection = INFINITY; //hold the value of the minimum projection
		float maxBorderProjection = -INFINITY; //hold the value of the maximum projection
		for (int borderPoint = 0; borderPoint < points.size(); borderPoint++) { //loop through each point in the border points vector
			float projection = points[borderPoint].scalarProduct(axisProjection); //project the point onto the axis
			minBorderProjection = min(minBorderProjection, projection); //if the point it less than the minimum, set it as the minimum projection
			maxBorderProjection = max(maxBorderProjection, projection); //if the point it more than the maximum, set it as the maximum projection
		}

		float minShapeProjection = INFINITY; //hold the value of the minimum projection
		float maxShapeProjection = -INFINITY; //hold the value of the maximum projection
		vector<Vector2> shapeVertex = p->getPoints(); //get the shape points 
		for (int shapePoint = 0; shapePoint < shapeVertex.size(); shapePoint++) { //loop through each point in the shape points vector
			float projection = shapeVertex[shapePoint].scalarProduct(axisProjection); //project the point onto the axis
			minShapeProjection = min(minShapeProjection, projection); //if the point it less than the minimum, set it as the minimum projection
			maxShapeProjection = max(maxShapeProjection, projection); //if the point it more than the maximum, set it as the maximum projection
		}

		penetration = min(min(maxBorderProjection, maxShapeProjection) - max(minBorderProjection, minShapeProjection), penetration);

		if (!(maxShapeProjection >= minBorderProjection && maxBorderProjection >= minShapeProjection)) return; //if there is no overlap in the projection, return 
	}

	Vector2 contactNormal = findNormalForce(p, b); //find the contact normal 
	contactNormal.normalise(); //normalise the contact normal
	collisions.push_back(CollisionDetail(p->getID(), -1, contactNormal, b.getRestitution(), penetration)); //compile the collision and add it to the collision vector
}

Vector2 CollisionDetector::findNormalForce(Shape* s1, Shape* s2) { //find the contact normal for 2 shapes
	vector<Vector2> s2Points = s2->getPoints(); //get the points of the second shape
	Vector2 normalForce; //vector2 to hold the normal force
	float closestDistance = INFINITY; //hold the distance of the closest point to the edge

	for (int edgeStart = 0; edgeStart < s2Points.size(); edgeStart++) { //loop through each point in s2
		int edgeEnd = (edgeStart + 1) % s2Points.size(); //get the end index of the edge
		Vector2 startPoint = s2Points[edgeStart];  //get the start point
		Vector2 endPoint = s2Points[edgeEnd]; //get the end point

		Vector2 toShape = s1->getPosition() - startPoint; //get the vector from the start point to the edge
		Vector2 lineDirection = endPoint - startPoint; //get the direction of the edge

		float projected = toShape * lineDirection; //project the shape onto the edge
		float edgeSquareLength = lineDirection.squareMagnitude(); //get the square length of the edge
		float distanceToEdge = toShape.squareMagnitude() - pow(projected, 2) / edgeSquareLength; //get the distance to the edge
		if (distanceToEdge < closestDistance) { //if the distance to the edge is less than the closest distance
			closestDistance = distanceToEdge; //the distance to edge becomes the closest distance
			if (projected <= 0) { //if the shape is nearer to the start point
				normalForce = toShape.unit(); //normal is the unit vector of the vector to shape
			}
			else if (projected >= edgeSquareLength) { //if the shape is nearer to the end point
				toShape = s1->getPosition() - endPoint; //get the vector from the end point to shape
				normalForce = toShape.unit(); //normal is the unit vector of the vector to shape
			}
			else //else the shape is somewhere in the middle
			{
				Vector2 closestPoint = startPoint + lineDirection * (projected / edgeSquareLength); //find the closest point on the edge
				normalForce = (s1->getPosition() - closestPoint).unit(); //normal is the unit vector from the shape center to the closest point
			}
		}
	}
	return normalForce; //return the normal force
}

Vector2 CollisionDetector::findNormalForce(Shape* s, Border b) { //find the contact normal for a shape and a border
	Vector2 borderStart = b.getPoints()[0]; //get the border start point
	Vector2 borderEnd = b.getPoints()[1]; //get the border end point

	Vector2 toShape = s->getPosition() - borderStart; //get the vector from the shape to the start of the border
	Vector2 lineDirection = borderEnd - borderStart; //get the direction of the border
	float borderSqLength = lineDirection.squareMagnitude(); //get the square length of the border
	float projected = toShape * lineDirection; //project the shape onto the border

	Vector2 closestPoint = borderStart + lineDirection * (projected / borderSqLength); // find the closest point on the border
	Vector2 contactNormal = (s->getPosition() - closestPoint).unit(); //normal is the unit vector from the shape center to the closest point

	return contactNormal; //return the normal force
}

vector<CollisionDetail> CollisionDetector::checkShapeToShapeCollisions(vector<Shape> shapes) { //checks collisions between shapes
	vector<CollisionDetail> collisions; //vector to hold the collisions
	for (int shape1Index = 0; shape1Index < shapes.size(); shape1Index++) { //for each shape in shapes
		Shape* s1 = &shapes[shape1Index]; //get the shape
		for (int shape2Index = 0; shape2Index < shapes.size(); shape2Index++) { //for each shape in shapes
			Shape* s2 = &shapes[shape2Index]; //get the shape to check collisions against
			if (s1->getID() != s2->getID()) { //if the 2 shapes are different
				if (s1->getType() == "Circle" && s2->getType() == "Circle") { //if the 2 shapes are circles
					Circle* c1 = (Circle*)s1; //cast shape 1 as circle 1
					Circle* c2 = (Circle*)s2; //cast shape 2 as circle 2
					checkCircleToCircleCollision(c1, c2, collisions); //run circle to circle collision detection
				}
				else if (s1->getType() == "Polygon" && s2->getType() == "Polygon") { //if the 2 shapes are polygons
					ConvexPolygon* p1 = (ConvexPolygon*)s1; //cast shape 1 as polygon 1
					ConvexPolygon* p2 = (ConvexPolygon*)s2; //cast shape 2 as polygon 2
					checkPolygonToPolygonCollision(p1, p2, collisions); //run polygon to polygon collision detection
				}
				else if (s1->getType() == "Circle" && s2->getType() == "Polygon") { //if s1 is a circle, and s2 is a polygon
					Circle* c = (Circle*)s1; //cast shape 1 as a circle
					ConvexPolygon* p = (ConvexPolygon*)s2; //cast shape 2 as a polygon
					checkCircleToPolygonCollision(c, p, collisions); //run circle to polygon collision detection
				}
				else { //if s1 is a polygon, and s2 is a circle
					ConvexPolygon* p = (ConvexPolygon*)s1; //cast shape 1 as a polygon
					Circle* c = (Circle*)s2; //cast shape 2 as a circle
					checkCircleToPolygonCollision(c, p, collisions); //run circle to polygon collision detection
				}
			}
		}
	}
	return collisions; //return the collisions
}

vector<CollisionDetail> CollisionDetector::checkShapeToBorderCollisions(vector<Border> borders, vector<Shape> shapes) { //checks collisions between the shapes and the borders
	vector<CollisionDetail> collisions; //vector to hold the collisions
	for (int borderIndex = 0; borderIndex < borders.size(); borderIndex++) { //loop through each border
		Border b = borders[borderIndex]; //get the current border
		for (int shapeIndex = 0; shapeIndex < shapes.size(); shapeIndex++) { //loop through each shape
			Shape* s = &shapes[shapeIndex]; //get the current shape
			if (s->getType() == "Circle") { //if the current shape is a circle
				Circle* c = (Circle*)s; //cast as a circle
				checkCircleToBorderCollision(c, b, collisions); //run circle to border collision detection
			}
			else { //if the current shape is a polygon
				ConvexPolygon* p = (ConvexPolygon*)s; //cast as a polygon
				checkPolygonToBorderCollision(p, b, collisions); //run polygon to border collision detection
			}
		}
	}
	return collisions; // return the collisions
}