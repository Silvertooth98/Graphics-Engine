#version 460

in vec3 vertexIn;
in vec3 colorIn;
in vec2 textureIn;
in vec3 normalIn;

out vec3 colorOut;
out vec3 vertexOut;
out vec2 textureOut;
out vec3 normalOut;

in vec3 lightColorIn;
out vec3 lightColorOut;

uniform mat3 normal;
uniform mat4 vertModel;
uniform mat4 view;
uniform mat4 projection;

void main(void)
{

	//pass through the color
	colorOut = colorIn;

	vertexOut = vertexIn;

	textureOut = textureIn;

	normalOut = normal * normalIn;

	gl_Position = projection * view * vertModel * vec4(vertexIn, 1.0);

}