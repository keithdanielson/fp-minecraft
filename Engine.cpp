#include "Engine.hpp"

#include <CSCI441/objects.hpp>
#include<iostream>
#include<map>
//*************************************************************************************
//
// Helper Functions

#ifndef M_PI
#define M_PI 3.14159265
#endif

//*************************************************************************************
//
// Public Interface

Engine::Engine(int OPENGL_MAJOR_VERSION, int OPENGL_MINOR_VERSION,
                         int WINDOW_WIDTH, int WINDOW_HEIGHT, const char* WINDOW_TITLE)
         : CSCI441::OpenGLEngine(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE) {

    for(auto& _key : _keys) _key = GL_FALSE;
    for(auto& _rep : _repeat) _rep = GL_FALSE;
    _mousePosition = glm::vec2(MOUSE_UNINITIALIZED, MOUSE_UNINITIALIZED );
    _leftMouseButtonState = GLFW_RELEASE;
}

Engine::~Engine() {
    delete _arcCam;
    delete _freeCam;
}

void Engine::handleKeyEvent(GLint key, GLint action) {
    if(key != GLFW_KEY_UNKNOWN){
	if (key == GLFW_KEY_0){
        _keys[key] = ((action == GLFW_RELEASE));
    }
    else{
        _keys[key] = ((action == GLFW_PRESS) || (action == GLFW_REPEAT));
    }

    }
    if(action == GLFW_PRESS) {
        switch( key ) {
            case GLFW_KEY_Q:
            case GLFW_KEY_ESCAPE:
                setWindowShouldClose();
                break;

            default: break; // suppress CLion warning
        }
    }
}

void Engine::handleMouseButtonEvent(GLint button, GLint action) {
    // if the event is for the left mouse button
    if( button == GLFW_MOUSE_BUTTON_LEFT ) {
        // update the left mouse button's state
        _leftMouseButtonState = action;

    }
    if( button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS){
        _rightPressed = true;
    } else {
        _rightPressed = false;
    }
}

void Engine::handleCursorPositionEvent(glm::vec2 currMousePosition) {
    // if mouse hasn't moved in the window, prevent camera from flipping out
    if(_mousePosition.x == MOUSE_UNINITIALIZED) {
        _mousePosition = currMousePosition;
    }
    // if the left mouse button is being held down while the mouse is moving
    if(_leftMouseButtonState == GLFW_PRESS) {
        // rotate the camera by the distance the mouse moved
        _arcCam->rotate((currMousePosition.x - _mousePosition.x) * 0.005f,
                         (_mousePosition.y - currMousePosition.y) * 0.005f );
        _freeCam->rotate((currMousePosition.x - _mousePosition.x) * 0.005f,
                        (_mousePosition.y - currMousePosition.y) * 0.005f );
    }
    _mousePosition = currMousePosition;
}

//*************************************************************************************
//
// Engine Setup

void Engine::_setupGLFW() {
    CSCI441::OpenGLEngine::_setupGLFW();
    // set our callbacks
    glfwSetKeyCallback(_window, keyboard_callback);
    glfwSetMouseButtonCallback(_window, mouse_button_callback);
    glfwSetCursorPosCallback(_window, cursor_callback);
    glfwSetScrollCallback(_window, mouse_scroll_callback);
}

void Engine::_setupOpenGL() {
    glEnable( GL_DEPTH_TEST );					                    // enable depth testing
    glDepthFunc( GL_LESS );							                // use less than depth test
    glEnable(GL_BLEND);									            // enable blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	            // use one minus blending equation
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );	// clear the frame buffer to black
}

