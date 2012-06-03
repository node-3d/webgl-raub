#ifdef GL_ES
precision highp float;
#endif


uniform vec2 resolution;
uniform float time;

float segm( float a, float b, float c, float x )
{
    return smoothstep(a-c,a,x) - smoothstep(b,b+c,x);
}

vec3 clover( float x, float y )
{
    float a = atan(x,y);
    float r = sqrt(x*x+y*y);
    float s = 0.5 + 0.5*sin(3.0*a + time);
    float g = sin(1.57+3.0*a+time);
    float d = 0.3 + 0.6*sqrt(s) + 0.15*g*g;
    float h = r/d;
    float f = 1.0-smoothstep( 0.95, 1.0, h );
    h *= 1.0-0.5*(1.0-h)*smoothstep(0.95+0.05*h,1.0,sin(3.0*a+time));
    return mix( vec3(1.0), vec3(0.4*h,0.2+0.3*h,0.0), f );
}

vec3 heart( float x, float y )
{
    float s = mod( time, 2.0 )/2.0;
    s = 0.9 + 0.1*(1.0-exp(-5.0*s)*sin(50.0*s));
    x *= s;
    y *= s;
    float a = atan(x,y)/3.141593;
    float r = sqrt(x*x+y*y);

    float h = abs(a);
    float d = (13.0*h - 22.0*h*h + 10.0*h*h*h)/(6.0-5.0*h);

    float f = smoothstep(d-0.02,d,r);
    float g = pow(1.0-clamp(r/d,0.0,1.0),0.25);
    return mix(vec3(0.5+0.5*g,0.2,0.1),vec3(1.0),f);
}

vec3 yinyan( float x, float y )
{
    float nx = x;
    float ny = y;
    x = 1.5*(nx*cos(0.2*time) - ny*sin(0.2*time));
    y = 1.5*(nx*sin(0.2*time) + ny*cos(0.2*time));
    float h = x*x + y*y;
    float d = abs(y)-h;
    float a = d-0.23;
    float b = h-1.00;
    float c = sign(a*b*(y+x + (y-x)*sign(d)));

    c = mix( c, 0.0, smoothstep(0.98,1.00,h) );
    c = mix( c, 1.0, smoothstep(1.00,1.02,h) );
    return vec3(c);
}

vec3 sun( float x, float y )
{
    float a = atan(x,y);
    float r = sqrt(x*x+y*y);

    float s = 0.5 + 0.5*sin(a*17.0+1.5*time);
    float d = 0.5 + 0.2*pow(s,1.0);
    float h = r/d;
    float f = 1.0-smoothstep(0.92,1.0,h);

    float b = pow(0.5 + 0.5*sin(3.0*time),500.0);
    vec2 e = vec2( abs(x)-0.15,(y-0.1)*(1.0+10.0*b) );
    float g = 1.0 - (segm(0.06,0.09,0.01,length(e)))*step(0.0,e.y);

    float t = 0.5 + 0.5*sin(12.0*time);
    vec2 m = vec2( x, (y+0.15)*(1.0+10.0*t) );
    g *= 1.0 - (segm(0.06,0.09,0.01,length(m)));

    return mix(vec3(1.0),vec3(0.9,0.8,0.0)*g,f);
}

void main(void)
{
    vec2 p = (-1.0+2.0*gl_FragCoord.xy/resolution.xy);

    vec3 col = yinyan(1.0+2.0*p.x,1.0+2.0*p.y);
    col *= heart( -1.0+2.0*p.x, 1.0+2.0*p.y );
    col *= sun( -1.0+2.0*p.x, -1.0+2.0*p.y );
    col *= clover( 1.0+2.0*p.x, -1.0+2.0*p.y );
    gl_FragColor = vec4(col,1.0);

}
