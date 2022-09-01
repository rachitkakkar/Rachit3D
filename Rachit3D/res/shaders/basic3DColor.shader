#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
layout(location = 3) in vec2 texCoord;

out vec3 vPosition;
out vec3 vNormal;
out vec3 vColor;
out vec2 vTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
	vPosition = position;
	vNormal = normal;
	vColor = color;
	vTexCoord = texCoord;

	gl_Position = uProjection * uView * uModel * vec4(position, 1.0f);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 vPosition;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexCoord;

void main()
{
	color = vec4(vColor, 1.0f);
}