void Engine::_setupShaders() {
    _lightingShaderProgram = new CSCI441::ShaderProgram("shaders/final_project.v.glsl", "shaders/final_project.f.glsl" );
    _lightingShaderUniformLocations.mvpMatrix      = _lightingShaderProgram->getUniformLocation("mvpMatrix");
    _lightingShaderUniformLocations.model      = _lightingShaderProgram->getUniformLocation("model");
    
    _lightingShaderUniformLocations.normMat  = _lightingShaderProgram->getUniformLocation("normMat");
    _lightingShaderUniformLocations.lDir  = _lightingShaderProgram->getUniformLocation("lDir");
    _lightingShaderUniformLocations.lCol  = _lightingShaderProgram->getUniformLocation("lCol");

    _lightingShaderUniformLocations.materialColor  = _lightingShaderProgram->getUniformLocation("materialColor");
    _lightingShaderUniformLocations.viewPos  = _lightingShaderProgram->getUniformLocation("viewPos");
    
    _lightingShaderAttributeLocations.vPos         = _lightingShaderProgram->getAttributeLocation("vPos");
    _lightingShaderAttributeLocations.vNorm         = _lightingShaderProgram->getAttributeLocation("vNorm");

    _lightingShaderUniformLocations.dirBool = _lightingShaderProgram->getUniformLocation("dirBool");

    _pointLight.pos = _lightingShaderProgram->getUniformLocation("pointPos");
    _pointLight.col = _lightingShaderProgram->getUniformLocation("pointCol");

    _spotlight.pos = _lightingShaderProgram->getUniformLocation("spotPos");
    _spotlight.col = _lightingShaderProgram->getUniformLocation("spotCol");

    _spotlight.dir = _lightingShaderProgram->getUniformLocation("spotDir");
    _setupBlockShader();

    _textureShaderProgram = new CSCI441::ShaderProgram("shaders/sb.v.glsl", "shaders/sb.f.glsl" );
    // query uniform locations
    _textureShaderUniformLocations.mvpMatrix      = _textureShaderProgram->getUniformLocation("mvpMatrix");
    _textureShaderUniformLocations.ourTexture      = _textureShaderProgram->getUniformLocation("ourTexture");
    // query attribute locations
    _textureShaderAttributeLocations.vPos         = _textureShaderProgram->getAttributeLocation("vPos");
    _textureShaderAttributeLocations.vNormal      = _textureShaderProgram->getAttributeLocation("vNormal");
    _textureShaderAttributeLocations.aTexCoord      = _textureShaderProgram->getAttributeLocation("aTexCoord");

    // set static uniforms
    _textureShaderProgram->setProgramUniform(_texHandles[TEXTURE_ID::METAL], 0); // ????
    CSCI441::setVertexAttributeLocations(_textureShaderAttributeLocations.vPos,
                                         _textureShaderAttributeLocations.vNormal, _textureShaderAttributeLocations.aTexCoord );


}

void Engine::_setupBlockShader(){
    _blockShaderProgram = new CSCI441::ShaderProgram("shaders/block.v.glsl", "shaders/block.f.glsl" );
    // attributes
    _blockShaderAttributeLocations.vPos = _blockShaderProgram->getAttributeLocation("vPos");
    _blockShaderAttributeLocations.texCoord = _blockShaderProgram->getAttributeLocation("textCordinateIn");
    _blockShaderAttributeLocations.vertexNormal = _blockShaderProgram->getAttributeLocation("vertexNormal");
    _blockShaderAttributeLocations.instanceMatrix = _blockShaderProgram->getAttributeLocation("instanceMatrix");

    // uniforms
    _blockShaderUniformLocations.projection = _blockShaderProgram->getUniformLocation("projection");
    _blockShaderUniformLocations.view = _blockShaderProgram->getUniformLocation("view");
    _blockShaderUniformLocations.textureMap = _blockShaderProgram->getUniformLocation("textureMap");


}

void Engine::_setupBuffers() {
    CSCI441::setVertexAttributeLocations( _lightingShaderAttributeLocations.vPos, _lightingShaderAttributeLocations.vNorm );

    // Character
    _steve = new Steve(_lightingShaderProgram->getShaderProgramHandle(),
                       _lightingShaderUniformLocations.mvpMatrix,
                       _lightingShaderUniformLocations.normMat,
                       _lightingShaderUniformLocations.materialColor,
                       _lightingShaderUniformLocations.model
                       );

    // Textures
    _textureManager = new TextureManager();
    _textureManager->LoadTextures("textures/");

    // Blocks
    Block *stoneBlock = new Block();
    stoneBlock->setupBlock(_blockShaderProgram->getShaderProgramHandle(),
                           _blockShaderUniformLocations.projection,
                           _blockShaderUniformLocations.view,
                           _blockShaderUniformLocations.textureMap,
                           _blockShaderAttributeLocations.vPos,
                           _blockShaderAttributeLocations.vertexNormal,
                           _blockShaderAttributeLocations.texCoord);
    stoneBlock->setTexture("dirt", _textureManager->getTextureHandle("dirt"));

    // Chunks
    _chunk = new Chunk(stoneBlock);
    _chunk->generateChunk(glm::vec3(0,0,0));
}

