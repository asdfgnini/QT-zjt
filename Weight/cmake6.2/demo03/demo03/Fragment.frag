#version 330 core
out vec4 FragColor;

in vec3 ourColor;

in vec2 Textcood;
uniform sampler2D ourTexture;
uniform sampler2D ourTexture1;

void main()
{
    // FragColor = vec4(1.0f,0.5f,0.2f,1.0f);
    // FragColor = vec4(ourColor,1.0f) * mix(texture(ourTexture,Textcood),texture(ourTexture1,Textcood),0.8);
    FragColor = mix(texture(ourTexture,Textcood),texture(ourTexture1,Textcood),0.3);
}
