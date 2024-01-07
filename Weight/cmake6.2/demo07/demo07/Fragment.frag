#version 330 core

out vec4 FragColor;


in vec2 outexCoord;

uniform sampler2D texture01;


void main()
{
    FragColor = texture(texture01,outexCoord);

}
