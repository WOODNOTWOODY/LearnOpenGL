#version 330 core
in vec3 iPosition;
uniform mat4 iModel;
uniform mat4 iCamera;

void main()
{
	gl_Position = iCamera * iModel * vec4(iPosition, 1.0);
}
