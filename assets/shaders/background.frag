uniform sampler2D texture;
uniform vec2 textureSize;
uniform vec2 cameraPos;
uniform vec2 resolution;

void main()
{
	vec2 offset = (cameraPos/textureSize);
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy + offset);
	gl_FragColor = gl_Color * pixel;
}

// for future - by multiplying gl_Texcoord you are affecting whole screen not just that small square, so it increases in size when you do gl_Texcoord / 0.8 etc.