#type vertex
#version 330 core

layout(location = 0) in vec3 a_pos;

uniform mat4 u_view_projection;

void main()
{
        gl_Position = u_view_projection * vec4(a_pos, 1.0);
}

#type fragment
#version 330 core

out vec4 color;

uniform vec4 u_color;

void main()
{
        color = u_color;
}

