#version 330 core
in vec2 UV;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    gl_FragColor = mix(texture(texture1, UV), texture(texture2, UV), 0.2f);
}
