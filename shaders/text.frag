#version 130

uniform sampler2D tex;
uniform vec3 textColor;

in vec2 vert_coord;
out vec4 color;

void main()
{
  color = vec4(textColor, texture(tex, vert_coord).r);
}
