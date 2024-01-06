#version 330 core

out vec4 Fragcolor;


in vec2 outexture;

uniform sampler2D texture01;
uniform sampler2D texture02;

void main()
{
    Fragcolor = mix(texture(texture01,outexture),texture(texture02,outexture),0.4);
}
