#version 330
#define MAX_INDEX 8U

vec2 gradients[8] = vec2[]( vec2( 1.0, 0.0),
                            vec2( 1.0, 1.0),
                            vec2( 0.0, 1.0),
                            vec2( 0.0, 1.0),
                            vec2( -1.0, 1.0),
                            vec2( -1.0, 0.0),
                            vec2( -1.0, -1.0),
                            vec2( 0, -1.0)
                            );

#define FNV_PRIME_32 16777619U
#define FNV_OFFSET_32 2166136261U
uint FNV32(int s, int t)
{
    uint hash = uint(FNV_OFFSET_32);
    //hash = hash ^ uint( (s % t) + (t % s) + t*s); // xor next byte into the bottom of the hash
    hash = hash ^ uint( t + s ); // xor next byte into the bottom of the hash
    hash = hash * FNV_PRIME_32; // Multiply by prime number found to work well
    
    return (hash % MAX_INDEX);
}

float interpolate(float t) {
  // return t*t*(3.0-2.0*t); // Old fade, yields discontinuous second derivative
  return t*t*t*(t*(t*6.0-15.0)+10.0); // Improved fade, yields C2-continuous noise
}

float noise2(vec2 p, float amplitude, int octave) {
    int i = int(p.x/octave);
    int j = int(p.y/octave);

    vec2 gradient00 = gradients[FNV32(i, j)];
    vec2 gradient10 = gradients[FNV32(i+1, j)];
    vec2 gradient11 = gradients[FNV32(i+1, j+1)];
    vec2 gradient01 = gradients[FNV32(i, j+1)];
    // vec2 p = vec2(x - float(i), y-float(j));
    
    float noise00 = dot(gradient00, p);
    float noise01 = dot(gradient01, p);
    float noise10 = dot(gradient10, p);
    float noise11 = dot(gradient11, p);

    float fx = interpolate(p.x);
    float fy = interpolate(p.y);

    float noisex0 = noise00*fx + noise10*(1.0 - fx);
    float noisex1 = noise01*fx + noise11*(1.0 - fx);
    float value = noisex0*(1.0 - fy) + noisex1*fy;

    return value*amplitude;
}

uniform mat4 qt_ModelViewProjectionMatrix;
uniform mat4 qt_ModelViewMatrix;
in vec4 qt_Vertex;
void main(void)
{
	float x = qt_Vertex[0];
	float y = qt_Vertex[1];
	float z = qt_Vertex[2];

    float value = 0.0;
    float amplitude = 1.0;
    int numOctaves = 1;
    for(int octave=1; octave<numOctaves; octave++) {
        value += noise2(qt_Vertex.xz, amplitude, octave);
        amplitude /= 2.0;
    }
    

	// y = exp(-(x*x + z*z));
	// y = noise(qt_Vertex.xz, 1.0, 1.0);
    y = value;
	gl_Position = qt_ModelViewProjectionMatrix * vec4(x,y,z,1.0);
}