#include "Steve.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <CSCI441/objects.hpp>
#include <CSCI441/OpenGLUtils.hpp>
#include <iostream>
#ifndef M_PI
#define M_PI 3.14159265
#endif

Steve::Steve(GLuint shaderProgramHandle, GLint mvpMtxUniformLocation, GLint normalMtxUniformLocation, GLint materialColorUniformLocation, GLint mMtxUniformLocation ) {
    // world position placement
    position = glm::vec3(0, 8.0f, 0);

    // color
    skinColor = glm::vec3(169.0f / 255.0f, 125.0f / 255.0f, 100.0f / 255.0f);
    bodyColor = glm::vec3(14.0f / 255.0f, 174.0f / 255.0f, 174.0f / 255.0f);
    eyeColor = glm::vec3(73.0f / 255.0f, 70.0f / 255.0f, 151.0f / 255.0f);
    // body
    _colorBody = bodyColor;
    bodyScale = glm::vec3(5.0f, 3.5f, 3.5f );
    bodyTranslation = glm::vec3(0.2f, 0.0f, 0.0f);
    // arm
    armColor = skinColor;
    armScale = glm::vec3(5.3f, 2.0f, 2.0f );
    leftArmTranslation = glm::vec3(0.034f, 0.14f, 0.0f );
    rightArmTranslation = glm::vec3(0.034f, -0.14f, 0.0f );
    leftArmAngle = 0.0f;
    armRotationSpeed = M_PI / 100.0f;
    // leg
    legColor = bodyColor;
    legScale = glm::vec3(5.5f, 1.85f, 2.0f);
    leftLegTranslation = glm::vec3(-0.05f, 0.05f, 0.0f );
    rightLegTranslation = glm::vec3(-0.05f, -0.05f, 0.0f );
    leftLegAngle = 0.0f;
    legRotationSpeed = (M_PI / 100.0f) * 5.0f;
    // head
    headColor = skinColor;
    headScale = glm::vec3(3.28f, 3.28f, 3.28f );
    headTranslation = glm::vec3(0.6f, 0.0f, 0.0f );
    headAngle = 0.0f;
    headRotationSpeed = 0.01f;
    // eyes
    eyeScale = glm::vec3(1.1f, 1.1f, 0.1f );
    leftEyeTranslation = glm::vec3(0.5f, 0.10f, 1.7f );
    rightEyeTranslation = glm::vec3(0.5f, -0.10f, 1.7f );
    // SHADER
    _shaderProgramHandle                            = shaderProgramHandle;
    _shaderProgramUniformLocations.mvpMtx           = mvpMtxUniformLocation;
    _shaderProgramUniformLocations.normalMtx        = normalMtxUniformLocation;
    _shaderProgramUniformLocations.materialColor    = materialColorUniformLocation;
    _shaderProgramUniformLocations.model            = mMtxUniformLocation;
    _rotateCharacterAngle = M_PI / 2.0f;

}

void Steve::drawFullCharacter(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) {
    glUseProgram( _shaderProgramHandle );
    modelMtx = glm::rotate(modelMtx, _rotateCharacterAngle, CSCI441::Y_AXIS );
    modelMtx = glm::rotate(modelMtx, headAngle, CSCI441::Y_AXIS );
    modelMtx = glm::rotate(modelMtx, -_rotateCharacterAngle, CSCI441::Y_AXIS );
    modelMtx = glm::rotate(modelMtx, _rotateCharacterAngle, CSCI441::Z_AXIS );
    drawBody(modelMtx, viewMtx, projMtx);
    drawArm(true, modelMtx, viewMtx, projMtx);
    drawArm(false, modelMtx, viewMtx, projMtx);
    drawLeg(true, modelMtx, viewMtx, projMtx);
    drawLeg(false, modelMtx, viewMtx, projMtx);
}

void Steve::walkForwards() {
    moveBothLegs();
    moveBothArms();
}
void Steve::walkBackwards() {
    moveBothLegs();
    moveBothArms();
}

void Steve::rotateHeadLeft() {
    headAngle += headRotationSpeed;
}
void Steve::rotateHeadRight() {
    headAngle -= headRotationSpeed;
}

void Steve::moveBothLegs() {
    if (isRunning) {
        legRotationSpeed = (M_PI / 100.0f) * 20.0f;
    } else {
        legRotationSpeed = (M_PI / 100.0f) * 3.0f;
    }
    moveLeftLeg();
    moveRightLeg();
}
void Steve::moveLeftLeg() {
    if (_leftlegLtoR) {
        leftLegAngle += legRotationSpeed;
        if (leftLegAngle > 0.6) {
            _leftlegLtoR = false;
        }
    }
    else {
        leftLegAngle -= legRotationSpeed;
        if (leftLegAngle < -0.6) {
            _leftlegLtoR = true;
        }
    }
}
void Steve::moveRightLeg() {
    if (_rightlegRtoL) {
        _legAngleR += legRotationSpeed;
        if (_legAngleR > 0.6) {
            _rightlegRtoL = false;
        }
    }
    else {
        _legAngleR -= legRotationSpeed;
        if (_legAngleR < -0.6) {
            _rightlegRtoL = true;
        }
    }
}

