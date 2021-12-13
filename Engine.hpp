#ifndef LAB05_LAB05_ENGINE_HPP
#define LAB05_LAB05_ENGINE_HPP

#include <CSCI441/FreeCam.hpp>
#include <CSCI441/OpenGLEngine.hpp>
#include <CSCI441/ShaderProgram.hpp>
#include <CSCI441/FreeCam.hpp>
#include "Chunk.hpp"
#include "Steve.hpp"
#include "ArcCam.hpp"
#include "FPCam.hpp"

#include <vector>
#include <ctime>

class Engine : public CSCI441::OpenGLEngine {
public:
    Engine(int OPENGL_MAJOR_VERSION, int OPENGL_MINOR_VERSION,
                int WINDOW_WIDTH, int WINDOW_HEIGHT,
                const char* WINDOW_TITLE);
    ~Engine();

    void run() final;

    /// \desc handle any key events inside the engine
    /// \param key key as represented by GLFW_KEY_ macros
    /// \param action key event action as represented by GLFW_ macros
    void handleKeyEvent(GLint key, GLint action);

    /// \desc handle any mouse button events inside the engine
    /// \param button mouse button as represented by GLFW_MOUSE_BUTTON_ macros
    /// \param action mouse event as represented by GLFW_ macros
    void handleMouseButtonEvent(GLint button, GLint action);

    /// \desc handle any cursor movement events inside the engine
    /// \param currMousePosition the current cursor position
    void handleCursorPositionEvent(glm::vec2 currMousePosition);

    /// \desc value off-screen to represent mouse has not begun interacting with window yet
    static constexpr GLfloat MOUSE_UNINITIALIZED = -9999.0f;
    
    /// \desc what hero we have selected
    int selectedHero = 0;

    bool isJumping = false;
    float jumpHeight = 0.0;

    void handleMouseScrollEvent(double xOffset, double yOffset);
private:
    /// \desc set up functions
    void _setupGLFW() final;
    void _setupOpenGL() final;
    void _setupShaders() final;
    void _setupBuffers() final;
    void _setupScene() final;
    /// \desc cleanup functions
    void _cleanupBuffers() final;
    void _cleanupShaders() final;

    struct Vertex{GLfloat x,y,z,xN,yN,zN;};//vertex to hold data for _gridPoints 
    std::vector<glm::vec3> _gridPoints;//points of the grid lines
    int _numGridPoints;
    glm::vec3 _gridColor = glm::vec3(1.0f, 1.0f, 1.0f);

    /// \desc draws everything to the scene from a particular point of view
    /// \param viewMtx the current view matrix for our camera
    /// \param projMtx the current projection matrix for our camera
    void _renderScene(glm::mat4 viewMtx, glm::mat4 projMtx);
    /// \desc handles moving as determined by keyboard input
    void _updateScene();

    /// \desc tracks the number of different keys that can be present as determined by GLFW
    static constexpr GLuint NUM_KEYS = GLFW_KEY_LAST;
    /// \desc boolean array tracking each key state.  if true, then the key is in a pressed or held
    /// down state.  if false, then the key is in a released state and not being interacted with
    GLboolean _keys[NUM_KEYS];
    GLboolean _repeat[NUM_KEYS];

    GLboolean povDisplayed = false;

    /// \desc skybox texture stuff from previous assignment
    // ***********************************************************************************
    /// \desc shader program that performs lighting
    CSCI441::ShaderProgram* _textureShaderProgram = nullptr;   // the wrapper for our shader program
    /// \desc stores the locations of all of our shader uniforms
    struct TextureShaderUniformLocations {
        /// \desc precomputed MVP matrix location
        GLint mvpMatrix;
        // TODO #11
        GLint ourTexture;

    } _textureShaderUniformLocations;
    /// \desc stores the locations of all of our shader attributes
    struct TextureShaderAttributeLocations {
        /// \desc vertex position location
        GLint vPos;
        /// \desc vertex normal location
        /// \note not used in this lab
        GLint vNormal;
        // TODO #10
        GLint aTexCoord;


    } _textureShaderAttributeLocations;


    /// \desc total number of textures in our scene
    static constexpr GLuint NUM_TEXTURES = 2;
    /// \desc used to index through our texture array to give named access
    enum TEXTURE_ID {
        /// \desc metal texture
        METAL = 0,
        /// \desc Mines logo texture
        MINES = 1
    };
    /// \desc texture handles for our textures
    GLuint _texHandles[NUM_TEXTURES];
    static GLuint _loadAndRegisterTexture(const char* FILENAME);



    // *************************************************************************************



    /// \desc last location of the mouse in window coordinates
    glm::vec2 _mousePosition;
    /// \desc current state of the left mouse button
    GLint _leftMouseButtonState;

