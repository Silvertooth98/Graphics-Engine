#version 460
#define TOTAL_LIGHTS 3
#define DIRECTIONAL 1
#define POINT 2
#define SPOT 3
#define FLASHLIGHT 4

//**************************************
//		Lighting
//**************************************

struct Light
{
	int type;
	bool isActive;

	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float attenuationConst;
	float attenuationLinear;
	float attenuationQuad;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float shininess;
};

uniform Light lights[TOTAL_LIGHTS];
uniform Material material;

uniform vec3 cameraPosition;

in vec3 vertexOut;

uniform bool isLit;
uniform bool isLight;

uniform mat4 fragModel;

//**************************************
//		Lighting
//**************************************

in vec3 colorOut;
in vec2 textureOut;
in vec3 normalOut;

out vec4 pixelColor;

uniform float value;

uniform bool flag;
uniform bool textureFlag;

uniform sampler2D textureImage;

uniform float time;

//**************************************
//		Shader attempts
//**************************************

//**************************************
//		Noise Shader
//**************************************
uniform bool isNoiseShader;

float ntsf(float x,float k)
{
	x = clamp(x,-1.0,1.0);
	float r = (x-x*k)/(k - abs(x) * 2.0 * k + 1.0);
	if(r < 0.00)
	{
		r=0.0;
	}
	
	return r;
}

float random (vec2 st,float d)
{
	st = floor(st * d) / d;
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
						 43758.5453123);
}

vec2 redux(vec2 v,float d)
{
	v += 0.5 / d;
	return floor(v * d) / d;
}

//**************************************
//		Circle Noise Shader
//**************************************

uniform bool isCircleNoiseShader;

float random (vec2 st)
{
	st = st * 2.0 - 1.0;
	st *= time * 0.2;
	return pow(cos(st.x * st.y), sin(st.y / (st.x)));
}

//**************************************************************
//		Colour Change Shader
//**************************************************************

uniform bool isColorChangeShader;

//**************************************************************
//		Fire Box Shader - https://shaderfrog.com/app/editor
//**************************************************************

uniform bool isFireBoxShader;

float PI = 3.14159265359,
			arms = 8.,
			speed = 1.5,
			width = .4,
			subdivide = 5.;

			vec4 color_ = vec4(1.,.4,.1,1.);

//**************************************
//		Shader attempts
//**************************************

//**************************************
//	   Lighting Calculation Function
//**************************************

vec3 f_vertexPos()
{
	//calculate vertex position in world space
	vec3 vertexPos = vec3(fragModel * vec4(vertexOut, 1.0));
	
	return vertexPos;
}

vec3 f_normal()
{
	//calculate diffuse lighting
	//vec3 normal = vec3(0.0, 1.0, 0.0);
	vec3 normal = normalize(normalOut);

	return normal;
}

vec3 f_ambient(in Light light)
{
	//calculate ambient color
	vec3 ambientColor = light.ambient * material.ambient;

	return ambientColor;
}

vec3 f_diffuse(in Light light)
{
	vec3 lightDirection;

	if (light.type == POINT)
	{
		//calculate light direction
		lightDirection = normalize(light.position - f_vertexPos());
	}

	if (light.type == DIRECTIONAL)
	{
		lightDirection = normalize(light.position);
	}

	//calculate light intensity (always stays between 0 and 1)
	float lightIntensity = max(dot(lightDirection, f_normal()), 0.0);

	//calculate diffuse color
	vec3 diffuseColor = light.diffuse * material.diffuse * lightIntensity;

	return diffuseColor;
}

vec3 f_specular(in Light light)
{
	vec3 lightDirection;

	if (light.type == POINT)
	{
		//calculate light direction
		lightDirection = normalize(light.position - f_vertexPos());
	}

	if (light.type == DIRECTIONAL)
	{
		lightDirection = normalize(light.position);
	}

	//calculate viewing direction (relation camera is to each vertex)
	vec3 viewDirection = normalize(cameraPosition - f_vertexPos());

	//calculate the reflection vector (reflecting the light direction around the normal)
	vec3 reflection = reflect(-lightDirection, f_normal());

	//calculate specular term
	float specularTerm = pow(max(dot(viewDirection, reflection), 0.0), material.shininess);

	//calculate specular color
	vec3 specularColor = light.specular * material.specular * specularTerm;

	return specularColor;
}