GLuint Engine::_loadAndRegisterTexture(const char* FILENAME) {
    // our handle to the GPU
    GLuint textureHandle = 0;

    // enable setting to prevent image from being upside down
    stbi_set_flip_vertically_on_load(true);

    // will hold image parameters after load
    GLint imageWidth, imageHeight, imageChannels;
    // load image from file
    GLubyte* data = stbi_load( FILENAME, &imageWidth, &imageHeight, &imageChannels, 0);

    // if data was read from file
    if( data ) {
        const GLint STORAGE_TYPE = (imageChannels == 4 ? GL_RGBA : GL_RGB);

        // TODO #01
        glGenTextures(1, &textureHandle);
        // TODO #02
        glBindTexture(GL_TEXTURE_2D, textureHandle);
        // TODO #03
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // TODO #04
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // TODO #05
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        // TODO #06
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // TODO #07
        glTexImage2D(GL_TEXTURE_2D, 0, STORAGE_TYPE, imageWidth, imageHeight, 0, STORAGE_TYPE, GL_UNSIGNED_BYTE, data);

        fprintf( stdout, "[INFO]: %s texture map read in with handle %d\n", FILENAME, textureHandle);

        // release image memory from CPU - it now lives on the GPU
        stbi_image_free(data);
    } else {
        // load failed
        fprintf( stderr, "[ERROR]: Could not load texture map \"%s\"\n", FILENAME );
    }

    // return generated texture handle
    return textureHandle;
}

void Engine::_setupTextures() {

    _texHandles[TEXTURE_ID::MINES] = _loadAndRegisterTexture("textures/skybox.jpg");

}


void Engine::_setupScene() {
    // arcball camera
    _arcCam = new ArcCam();
    _arcCam->setPosition( glm::vec3(60.0f, 40.0f, 30.0f) );
    _arcCam->setTheta( -M_PI / 3.0f );
    _arcCam->setPhi( M_PI / 3.0f );
    selectedHero = 3;
    _arcCam->setLookAtPoint(_steve->position);
    _arcCam->recomputeOrientation();
    _cameraSpeed = glm::vec2(0.05f, 0.02f);
    // free camera
    _freeCam = new CSCI441::FreeCam();//setup Free cam, is this a problem?
    _freeCam->setPosition( glm::vec3(60.0f, 40.0f, 30.0f) );
    _freeCam->setTheta( -M_PI / 3.0f );
    _freeCam->setPhi( M_PI / 2.8f );
    _freeCam->recomputeOrientation();
    // TODO finish implementing the first person camera
    // first person camera
    _fpCam = new FPCam();
    _fpCam->setTheta( -M_PI / 3.0f );
    _fpCam->recomputeOrientation();
    
    glm::vec3 pos = glm::vec3(-WORLD_SIZE/2,10,-WORLD_SIZE/2);
    glm::vec3 col = glm::vec3(0,1,0);
    glProgramUniform3fv(_lightingShaderProgram->getShaderProgramHandle(),
                        _pointLight.pos,
                        1,&pos[0]);
    glProgramUniform3fv(_lightingShaderProgram->getShaderProgramHandle(),
                        _pointLight.col,
                        1,&col[0]);
    glm::vec3 pcol = glm::vec3(1, 0, 0);
    glm::vec3 pdir = glm::vec3(0,-1.0f,0);
    glm::vec3 ppos = glm::vec3(WORLD_SIZE/2,10, WORLD_SIZE/2);
    glProgramUniform3fv(_lightingShaderProgram->getShaderProgramHandle(),
                        _spotlight.pos,
                        1,&ppos[0]);
    glProgramUniform3fv(_lightingShaderProgram->getShaderProgramHandle(),
                        _spotlight.col,
                        1,&pcol[0]);
    glProgramUniform3fv(_lightingShaderProgram->getShaderProgramHandle(),
                        _spotlight.dir,
                        1,&pdir[0]);

    glm::vec3 lDir = glm::vec3(-1,-1,-1);
    glm::vec3 lCol = glm::vec3(1,1,1);
	glProgramUniform3fv(_lightingShaderProgram->getShaderProgramHandle(),
			_lightingShaderUniformLocations.lDir,
			1,&lDir[0]);
	glProgramUniform3fv(_lightingShaderProgram->getShaderProgramHandle(),
			_lightingShaderUniformLocations.lCol,
			1,&lCol[0]);
}

