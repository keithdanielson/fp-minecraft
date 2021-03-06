#include "FPCam.hpp"
#include <cmath>

// TODO: change code from ArcBall Cam to FP Cam
void FPCam::recomputeOrientation() {
	double tmp = sin(_phi)*_radius;
	double x = -tmp*sin(_theta);
	double y = _radius*cos(_phi);
	double z = tmp*cos(_theta);

	_direction = glm::normalize(glm::vec3(x, y, z));
    setLookAtPoint(_position + _direction);
	computeViewMatrix();
}

void FPCam::moveForward(GLfloat movementFactor) {
    double tmp = atan(_direction.x / _direction.z);
    _position += glm::vec3(_position.x * cos(tmp) * movementFactor, 0.0,
                           _position.y * sin(tmp)  * movementFactor);
	recomputeOrientation();
}

void FPCam::moveBackward(GLfloat movementFactor) {
    double tmp = atan(_direction.x / _direction.z);
    _position -= glm::vec3(_position.x * cos(tmp) * movementFactor, 0.0,
                           _position.y * sin(tmp) * movementFactor);
    recomputeOrientation();
}
void FPCam::turnHead(GLfloat dTheta, GLfloat dPhi) {
    _theta += dTheta;           // update theta
    _phi += dPhi;               // update phi
    recomputeOrientation();
}

void FPCam::setHead(GLfloat head){
_theta = head;
}
