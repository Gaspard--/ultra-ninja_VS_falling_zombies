#version 130

uniform vec2 dim;

in vec2 coord;
in vec2 pos;
out vec2 vert_coord;

void main()
{
  vert_coord = coord;
  gl_Position = vec4(pos * dim, 0.0f, 1.0f);
}
