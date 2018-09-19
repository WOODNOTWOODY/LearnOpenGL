#version 330 core
out vec4 FragColor;

in vec2 fragTexCoord;

uniform sampler2D iTex;

void main()
{
	FragColor = texture(iTex, fragTexCoord);
	//FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
}