float f_attenuation(in Light light)
{
	//calculate distance vector for attenuation lighting
	float lightDistance = length(light.position - f_vertexPos());

	//calculate attenuation lighting
	float attenLight = 1.0 / (light.attenuationConst + light.attenuationLinear * lightDistance + light.attenuationQuad * (lightDistance * lightDistance));

	return attenLight;
}

//**************************************
//	   Lighting Calculation Function
//**************************************

void main(void)
{
	//perform lighting calculations on every object
	if (isLit)
	{
		if (!isLight)
		{
			for (int i = 0; i < TOTAL_LIGHTS; i++)
			{
				//add up color values using ADS
				vec3 totalColor = f_ambient(lights[i]) +
								  f_diffuse(lights[i]) +
								  f_specular(lights[i]);

				//cap values at 1.0
				totalColor.r = min(totalColor.r, 1.0);
				totalColor.g = min(totalColor.g, 1.0);
				totalColor.b = min(totalColor.b, 1.0);

				//append color to final frag color
				if (lights[i].type == 1)
				{
					pixelColor += vec4(totalColor, 1.0);
				}

				if (lights[i].type == 2)
				{
					pixelColor += vec4(totalColor * f_attenuation(lights[i]), 1.0);
				}

				if (textureFlag)
				{
					pixelColor *= texture(textureImage, textureOut);
				}

				else
				{
					pixelColor *= vec4(colorOut, 1.0);
				}
			}
		}
		else
		{
			pixelColor = vec4(colorOut, 1.0);
		}
	}

	else
	{
		if (textureFlag && !isFireBoxShader)
		{
			pixelColor = texture(textureImage, textureOut);
		}

		else if (isNoiseShader)
		{
			vec2 p = ( gl_FragCoord.x / vertexOut.xy ) + 0.0000001;

			vec2 q = redux(p,10.0);
			q.x = q.x + (random(p, 1000.0) - 0.5) / 30.0;
			q.y = q.y + (random(p, 999.9) - 0.5) / 30.0;
			float e = 1.0 - ntsf(distance(p, q), -0.97);
	
			pixelColor = vec4(colorOut, 1.0) + vec4( vec3(e),1);
		}

		else if (isCircleNoiseShader)
		{
			vec2 p = colorOut.xy / vertexOut.xy + time * 0.0000000000000000000000000000000000000000000000000000001;
			pixelColor = vec4(colorOut, 1.0) * vec4(vec3(random(p)), 1.0);
		}

		else if (isColorChangeShader)
		{
			vec2 uv = colorOut.xy / vertexOut.zy;
			float t = time + (uv.y / 2.0);
			vec3 a = vec3(1.0, 0.0, (sin(t) + 1.0) / 2.0), b = vec3((sin(t * 2.0) + 1.0) / 2.0, 1.0,(sin(t * 2.5) + 1.0) / 2.0);
			vec3 color = uv.y < 0.5 ? mix(a, b, uv.x) : sqrt(mix(pow(a, vec3(2.0)), pow(b, vec3(2.0)), uv.x));
			pixelColor = vec4(color, 1.0);
		}
		else if (isFireBoxShader)
		{
			float len = length(vertexOut),
   			angle = (atan(vertexOut.x,vertexOut.y)/(2.*PI))+1.5,
    		wobble = 6.+4.*cos(time/5.),
    		white = fract((angle)*arms+sin((sqrt(len)*wobble)-time*speed));
    
			white  = 2.*sin(white/(PI/10.));
			white *= floor(fract(angle*arms+sin(time/speed-(len*1.2)*wobble))*subdivide)/subdivide;
    
			vec4 color1 = smoothstep(0.,1.,white*color_);
			vec4 bg = texture(textureImage, textureOut);
    
			pixelColor = mix(bg,color1, color1.a);
		}
		else
		{
			pixelColor = vec4(colorOut, 1.0);
		}
	}
}