//*************************************************************************************
//
// Engine Cleanup

void Engine::_cleanupShaders() {
    fprintf( stdout, "[INFO]: ...deleting Shaders.\n" );
    delete _lightingShaderProgram;
    delete _textureShaderProgram;
}

void Engine::_cleanupTextures() {
    fprintf( stdout, "[INFO]: ...deleting textures\n" );
    glDeleteTextures(1, &_texHandles[TEXTURE_ID::METAL]);
    glDeleteTextures(1, &_texHandles[TEXTURE_ID::MINES]);
}


void Engine::_cleanupBuffers() {
    fprintf( stdout, "[INFO]: ...deleting VAOs....\n" );
    CSCI441::deleteObjectVAOs();
    glDeleteVertexArrays( 1, &_groundVAO );

    fprintf( stdout, "[INFO]: ...deleting VBOs....\n" );
    CSCI441::deleteObjectVBOs();

    fprintf( stdout, "[INFO]: ...deleting models..\n" );
    delete _steve;
}

//*************************************************************************************
//
// Rendering / Drawing Functions - this is where the magic happens!

void Engine::_renderScene(glm::mat4 viewMtx, glm::mat4 projMtx) {

    // use our lighting shader program
    _lightingShaderProgram->useProgram();
    glUniform1i(_lightingShaderUniformLocations.dirBool, 1);

    //// BEGIN SETING LOOK AT LOCAL///
    glm::vec3 viewPos;
    if(selectedHero != -1){
        if ( camera == 1 ) viewPos = _arcCam->getPosition();
        if ( camera == 2 ) viewPos = _fpCam->getPosition();
    }
    else{
	    viewPos = _freeCam->getPosition();
    }
    glUniform3fv(_lightingShaderUniformLocations.viewPos, 1, &viewPos[0]);
    //// END SETING LOOK AT LOCAL///

    //// BEGIN DRAWING THE MODELS ////
    glm::mat4 modelMtx(1.0f);
    // we are going to cheat and use our look at point to place our model so that it is always in view
    glm::mat4 modelMtxSteve = glm::translate(modelMtx, _steve->position);
    _steve->drawFullCharacter(modelMtxSteve, viewMtx, projMtx);
    //// END DRAWING MODELS ////
    _chunk->drawChunk(viewMtx, projMtx);

    // Skybox from previous assignment
    //***************************************************************************

    _textureShaderProgram->useProgram();

    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.1f, 0.0f));
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMatrix;
    _textureShaderProgram->setProgramUniform(_textureShaderUniformLocations.mvpMatrix, mvpMtx);

    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 2.1f, 0.0f));
    //modelMatrix = glm::rotate( modelMatrix, _objectAngle, CSCI441::Y_AXIS );
    mvpMtx = projMtx * viewMtx * modelMatrix;
    _textureShaderProgram->setProgramUniform(_textureShaderUniformLocations.mvpMatrix, mvpMtx);


    glBindTexture(GL_TEXTURE_2D, _texHandles[TEXTURE_ID::MINES]);
    // draw all the cool stuff!
    CSCI441::drawSolidSphere( 200.0f, 200.0f, 200.0f );

    CSCI441::setVertexAttributeLocations(_textureShaderAttributeLocations.vPos,
                                         _textureShaderAttributeLocations.vNormal, _textureShaderAttributeLocations.aTexCoord );


    //***************************************************************************

}