    /// \desc ArcBall camera attached to a character
    ArcCam* _arcCam;
    /// \desc Free Camera
    CSCI441::FreeCam* _freeCam;

    CSCI441::Camera* _currentCamera = nullptr;

    /// \desc First Person camera attached to a character
    FPCam* _fpCam;
    /// \desc pair of values to store the speed the camera can move/rotate.
    /// \brief x = forward/backward delta, y = rotational delta
    glm::vec2 _cameraSpeed;
    /// \desc to show which camera they're using, default is 1 (arcCam)
    int camera = 1;

    /// \desc steve model
    Steve* _steve;
    /// \desc chunk
    Chunk* _chunk;

    std::vector<Chunk*> _chunks;

    /// \desc the size of the world (controls the ground size and locations of buildings)
    static constexpr GLfloat WORLD_SIZE = 55.0f;
    /// \desc VAO for our ground
    GLuint _groundVAO;
    
    /// \desc VAO for ViewPort
    
    /// \desc the number of points that make up our ground object
    GLsizei _numGroundPoints;

    /// \desc creates the ground VAO
    void _createGroundBuffers();
    
    /// \desc smart container to store information specific to each building we wish to draw
    struct BuildingData {
        /// \desc transformations to position and size the building
        glm::mat4 modelMatrix;
        /// \desc color to draw the building
        glm::vec3 color;
    };
    /// \desc information list of all the buildings to draw
    std::vector<BuildingData> _buildings;
    
    struct TreeData {
        /// \desc transformations to position and size the building
        glm::mat4 topModMatrix;
        glm::mat4 trunkModMatrix;
	glm::vec3 green = glm::vec3(0.0,0.8,0.0);
	glm::vec3 brown = glm::vec3(0.325,0.192,0.094);
    };
    std::vector<TreeData> _trees;

    /// \desc generates building information to make up our scene
    void _generateEnvironment();

    /// \desc shader program that performs lighting
    CSCI441::ShaderProgram* _lightingShaderProgram = nullptr;   // the wrapper for our shader program
    /// \desc stores the locations of all of our shader uniforms
    struct LightingShaderUniformLocations {
        /// \desc precomputed MVP matrix location
        GLint mvpMatrix;
        GLint model;
        /// \desc material diffuse color location
        GLint materialColor;
        /// \desc normal matrix
    	GLint normMat;
        /// \desc direction for the direction light
        GLint lDir;
        /// \desc color of the direction light
        GLint lCol;
	/// \desc poisition we are view from
        GLint viewPos;

        GLint dirBool;
    } _lightingShaderUniformLocations;
    struct pointLight{
	/// \desc position of the point light
	GLint col;
	GLint pos;
    }_pointLight;
    struct spotLight{
        /// \desc position of the point light
        GLint col;
        GLint pos;
        GLint width;
        GLint dir;
    }_spotlight;
    /// \desc stores the locations of all of our shader attributes
    struct LightingShaderAttributeLocations {
        /// \desc vertex position location
        GLint vPos;
        /// \desc vertex normal
        GLint vNorm;
    } _lightingShaderAttributeLocations;

    struct BlockShaderUniformLocations {
        GLint projection;
        GLint view;
        GLint textureMap;
    }_blockShaderUniformLocations;

    struct BlockShaderAttributeLocations{
        GLint vPos;
        GLint vertexNormal;
        GLint texCoord;
        GLint instanceMatrix;
    }_blockShaderAttributeLocations;

    bool _rightPressed = false;

    CSCI441::ShaderProgram* _blockShaderProgram = nullptr;
    TextureManager* _textureManager = nullptr;
    void _setupBlockShader();

    GLfloat currentJumpTravel = 0.0f;
    GLfloat maxJumpHeight = 2.0f;
    bool jumpRising = false;
    bool jumpFalling = false;
    bool characterIsJumping = false;
    bool characterIsRunning = false;
    GLfloat characterSpeed = 3.0f;

    const GLfloat SPRINT_SPEED = 10.0f;
    const GLfloat WALK_SPEED = 3.0f;

    GLfloat nearestYBelowCharacter = 9.0f;

    /// \desc precomputes the matrix uniforms CPU-side and then sends them
    /// to the GPU to be used in the shader for each vertex.  It is more efficient
    /// to calculate these once and then use the resultant product in the shader.
    /// \param modelMtx model transformation matrix
    /// \param viewMtx camera view matrix
    /// \param projMtx camera projection matrix
    void _computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const;

    GLuint loadCubeMap(std::vector<std::string> faces);

    void _setupTextures();

    void _cleanupTextures();
};
/// \desc functions for user interactions
void keyboard_callback(GLFWwindow *window, int key, int scancode, int action, int mods );
void cursor_callback(GLFWwindow *window, double x, double y );
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods );
void mouse_scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
#endif // LAB05_LAB05_ENGINE_HPP
