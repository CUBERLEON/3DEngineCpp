#version 400

in vec2 f_textureCoord;
in vec3 f_normalInterpolated; vec3 f_normal;
in vec3 f_worldPosition;

//additional variables
uniform vec3 f_eyePosition;

//material
uniform sampler2D m_diffuse;
uniform float m_specularIntensity;
uniform float m_specularPower;

include "lighting.glh"

//lights
uniform DirectionalLight l_directional;

void main() {
	f_normal = normalize(f_normalInterpolated);

	gl_FragColor = texture(m_diffuse, f_textureCoord) * calcDirectionalLight(l_directional, f_normal, f_worldPosition);
}