void Engine::_updateScene() {
    nearestYBelowCharacter = _chunk->getHeightMap()[std::make_pair(int(_steve->position.x + 0.5), int(_steve->position.z + 0.5))] + 1.5;

    //Running
    if (characterIsRunning) {
        characterSpeed = SPRINT_SPEED;
        _steve->changeRun(true);
    } else {
        characterSpeed = WALK_SPEED;
        _steve->changeRun(false);
    }
    //Gravity
    if (_steve->position[1] > nearestYBelowCharacter && !characterIsJumping) {
        if (_steve->position[1] - 0.5 < nearestYBelowCharacter) {
            _steve->position = glm::vec3(_steve->position[0], nearestYBelowCharacter, _steve-> position[2]);
        } else {
            _steve->position = glm::vec3(_steve->position[0], _steve->position[1] - 0.5, _steve-> position[2]);
        }
        _arcCam->setLookAtPoint(_steve->position);
        _arcCam->recomputeOrientation();
    }
    //Jumping
    if (characterIsJumping) {
        glm::vec3 pos = _steve->position;

        currentJumpTravel += 0.5;
        if (currentJumpTravel >= maxJumpHeight) {
            characterIsJumping = false;
            currentJumpTravel = 0.0;
        }
        pos[1] += _cameraSpeed.x + 0.5;
        _steve->position = pos;
        _arcCam->setLookAtPoint(_steve->position);
        _arcCam->recomputeOrientation();

    }
    // whenever a hero is selected -> arcball and first person
    if (selectedHero != -1){
        // arcball camera
        if ( camera == 1 ) {
            switch (selectedHero) {
                case 3: // Steve
                    // turn head right
                    if (_keys[GLFW_KEY_D]) {
                        _steve->rotateHeadRight();
                    }
                    // turn head left
                    if (_keys[GLFW_KEY_A]) {
                        _steve->rotateHeadLeft();
                    }
                    // walk forward
                    if (_keys[GLFW_KEY_W]) {

                        _steve->walkForwards();
                        glm::vec3 pos = _steve->position;
                        GLfloat head = _steve->headAngle;//get which dir the vehicle is faceing

                        pos[0] += sin(head) * _cameraSpeed.x * characterSpeed;
                        pos[2] += cos(head) * _cameraSpeed.x * characterSpeed;
                        std::cout << _steve->position.y;
                        if (nearestYBelowCharacter > pos[1]) {
                            pos[0] -= sin(head) * _cameraSpeed.x * (characterSpeed * 2.5);
                            pos[2] -= cos(head) * _cameraSpeed.x * (characterSpeed * 2.5);
                            _steve->position = pos;
                        } else {
                            _steve->position = pos;
                        }


                        _arcCam->setLookAtPoint(_steve->position);
                        _arcCam->recomputeOrientation();
                    }
                    // walk backward
                    if (_keys[GLFW_KEY_S]) {
                        _steve->walkBackwards();
                        glm::vec3 pos = _steve->position;
                        GLfloat head = _steve->headAngle;//get which dir the vehicle is faceing

                        pos[0] -= sin(head) * _cameraSpeed.x * characterSpeed;
                        pos[2] -= cos(head) * _cameraSpeed.x * characterSpeed;
                        if (nearestYBelowCharacter > pos[1]) {
                            pos[0] += sin(head) * _cameraSpeed.x * (characterSpeed * 2.5);
                            pos[2] += cos(head) * _cameraSpeed.x * (characterSpeed * 2.5);
                            _steve->position = pos;
                        } else {
                            _steve->position = pos;
                        }
                        _arcCam->setLookAtPoint(_steve->position);
                        _arcCam->recomputeOrientation();
                    }
                    //jump
                    if (_keys[GLFW_KEY_SPACE]) {
                        characterIsJumping = true;
                        if (currentJumpTravel >= maxJumpHeight) {
                            jumpFalling = true;
                        }

                    }
                    //Toggle if character is running or not
                    if (_keys[GLFW_KEY_LEFT_SHIFT]) {
                        characterIsRunning = true;
                    } else {
                        characterIsRunning = false;
                    }
                    break;

                default:
                    break;
            }
        }
        // fp camera
        if ( camera == 2 ) {
            // turn right
            switch (selectedHero) {
                case 3: // steve

                    if (_keys[GLFW_KEY_D]) {
                        _steve->rotateHeadRight();
                    }
                    // turn head left
                    if (_keys[GLFW_KEY_A]) {
                        _steve->rotateHeadLeft();
                    }
                    // walk forward
                    if (_keys[GLFW_KEY_W]) {
                        _steve->walkForwards();
                        _fpCam->moveForward(0.1);
                        glm::vec3 pos = _steve->position;
                        GLfloat head = _steve->headAngle;//get which dir the vehicle is faceing
                        glm::vec3 point = _steve->fpPos;

                        _fpCam->setPosition(pos + point);
                        _fpCam->setHead(-head);
                        _fpCam->recomputeOrientation();
                    }
                    // walk backward
                    if (_keys[GLFW_KEY_S]) {
                        _steve->walkBackwards();
                        _fpCam->moveBackward(0.1);
                        glm::vec3 pos = _steve->position;
                        GLfloat head = _steve->headAngle;//get which dir the vehicle is faceing
                        glm::vec3 point = _steve->fpPos;

                        auto tmp = (glm::rotate(glm::mat4(1.0f),head,CSCI441::Y_AXIS) * glm::vec4(point, 1.0));
                        point = glm::vec3(tmp[0],tmp[1],tmp[2]);
                        _fpCam->setPosition(pos + point);
                        _fpCam->setHead(-head);
                        _fpCam->recomputeOrientation();
                    }

			 {
                        glm::vec3 pos = _steve->position;
                        GLfloat head = _steve->headAngle;//get which dir the vehicle is faceing
                        glm::vec3 point = _steve->fpPos;

                        auto tmp = (glm::rotate(glm::mat4(1.0f),head,CSCI441::Y_AXIS) * glm::vec4(point, 1.0));
                        point = glm::vec3(tmp[0],tmp[1],tmp[2]);
                        _fpCam->setPosition(pos + point);
                        _fpCam->setHead(-head);
                        _fpCam->recomputeOrientation();
                    }
			break;

                   // break;

                default:
                    break;
            }
        }
    }
    else { // free cam
		if( _keys[GLFW_KEY_W] ) {
            _freeCam->moveForward(_cameraSpeed.x * 5);
        }
        else if (_keys[GLFW_KEY_S]) {
            _freeCam->moveBackward(_cameraSpeed.x*5);
        }else if (_keys[GLFW_KEY_G]){
            _freeCam->recomputeOrientation();
            for (float i = .1; i <= 4; i = i + 0.01f){
                GLfloat x = GLfloat(i);
                glm::vec3 direction = x * _freeCam->getDirectionVec()  + _freeCam->getPosition();
                if (_chunk->deleteBlock(int(direction.x), int(direction.y), int(direction.z))){
                    _keys[GLFW_KEY_G] = false;
                    break;
                }
            }
        }
        else if (_keys[GLFW_KEY_T]){
            glm::vec3 prev_direction = 0.05f * _freeCam->getDirectionVec()  + _freeCam->getPosition();
            printf("\n\n\n");
            for (float i = .1; i <= 4; i = i + 0.01f){
                GLfloat x = GLfloat(i);
                glm::vec3 direction = x * _freeCam->getDirectionVec()  + _freeCam->getPosition();
                if (_chunk->findBlock(int(direction.x), int(direction.y), int(direction.z))){
                    _chunk->addBlock((int)prev_direction.x, (int)prev_direction.y, (int)prev_direction.z);
                    break;
                }
                prev_direction = direction;
            }
        }
    }
    // switching POV
    // 1: Hero, 2: FreeCam, 3: toggle POV
    // 1: Arcball Steve: 2: FP Steve 3: Freecam
    // Camera: Arcball
    if(_keys[GLFW_KEY_1]){ //Steve
	    selectedHero = 3;
        camera = 1;
        _arcCam->setLookAtPoint(_steve->position);
	    _arcCam->recomputeOrientation();
        _currentCamera = _arcCam;
    }
    // Camera: FreeCam
    // Camera: First Person
    if(_keys[GLFW_KEY_2] and selectedHero != -1){
        povDisplayed ^= true;
        camera = 2;
        _currentCamera = _fpCam;
	_keys[GLFW_KEY_2] = false;//consume that input
    }
    if(_keys[GLFW_KEY_3]){
        selectedHero = -1;//no hero free roam
        camera = 3;
        povDisplayed = false;
        _currentCamera = _freeCam;
    }

//    for (int i = 1; i <= 10; ++i){
//        GLfloat x = GLfloat(i);
//        glm::vec3 direction = x * _freeCam->getDirectionVec()  + _freeCam->getPosition();
////                if (_chunk->deleteBlock(int(direction.x), int(direction.y), int(direction.z))){
////                    _keys[GLFW_KEY_T] = false;
////                    break;
////                }
//    }
}

