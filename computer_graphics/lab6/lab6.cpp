#include <iostream>
#include <cmath>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Other includes
#include "Shader.h"
#include "Camera.h"
#include "multyplyes.h"
using namespace std;

// compile: g++ main.cpp -o start -lGL -lGLEW -lglfw

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();
void new_func_size_callback(GLFWwindow* window, int width, int heigh);

GLfloat* get_figure();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

double speed = 0.5;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX  =  WIDTH  / 2.0;
GLfloat lastY  =  HEIGHT / 2.0;
bool    keys[1024];
bool ret = true;

GLfloat APPROX = 0.01f;
GLfloat chill_height = 1.5f;

// Light attributes
glm::vec3 lightPos(-1.2f, 1.0f, 2.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame


GLfloat x_rotation = 0.0f, y_rotation = 0.0f, z_rotation = 0.0f;
GLfloat scale = 1.0f;

void new_func_size_callback(GLFWwindow* window, int width, int height){
    if(!height){
        height = 0;
    }
    glViewport(0, 0, width, height);
}

GLfloat* get_figure(){
    GLfloat* vertex =(GLfloat*) malloc(sizeof(GLfloat) * (1 + (unsigned)(2.0f/APPROX)) * 9 * 4 * 2);
    GLint j = 0;

    for(GLfloat i = 0.0f; i <= 2.0f*M_PI; i += M_PI*APPROX){
        vertex[j++] = 0.0f;
        vertex[j++] = -chill_height / 2.0f;
        vertex[j++] = 0.0f;

        vertex[j++] = 0.0f;
        vertex[j++] = -1.0f;
        vertex[j++] = 0.0f;


        vertex[j++] = 0.6f * cos(i);
        vertex[j++] = -chill_height / 2.0f;
        vertex[j++] = 0.6f * sin(i);

        vertex[j++] = 0.0f;
        vertex[j++] = -1.0f;
        vertex[j++] = 0.0f;


        vertex[j++] = 0.6f * cos(i + M_PI*APPROX);
        vertex[j++] = -chill_height / 2.0f;
        vertex[j++] = 0.6f * sin(i + M_PI*APPROX);

        vertex[j++] = 0.0f;
        vertex[j++] = -1.0f;
        vertex[j++] = 0.0f;
    }

    for(GLfloat i = 0.0f; i <= 2*M_PI; i += M_PI*APPROX){
        vertex[j++] = 0.0f;
        vertex[j++] = chill_height / 2;
        vertex[j++] = 0.0f;

        vertex[j++] = -1.0f;
        vertex[j++] = 1.0f;
        vertex[j++] = 0.0f;


        vertex[j++] = 0.6f * cos(i);
        vertex[j++] = chill_height / 2 + 0.6* cos(i);
        vertex[j++] = 0.6f * sin(i);

        vertex[j++] = -1.0f;
        vertex[j++] = 1.0f;
        vertex[j++] = 0.0f;


        vertex[j++] = 0.6f * cos(i + M_PI*APPROX);
        vertex[j++] = chill_height / 2 + 0.6 * cos(i + M_PI*APPROX);
        vertex[j++] = 0.6f * sin(i + M_PI*APPROX);

        vertex[j++] = -1.0f;
        vertex[j++] = 1.0f;
        vertex[j++] = 0.0f;
    }


    for(GLfloat i = 0.0f; i <= 2*M_PI; i += M_PI*APPROX){
        GLfloat ax = cos(i) - cos(i + M_PI*APPROX);
        GLfloat ay = 0.0f;
        GLfloat az = sin(i) - sin(i + M_PI * APPROX);

        GLfloat bx = 0.0f;
        GLfloat by = 1.0f;
        GLfloat bz = 0.0f;

        GLfloat nx = ay * bz - az * by;
        GLfloat ny = 0.0f;
        GLfloat nz = ax*by - ay*bx;


        vertex[j++] = 0.6f * cos(i);
        vertex[j++] = -chill_height / 2;
        vertex[j++] = 0.6f * sin(i);

        vertex[j++] = nx;
        vertex[j++] = ny;
        vertex[j++] = nz;


        vertex[j++] = 0.6f * cos(i + M_PI*APPROX);
        vertex[j++] = -chill_height / 2;
        vertex[j++] = 0.6f * sin(i + M_PI*APPROX);

        vertex[j++] = nx;
        vertex[j++] = ny;
        vertex[j++] = nz;


        vertex[j++] = 0.6f * cos(i);
        vertex[j++] = chill_height / 2 + 0.6*cos(i);
        vertex[j++] = 0.6f * sin(i);

        vertex[j++] = nx;
        vertex[j++] = ny;
        vertex[j++] = nz;
    }



    for(GLfloat i = 0.0f; i <= 2*M_PI; i += M_PI*APPROX){
        GLfloat ax = cos(i) - cos(i + M_PI * APPROX);
        GLfloat ay = 0.0f;
        GLfloat az = sin(i) - sin(i + M_PI*APPROX);

        GLfloat bx = 0.0f;
        GLfloat by = 1.0f;
        GLfloat bz = 0.0f;

        GLfloat nx = ay * bz - az * by;
        GLfloat ny = 0.0f;
        GLfloat nz = ax*by - ay*bx;

        vertex[j++] = 0.6f * cos(i);
        vertex[j++] = chill_height / 2 + 0.6*cos(i);
        vertex[j++] = 0.6f * sin(i);

        vertex[j++] = nx;
        vertex[j++] = ny;
        vertex[j++] = nz;


        vertex[j++] = 0.6f * cos(i + M_PI*APPROX);
        vertex[j++] = chill_height / 2 + 0.6 * cos(i + M_PI*APPROX);
        vertex[j++] = 0.6f * sin(i + M_PI*APPROX);

        vertex[j++] = nx;
        vertex[j++] = ny;
        vertex[j++] = nz;


        vertex[j++] = 0.6f * cos(i + M_PI*APPROX);
        vertex[j++] = -chill_height / 2;
        vertex[j++] = 0.6f * sin(i + M_PI*APPROX);

        vertex[j++] = nx;
        vertex[j++] = ny;
        vertex[j++] = nz;
    }

    return vertex;
}

// The MAIN function, from here we start the application and run the game loop
int main()
{
    GLfloat AmbStren, DifStren, SpecStren;
    cout << "Enter params of light:" << endl;
    cout << "\t>> Strenght of ambient light [0.0, 1.0] (default 0.5): ";
    cin >> AmbStren;
    cout << "\t>> Strenght of diffusion light [0.0, 1.0] (default 0.5): ";
    cin >> DifStren;
    cout << "\t>> Strenght of specular light [0.0, 1.0] (default 0.5): ";
    cin >> SpecStren;
    cout << "\t4)Enter approximation parametr less then 1.0 (default ~0.002): ";
    cin >> APPROX;
    cout << "\n Success" << endl;
    cout << "Start" << endl;
    // Init GLFW
    glm::vec3 strenght(AmbStren, DifStren, SpecStren);
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lab6 Var13", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    glfwSetFramebufferSizeCallback(window, new_func_size_callback);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();

    // Define the viewport dimensions
    glViewport(0, 0, WIDTH, HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Build and compile our shader program
    Shader lightingShader("shaders/lighting.vs", "shaders/lighting.frag");
    Shader lampShader("shaders/lamp.vs", "shaders/lamp.frag");

    GLfloat* vertices = get_figure();

    // First, set the container's VAO (and VBO)
    GLuint VBO, containerVAO;
    glGenVertexArrays(1, &containerVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (1 + (unsigned)(2/APPROX)) * 9 * 4 * 2, vertices, GL_STATIC_DRAW);

    glBindVertexArray(containerVAO);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);

    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    // Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
    GLuint lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Set the vertex attributes (only position data for the lamp))
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the normal vectors
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glm::mat4 chillModel = glm::mat4(1.0f);

    double time = 0;

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        //speed
        time += 0.01;
        if (time > 2*M_PI) {
            time -=  2*M_PI;
        }
        speed = sin(time);
        // Calculate deltatime of current frame
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        do_movement();

        // Clear the colorbuffer
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use cooresponding shader when setting uniforms/drawing objects
        lightingShader.Use();
        GLint objectColorLoc = glGetUniformLocation(lightingShader.Program, "objectColor");
        GLint lightColorLoc  = glGetUniformLocation(lightingShader.Program, "lightColor");
        GLint lightPosLoc    = glGetUniformLocation(lightingShader.Program, "lightPos");
        GLint viewPosLoc     = glGetUniformLocation(lightingShader.Program, "viewPos");
        GLint strenPosLoc = glGetUniformLocation(lightingShader.Program, "strenght");
        glUniform3f(objectColorLoc, 0.5f, 0.5f, 0.8f);
        glUniform3f(lightColorLoc,  1.0f, 1.0f, 1.0f);
        glUniform3f(lightPosLoc,    lightPos.x, lightPos.y, lightPos.z);
        glUniform3f(viewPosLoc,     camera.Position.x, camera.Position.y, camera.Position.z);
        glUniform3f(strenPosLoc,     strenght.x, strenght.y, strenght.z);

        // Create camera transformations
        glm::mat4 view;
        view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
        // Get the uniform locations
        GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
        GLint viewLoc  = glGetUniformLocation(lightingShader.Program,  "view");
        GLint projLoc  = glGetUniformLocation(lightingShader.Program,  "projection");
        // Pass the matrices to the shader
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Draw the container (using container's vertex attributes)
        glBindVertexArray(containerVAO);
        glm::mat4 model = glm::mat4(1.0f);

        if(ret){
            chillModel = glm::mat4(1.0f);
            ret = false;
        }else{
            glm::vec4 quaternion;
            glm::mat4 rotation, scalem = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));
            xyz_rotation_to_quaternion(quaternion, x_rotation, y_rotation, z_rotation);
            quaternion_to_matrix(rotation, quaternion);
            chillModel = rotation * scalem * chillModel;
        }


        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(chillModel));
        glDrawArrays(GL_TRIANGLES, 0, (1 + (unsigned)(2/APPROX)) * 3 * 4);
        glBindVertexArray(0);

        // Also draw the lamp object, again binding the appropriate shader
        lampShader.Use();
        // Get location objects for the matrices on the lamp shader (these could be different on a different shader)
        modelLoc = glGetUniformLocation(lampShader.Program, "model");
        viewLoc  = glGetUniformLocation(lampShader.Program, "view");
        projLoc  = glGetUniformLocation(lampShader.Program, "projection");
        // Set matrices
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        model = glm::mat4(1.0);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.05f)); // Make it a smaller cube
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        // Draw the light object (using light's vertex attributes)
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, (1 + (unsigned)(2/APPROX)) * 3 * 4);
        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    free(vertices);
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void do_movement()
{
    // Camera controls
    if (keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);

    if(keys[GLFW_KEY_UP]){
        scale = 1.04f;
    }else if(keys[GLFW_KEY_DOWN]){
        scale = 0.96f;
    }else{
        scale = 1.0f;
    }
    if(keys[GLFW_KEY_Y]){
        x_rotation = glm::radians(5.0f);
    }else if(keys[GLFW_KEY_T]){
        x_rotation = -glm::radians(5.0f);
    }else{
        x_rotation = 0.0f;
    }
    if(keys[GLFW_KEY_G]){
        y_rotation = -glm::radians(5.0f);
    }else if(keys[GLFW_KEY_H]){
        y_rotation = glm::radians(5.0f);
    }else{
        y_rotation = 0.0f;
    }
    if(keys[GLFW_KEY_B]){
        z_rotation = -glm::radians(5.0f) * speed;
    }else if(keys[GLFW_KEY_N]){
        z_rotation = glm::radians(5.0f) * speed;
    }else{
        z_rotation = 0.0f;
    }
    if(keys[GLFW_KEY_R]){
        ret = true;
    }
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}