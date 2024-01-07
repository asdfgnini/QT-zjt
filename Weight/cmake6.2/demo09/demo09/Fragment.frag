#version 330 core

// out vec4 FragColor;

in vec2 Textcood;

uniform sampler2D textureY;
uniform sampler2D textureU;
uniform sampler2D textureV;


void main()
{
    // FragColor = vec4(1.0f,0.5f,0.2f,1.0f);
    vec3 YUV;
    vec3 RGB;

    YUV.x = texture2D(textureY,Textcood.st).r;
    YUV.y = texture2D(textureY,Textcood.st).r - 0.5;
    YUV.z = texture2D(textureY,Textcood.st).r - 0.5;
    RGB = mat3( 1, 1, 1, 0, -0.39465, 2.03211, 1.13983, -0.58060,  0) * YUV;
    gl_FragColor = vec4(RGB, 1);
}