GLuint Engine::loadCubeMap(std::vector<std::string> faces){
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}
void Engine::run() {
    //  This is our draw loop - all rendering is done here.  We use a loop to keep the window open
    //	until the user decides to close the window and quit the program.  Without a loop, the
    //	window will display once and then the program exits.
    while( !glfwWindowShouldClose(_window) ) {	        // check if the window was instructed to be closed
        glDrawBuffer( GL_BACK );				        // work with our back frame buffer
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// clear the current color contents and depth buffer in the window

        // Get the size of our framebuffer.  Ideally this should be the same dimensions as our window, but
        // when using a Retina display the actual window can be larger than the requested window.  Therefore,
        // query what the actual size of the window we are rendering to is.
        GLint framebufferWidth, framebufferHeight;
        glfwGetFramebufferSize( _window, &framebufferWidth, &framebufferHeight );

        // update the viewport - tell OpenGL we want to render to the whole window
        glViewport( 0, 0, framebufferWidth, framebufferHeight );

        // set the projection matrix based on the window size
        // use a perspective projection that ranges
        // with a FOV of 45 degrees, for our current aspect ratio, and Z ranges from [0.001, 1000].
        glm::mat4 projectionMatrix = glm::perspective( 45.0f, (GLfloat) framebufferWidth / (GLfloat) framebufferHeight, 0.001f, 1000.0f );

        // set up our look at matrix to position our camera

	    glm::mat4 viewMatrix;
        if(selectedHero != -1){
            if ( camera == 1) {
                viewMatrix = _arcCam->getViewMatrix();
            }
            if ( camera == 2) {
                viewMatrix = _fpCam->getViewMatrix();
            }
        }
	    else {
            viewMatrix = _freeCam->getViewMatrix();
       	}
        // draw everything to the window
        _renderScene(viewMatrix, projectionMatrix);


        _updateScene();
        glfwSwapBuffers(_window);                       // flush the OpenGL commands and make sure they get rendered!
        glfwPollEvents();				                // check for any events and signal to redraw screen
    }
}

