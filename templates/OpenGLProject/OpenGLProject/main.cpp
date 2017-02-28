// Include standard headers
#include <iostream>
#include <cstdlib>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>

using namespace std;

void errorCallback(int error, const char* description) {
    cout << "Error: " << description << endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS)) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main(int argc, char** argv) {
    glfwSetErrorCallback(errorCallback);

    // Initialise GLFW
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = NULL;

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(1024, 768, "OpenGL Window", NULL, NULL);

    if (window == NULL) {
        glfwTerminate();

        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, keyCallback);

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        glfwTerminate();

        exit(EXIT_FAILURE);
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Main Loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen.
        glClear(GL_COLOR_BUFFER_BIT);

        // DRAW HERE

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    exit(EXIT_SUCCESS);
}
