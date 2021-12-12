#include <CSCI441/Camera.hpp>

#ifndef FP_CAM_HPP
#define FP_CAM_HPP

class FPCam : public CSCI441::Camera {
public:
    void recomputeOrientation() final;

    void moveForward(GLfloat movementFactor);
    void moveBackward(GLfloat movementFactor);

    void turnHead(GLfloat dTheta, GLfloat dPhi);
    void setHead(GLfloat head);
};

#endif // FP_CAM_HPP
