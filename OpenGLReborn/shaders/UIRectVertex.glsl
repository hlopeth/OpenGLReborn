#version 460 core

layout (location = 0) in vec2 i_pos;

//format x, y, scaleX, scaleY
uniform vec4 u_transform;
uniform vec2 u_viewportSize;

vec2 screenToNdc(vec2 screenPos, vec2 viewportSize)
{
	vec2 ndc =  2.0 * screenPos / viewportSize - 1.0;
	ndc.y = -ndc.y;
	return ndc;
}

void main() 
{
	vec2 screen = i_pos * u_transform.zw + u_transform.xy;
	vec2 ndc = screenToNdc(screen, u_viewportSize);
	gl_Position = vec4(ndc, 0, 1.0);
}