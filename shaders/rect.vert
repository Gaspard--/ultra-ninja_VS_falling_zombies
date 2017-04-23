#version 130

uniform vec2 dim;

in vec2 pos;

void main()
{
  gl_Position = vec4(pos * dim, 0.0f, 1.0f);
}
