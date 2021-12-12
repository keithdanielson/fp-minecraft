#include "ArcCam.hpp"

#include <cmath>
void ArcCam::recomputeOrientation() {
	double tmp = sin(_phi)*_radius;
	double x = -tmp*sin(_theta);
	double y = _radius*cos(_phi);
	double z = tmp*cos(_theta);
	
	
	_direction = glm::vec3(x, y, z);
	_position = _direction + _lookAtPoint;
	computeViewMatrix();
}

void ArcCam::moveForward(GLfloat movementFactor) {
	if (_radius > 0.5){//do not go past the look at point
		_radius -= movementFactor;
		recomputeOrientation();
	}
}

void ArcCam::moveBackward(GLfloat movementFactor) {
	if (_radius < 5.0){//do not go too far out, then we can't see
		_radius += movementFactor;
		recomputeOrientation();
	}
}
