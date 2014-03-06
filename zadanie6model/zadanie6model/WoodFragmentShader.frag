#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

vec3 mod289(vec3 x) {
	return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec2 mod289(vec2 x) {
	return x - floor(x * (1.0 / 289.0)) * 289.0;
}

vec3 permute(vec3 x) {
	return mod289(((x*34.0)+1.0)*x);
}

float snoise(vec2 v) {
	const vec4 C = vec4(0.211324865405187, 	// (3.0-sqrt(3.0))/6.0
					0.366025403784439, 		// 0.5*(sqrt(3.0)-1.0)
					-0.577350269189626, 	// -1.0 + 2.0 * C.x
					0.024390243902439); 	// 1.0 / 41.0
	// First corner
	vec2 i = floor(v + dot(v, C.yy) );
	vec2 x0 = v - i + dot(i, C.xx);

	// Other corners
	vec2 i1;
	//i1.x = step( x0.y, x0.x ); // x0.x > x0.y ? 1.0 : 0.0
	//i1.y = 1.0 - i1.x;
	i1 = (x0.x > x0.y) ? vec2(1.0, 0.0) : vec2(0.0, 1.0);
	// x0 = x0 - 0.0 + 0.0 * C.xx ;
	// x1 = x0 - i1 + 1.0 * C.xx ;
	// x2 = x0 - 1.0 + 2.0 * C.xx ;
	vec4 x12 = x0.xyxy + C.xxzz;
	x12.xy -= i1;

	// Permutations
	i = mod289(i); // Avoid truncation effects in permutation
	vec3 p = permute( permute( i.y + vec3(0.0, i1.y, 1.0 ))
			+ i.x + vec3(0.0, i1.x, 1.0 ));

	vec3 m = max(0.5 - vec3(dot(x0,x0), dot(x12.xy,x12.xy), dot(x12.zw,x12.zw)), 0.0);
	m = m*m ;
	m = m*m ;

	// Gradients: 41 points uniformly over a line, mapped onto a diamond.
	// The ring size 17*17 = 289 is close to a multiple of 41 (41*7 = 287)

	vec3 x = 2.0 * fract(p * C.www) - 1.0;
	vec3 h = abs(x) - 0.5;
	vec3 ox = floor(x + 0.5);
	vec3 a0 = x - ox;

	// Normalise gradients implicitly by scaling m
	// Approximation of: m *= inversesqrt( a0*a0 + h*h );
	m *= 1.79284291400159 - 0.85373472095314 * ( a0*a0 + h*h );

	// Compute final noise value at P
	vec3 g;
	g.x = a0.x * x0.x + h.x * x0.y;
	g.yz = a0.yz * x12.xz + h.yz * x12.yw;
	return 130.0 * dot(m, g);
}

float turbulence(float x, float y, float size) {
    float value = 0.0, initialSize = size;
    
    while(size >= 1) {
        value += snoise(vec2(x / size, y / size)) * size;
        size /= 2.0;
    }
    
    return(128.0 * value / initialSize);
}

void main(){
    float x = UV.x;
    float y = UV.y;

//    float xyPeriod = 60.0; //number of rings
//    float turbPower = 0.1; //makes twists
//    float turbSize = 32.0; //initial size of the turbulence
//    float xValue = (x - noiseHeight / 2) / float(noiseHeight);
//    float yValue = (y - / 2) / float(noiseWidth);
//    float distValue = sqrt(xValue * xValue + yValue * yValue) + turbPower
//                    * turbulence(x, y, turbSize) / 256.0;
//    float sineValue = 128.0 * abs(sin(2 * xyPeriod * distValue * 3.14159));
//    color.r = (80 + sineValue) / 255;
//    color.g = (30 + sineValue) / 255;
//    color.b = 30.0 / 255;

    float xPeriod = 0.05; //defines repetition of marble lines in x direction
    float yPeriod = 10.0; //defines repetition of marble lines in y direction
    //turbPower = 0 ==> it becomes a normal sine pattern
    float turbPower = 10.0; //makes twists
    float turbSize = 32.0; //initial size of the turbulence

    float xyValue = x * xPeriod + y * yPeriod + turbPower * turbulence(x, y, turbSize) / 256.0;
    float sineValue = 128.0 * abs(sin(xyValue * 3.14159));
    color.r = (80 + sineValue) / 255;
    color.g = (30 + sineValue) / 255;
    color.b = 30.0 / 255;
}
