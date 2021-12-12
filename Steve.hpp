#ifndef LAB05_MAYZ_HPP
#define LAB05_MAYZ_HPP

#include <GL/glew.h>

#include <glm/glm.hpp>

class Steve {
public:
    Steve(GLuint shaderProgramHandle, GLint mvpMtxUniformLocation, GLint normalMtxUniformLocation, GLint materialColorUniformLocation, GLint mMtxUniformLocation );
    void drawFullCharacter(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx );
    void walkForwards();
    void walkBackwards();
    void rotateHeadLeft();
    void rotateHeadRight();
    void jump();
    glm::vec3 position = glm::vec3(-2,0,-2);
    GLfloat headAngle = 0.0f;
    GLfloat heading = 0.0f;
    glm::vec3 fpPos = glm::vec3(0.5f, 2.5f, 0.5f);

    void changeRun(bool run);

private:
    GLfloat _headRot = 0.05;//rotation speed of heading
    bool isRunning = false;
    glm::vec3 skinColor;
    glm::vec3 bodyColor;
    glm::vec3 eyeColor;
    glm::vec3 _colorBody, bodyScale, bodyTranslation;
    glm::vec3 armColor, armScale, leftArmTranslation, rightArmTranslation;
    GLfloat leftArmAngle, _armAngleR, armRotationSpeed;
    bool _leftarmLtoR, _rightarmRtoL;
    glm::vec3 legColor, legScale, leftLegTranslation, rightLegTranslation;
    GLfloat leftLegAngle, _legAngleR, legRotationSpeed;
    bool _leftlegLtoR, _rightlegRtoL;
    glm::vec3 headColor, headScale, headTranslation;
    GLfloat headRotationSpeed;
    glm::vec3 eyeScale, leftEyeTranslation, rightEyeTranslation;

    GLuint _shaderProgramHandle;
    struct ShaderProgramUniformLocations {
        GLint mvpMtx;
        GLint normalMtx;
        GLint materialColor;
        GLint model;
    } _shaderProgramUniformLocations;
    GLfloat _rotateCharacterAngle;

    void moveBothLegs();
    void moveLeftLeg();
    void moveRightLeg();
    void moveBothArms();
    void moveleftArm();
    void moveRightArm();

    void drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;
    void drawArm(bool leftArm, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;
    void drawLeg(bool leftLeg, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;
    void drawHead(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;
    void drawEye(bool leftEye, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;
    void _computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const;
};


#endif //LAB05_MAYZ_HPP
