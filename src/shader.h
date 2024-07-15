#ifndef SHADER_H
#define SHADER_H

#include <glew.h>
#include <stdlib.h>
#include <stdio.h>

extern const char* vertexShaderSource;
extern const char* fragmentShaderSource;

unsigned int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

#endif // SHADER_H
