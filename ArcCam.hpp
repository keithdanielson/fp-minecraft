#include <CSCI441/Camera.hpp>

#ifndef ARC_CAM_HPP
#define ARC_CAM_HPP

class ArcCam : public CSCI441::Camera {
public:
    void recomputeOrientation() final;

    void moveForward(GLfloat movementFactor) final;
    void moveBackward(GLfloat movementFactor) final;
};

#endif // ARC_CAM_HPP
