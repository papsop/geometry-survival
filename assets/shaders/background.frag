uniform sampler2D texture;
uniform vec2 cameraPos;

void main()
{
	vec4 pixel = texture2D(texture, gl_texCoord[0].xy);

	gl_FragColor = gl_Color * pixel;
}