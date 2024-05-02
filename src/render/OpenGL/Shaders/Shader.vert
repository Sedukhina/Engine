#version 440 core

layout (location = 0) in vec3 position;

uniform mat4 CameraPerspectiveMatrix;

void main()
{
   gl_Position =  CameraPerspectiveMatrix * vec4(position, 1.0f);
   //gl_Position =  vec4(position, 1.0f);
};
