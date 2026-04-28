#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TilingFactor;
layout(location = 5) in int a_EntityID;

// The Uniform Buffer Block that catches the camera matrix
layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

struct VertexOutput
{
	vec2 TexCoord;
	vec4 Color;
	float TexIndex;
	float TilingFactor;
};

layout (location = 0) out VertexOutput Output;
layout (location = 4) out flat int v_EntityID;

void main()
{
	Output.TexCoord = a_TexCoord;
	Output.Color = a_Color;
	Output.TexIndex = a_TexIndex;
	Output.TilingFactor = a_TilingFactor;
	v_EntityID = a_EntityID;

	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_EntityID;

struct VertexOutput
{
	vec2 TexCoord;
	vec4 Color;
	float TexIndex;
	float TilingFactor;
};

layout (location = 0) in VertexOutput Input;
layout (location = 4) in flat int v_EntityID;

uniform sampler2D u_Texture[32];

void main()
{
    vec4 texColor = Input.Color;

    // Sample the texture array based on the incoming index
    texColor *= texture(u_Texture[int(Input.TexIndex)], Input.TexCoord * Input.TilingFactor);

    if (texColor.a == 0.0)
        discard;

    o_Color = texColor;
	o_EntityID = v_EntityID;
}