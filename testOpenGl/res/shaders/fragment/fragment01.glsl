#version 330
uniform float time;
uniform sampler2D u_texture;
in vec2 v_texCoord;
layout(location = 0) out vec4 color;
void main()
{
	vec4 texColor = texture(u_texture, v_texCoord);
	//float squared =  (gl_FragCoord.xy[0] - 320) * (gl_FragCoord.xy[0] - 320) + (gl_FragCoord.xy[1] - 240) * (gl_FragCoord.xy[1] - 240); 
	//float sqr = sqrt(squared*10) -  time/10 ;
    //vec4 colorO = vec4(sin(gl_FragCoord.xy[0]/300.0 + time/300.0),cos(gl_FragCoord.xy[1]/300.0 + time/200.0), 1.0, 1.0);
	color = texColor;// + 0.1*colorO;
};