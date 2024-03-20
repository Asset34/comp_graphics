#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;

void main()
{   
    mat4 matr = mat4(1.0);
    matr[3][3] = 10.0;

    gl_Position = matr * model * vec4(aPos, 1.0);
};