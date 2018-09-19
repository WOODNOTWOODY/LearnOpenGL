#version 330 core
in vec3 iPosition;
in vec2 iTexCoord;

out vec2 fragTexCoord;

uniform mat4 iModel;
uniform mat4 iCamera;

void main()
{
	fragTexCoord = iTexCoord;
	gl_Position = iCamera * iModel * vec4(iPosition, 1.0);
}
