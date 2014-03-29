#ifdef GL_ES
precision highp float;
#endif

uniform float time;
uniform vec2 resolution;
uniform vec4 mouse;
uniform sampler2D tex0;

float spow( float x, float y ) { float s = sign( x ); return s*pow( s*x, y ); }

vec3 doit( in vec2 pix )
{
    vec2 p = -1.0 + 2.0*pix;
    p.x *= resolution.x/resolution.y;

    vec3 ro = vec3( 0.0, 0.0, 2.5 );
    vec3 rd = normalize( vec3( p, -2.0 ) );

    vec3 col = vec3(0.0);

    // intersect sphere
    float b = dot(ro,rd);
    float c = dot(ro,ro) - 1.0;
    float h = b*b - c;
    if( h>0.0 )
    {
        float t = -b - sqrt(h);
        vec3 pos = ro + t*rd;
        vec3 nor = pos;

        // texture mapping
        vec2 uv;
        uv.x = atan(nor.x,nor.z)/6.2831 - 0.05*time - mouse.x/resolution.x;
        uv.y = -acos(nor.y)/3.1416;
        uv.y = 0.5 + spow( uv.y-0.5, 1.2 );
        col = texture2D(tex0,uv).xyz;

        // lighting
        col *= 0.3 + 0.7*max(nor.x*2.0+nor.z,0.0);
    }

    return col;
}

void main(void)
{
    // render this with four sampels per pixel
    vec3 col0 = doit( (gl_FragCoord.xy+vec2(0.0,0.0) )/resolution.xy );
    vec3 col1 = doit( (gl_FragCoord.xy+vec2(0.5,0.0) )/resolution.xy );
    vec3 col2 = doit( (gl_FragCoord.xy+vec2(0.0,0.5) )/resolution.xy );
    vec3 col3 = doit( (gl_FragCoord.xy+vec2(0.5,0.5) )/resolution.xy );
    vec3 col = 0.25*(col0 + col1 + col2 + col3);

    gl_FragColor = vec4(col,1.0);
}
