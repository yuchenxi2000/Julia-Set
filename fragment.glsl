#version 330 core

in vec2 xy;

out vec4 color;

//uniform int max_iter;
uniform vec2 c;
//uniform float scale;
uniform float scale;
uniform vec2 center;

void main(){
    int iter = 0;
    float x = scale * xy.x + center.x;
    float y = scale * xy.y + center.y;
//    float limit = 4.0f * scale * scale;
    float cx = c.x;
    float cy = c.y;
    while (iter < 96 && x * x + y * y < 4.0f) {
        float x0 = x * x - y * y + cx;
        float y0 = 2.0f * x * y + cy;
        x = x0;
        y = y0;
        iter++;
    }
    float rate = float(iter) / float(96);
    color = vec4(0.0f, rate, 1.0f - rate, 1.0f);
}
