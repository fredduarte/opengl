#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <GL/glew.h>

#include "shader.h"

using namespace std;

GLuint loadShaders(const char* vertexShaderFilePath, const char* fragmentShaderFilePath) {
    // Create the shaders
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    string vertexShaderCode;
    ifstream vertexShaderFilestream(vertexShaderFilePath, ios::in);

    if (vertexShaderFilestream.is_open()) {
        string line = "";

        while (getline(vertexShaderFilestream, line)) {
            vertexShaderCode += "\n" + line;
        }

        vertexShaderFilestream.close();
    } else {
        cout << "Impossible to open " << vertexShaderFilePath
             << ". File could NOT be read/found." << endl;

        return NULL;
    }

    // Read the Fragment Shader code from the file
    string fragmentShaderCode;
    ifstream fragmentShaderFilestream(fragmentShaderFilePath, ios::in);

    if (fragmentShaderFilestream.is_open()) {
        string line = "";

        while (getline(fragmentShaderFilestream, line)) {
            fragmentShaderCode += "\n" + line;
        }

        fragmentShaderFilestream.close();
    } else {
        cout << "Impossible to open " << fragmentShaderFilePath
             << ". File could NOT be found." << endl;

        return NULL;
    }

    GLint compileResult = GL_FALSE;
    int infoLogLength;

    // Compile Vertex Shader
    cout << "Compiling shader : " << vertexShaderFilePath << endl;

    char const* vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderId, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderId);

    // Check Vertex Shader
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &compileResult);
    glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0) {
        vector<char> vertexShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(vertexShaderId, infoLogLength, NULL, &vertexShaderErrorMessage[0]);

        cout << vertexShaderErrorMessage[0] << endl;
    }

    // Compile Fragment Shader
    cout << "Compiling shader : " << fragmentShaderFilePath << endl;

    char const* fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderId, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShaderId);

    // Check Fragment Shader
    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &compileResult);
    glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0) {
        vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(fragmentShaderId, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);

        cout << fragmentShaderErrorMessage[0] << endl;
    }

    // Link the program
    cout << "Linking program" << endl;

    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    // Check the program
    glGetProgramiv(programId, GL_LINK_STATUS, &compileResult);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);

    if (infoLogLength > 0) {
        vector<char> programErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(programId, infoLogLength, NULL, &programErrorMessage[0]);

        cout << programErrorMessage[0] << endl;
    }

    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}
