uniform sampler2D texture;
uniform vec2 textureSize;
uniform vec2 cameraPos;

void main()
{
	vec2 offset = cameraPos/textureSize;
	offset.y = -offset.y;
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy + offset);

	gl_FragColor = gl_Color * pixel;
}