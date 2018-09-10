#version 330 core
in vec3 iPosition;
in vec3 iNormal;
in vec2 iTexCoord;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoord;

uniform mat4 iCamera;
uniform mat4 iModel;

void main()
{
	fragPos = vec3(iModel * vec4(iPosition, 1.0));
	fragNormal = mat3(transpose(inverse(iModel))) * iNormal;
	fragTexCoord = iTexCoord;
	gl_Position = iCamera * vec4(fragPos, 1.0);
}