void Steve::moveBothArms() {
    if (isRunning) {
        armRotationSpeed = (M_PI / 100.0f) * 20.0f;
    } else {
        armRotationSpeed = (M_PI / 100.0f) * 3.0f;
    }
    moveleftArm();
    moveRightArm();
}
void Steve::moveleftArm() {
    if (_leftarmLtoR) {
        leftArmAngle += armRotationSpeed;
        if (leftArmAngle > 1) {
            _leftarmLtoR = false;
        }
    }
    else {
        leftArmAngle -= armRotationSpeed;
        if (leftArmAngle < 0) {
            _leftarmLtoR = true;
        }
    }
}
void Steve::moveRightArm() {
    if (_rightarmRtoL) {
        _armAngleR += armRotationSpeed;
        if (_armAngleR > 1) {
            _rightarmRtoL = false;
        }
    }
    else {
        _armAngleR -= armRotationSpeed;
        if (_armAngleR < 0) {
            _rightarmRtoL = true;
        }
    }
}

void Steve::drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    glm::mat4 modelMtx1= glm::translate(modelMtx, bodyTranslation );
    modelMtx1 = glm::scale(modelMtx1, bodyScale );
    _computeAndSendMatrixUniforms(modelMtx1, viewMtx, projMtx);
    glUniform3fv(_shaderProgramUniformLocations.materialColor, 1, &_colorBody[0]);
    CSCI441::drawSolidCube( 0.1 );

    GLfloat ang = 0.0f;
    glm::mat4 modelMtx2 =glm::rotate( modelMtx, ang, CSCI441::X_AXIS );
    drawHead(modelMtx2, viewMtx, projMtx);
}
void Steve::drawArm(bool leftArm, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    modelMtx = glm::scale(modelMtx, armScale );

    if( leftArm ) {
        //modelMtx = glm::translate( modelMtx, armScale );
        modelMtx = glm::translate(modelMtx, leftArmTranslation );
    }
    else {
        modelMtx = glm::translate(modelMtx, rightArmTranslation );
    }

    if( leftArm ) {
        modelMtx = glm::rotate(modelMtx, -leftArmAngle, CSCI441::Y_AXIS );
    }
    else {
        modelMtx = glm::rotate(modelMtx, leftArmAngle, CSCI441::Y_AXIS );
    }

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);
    glUniform3fv(_shaderProgramUniformLocations.materialColor, 1, &armColor[0]);
    CSCI441::drawSolidCube( 0.1 );
}
void Steve::drawLeg(bool leftLeg, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    modelMtx = glm::scale(modelMtx, legScale );

    if( leftLeg ) modelMtx = glm::translate(modelMtx, leftLegTranslation );
    else modelMtx = glm::translate(modelMtx, rightLegTranslation );

    if( leftLeg ) {
        //modelMtx = glm::translate( modelMtx, glm::vec3( 1.0f, 0.0f, 0.0f ) );
        modelMtx = glm::rotate(modelMtx, leftLegAngle, CSCI441::Y_AXIS );
    }
    else {
        modelMtx = glm::rotate( modelMtx, -leftLegAngle, CSCI441::Y_AXIS );
    }

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);
    glUniform3fv(_shaderProgramUniformLocations.materialColor, 1, &legColor[0]);
    CSCI441::drawSolidCube( 0.1 );
}
void Steve::drawHead(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    glm::mat4 modelMtx1 = glm::translate(modelMtx, headTranslation );
    modelMtx1 = glm::scale(modelMtx1, headScale );
    _computeAndSendMatrixUniforms(modelMtx1, viewMtx, projMtx);
    glUniform3fv(_shaderProgramUniformLocations.materialColor, 1, &headColor[0]);
    CSCI441::drawSolidCube( 0.1 );
    drawEye(true, modelMtx, viewMtx, projMtx);  // the left eye
    drawEye(false, modelMtx, viewMtx, projMtx); // the right eye
}
void Steve::drawEye(bool leftEye, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    modelMtx = glm::scale(modelMtx, eyeScale );
    if( leftEye ) modelMtx = glm::translate(modelMtx, leftEyeTranslation );
    else modelMtx = glm::translate(modelMtx, rightEyeTranslation );
    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);
    glUniform3fv(_shaderProgramUniformLocations.materialColor, 1, &eyeColor[0]);
    CSCI441::drawSolidCube( 0.1 );
}

void Steve::_computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    glProgramUniformMatrix4fv( _shaderProgramHandle, _shaderProgramUniformLocations.mvpMtx, 1, GL_FALSE, &mvpMtx[0][0] );
    glProgramUniformMatrix4fv( _shaderProgramHandle, _shaderProgramUniformLocations.model, 1, GL_FALSE, &modelMtx[0][0] );
    glm::mat3 normalMtx = glm::mat3( glm::transpose( glm::inverse( modelMtx )));
    glProgramUniformMatrix3fv( _shaderProgramHandle, _shaderProgramUniformLocations.normalMtx, 1, GL_FALSE, &normalMtx[0][0] );
}

void Steve::jump() {
    // Jump animation here
}

void Steve::changeRun(bool run) {
    isRunning = run;
}


