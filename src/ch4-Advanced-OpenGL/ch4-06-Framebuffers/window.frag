#version 330 core

in vec2 tc;
out vec4 color;

uniform sampler2D tex;

const float offset = 1.0 / 300;  

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset, offset),  // top-left
        vec2(0.0f,    offset),  // top-center
        vec2(offset,  offset),  // top-right
        vec2(-offset, 0.0f),    // center-left
        vec2(0.0f,    0.0f),    // center-center
        vec2(offset,  0.0f),    // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f,    -offset), // bottom-center
        vec2(offset,  -offset)  // bottom-right    
    );

    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );
    
    vec3 sample[9];
    for(int i = 0; i < 9; i++)
    {
        sample[i] = vec3(texture(tex, tc.st + offsets[i]));
    }
    vec3 col;
    for(int i = 0; i < 9; i++)
        col += sample[i] * kernel[i];
    
    color = vec4(col, 1.0);
} 