#version 330 core
layout (location = 0) in vec2 aPos;



//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;

void main()
{
	gl_Position = vec4(2*aPos.x-1,2*aPos.y-1,0.0f, 1.0);
;
}