//*************************************************************************************
//
// Private Helper FUnctions

void Engine::_computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    _lightingShaderProgram->setProgramUniform(_lightingShaderUniformLocations.mvpMatrix, mvpMtx);
    _lightingShaderProgram->setProgramUniform(_lightingShaderUniformLocations.model, modelMtx);

    glm::mat3 normalMtx = glm::mat3(glm::transpose(glm::inverse(modelMtx)));
    _lightingShaderProgram->setProgramUniform(_lightingShaderUniformLocations.normMat, normalMtx);

}

//*************************************************************************************
//
// Callbacks
void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods ) {
    auto engine = (Engine*) glfwGetWindowUserPointer(window);

    // pass the key and action through to the engine
    engine->handleKeyEvent(key, action);
}

void cursor_callback(GLFWwindow *window, double x, double y ) {
    auto engine = (Engine*) glfwGetWindowUserPointer(window);

    // pass the cursor position through to the engine
    engine->handleCursorPositionEvent(glm::vec2(x, y));
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods ) {
    auto engine = (Engine*) glfwGetWindowUserPointer(window);

    // pass the mouse button and action through to the engine
    engine->handleMouseButtonEvent(button, action);
}

void mouse_scroll_callback(GLFWwindow* window, double xOffset, double yOffset){
    auto engine = (Engine*) glfwGetWindowUserPointer(window);
    // pass the scroll direction to the engine
    // only Y is used due to exclusive mouse input
    engine->handleMouseScrollEvent(xOffset, yOffset);
}

void Engine::handleMouseScrollEvent(double xOffset, double yOffset) {
    // yOffset is -1 if scrolling towards user else 1
    yOffset == -1 ? _arcCam->moveBackward(_cameraSpeed.x) : _arcCam->moveForward(_cameraSpeed.x);
}


