#ifdef GL_ES
precision highp float;
#endif

uniform float time;
uniform vec2 resolution;

float j, k, g=acos(-1.0), h= sqrt( 0.75 ), expand;


vec2 r(vec2 v,float y)
{
  return cos(y)*v+sin(y)*vec2(-v.y,v.x);
}

void s(inout vec2 v,float x, float y)
{
  float z=mod(atan(v.y,v.x),y)-y*.5;
  v=(length(v))*vec2(cos(z),sin(z));
  v.x-=x;
}

float l(vec3 p,float f)
{
  return length(vec2(length(p.xz) - f,p.y));
}

float i( vec2 p, float y, float z )
{
    return length( max( abs(p) - vec2(y) + vec2(z), 0.0 ) ) - z;
}

float u( vec3 p )
{
  return fract( sin( p.x * 151.0 + p.y * 33.0 + p.z ) * 11.0 );
}

float w(vec3 p)
{
  vec2 e = vec2(1.0, 0.0);
  vec3 o= smoothstep(0.0,1.0,fract( p ));
  p= floor( p );

  vec4 n= mix(
    vec4(
      u( p+e.yyy),//n000,
      u( p+e.xyy),//n100,
      u( p+e.yxy),//n010,
      u( p+e.xxy)),//n110),
    vec4(
      u( p+e.yyx),//n001,
      u( p+e.xyx),//n101,
      u( p+e.yxx),//n011,
      u( p+e.xxx)),//n111),
    o.z);
  e = mix(n.xy, n.zw, o.y);
  return mix(e.x, e.y, o.x);
}

float A(vec3 p)
{
  vec3 o= p;
  p.x= mod( p.x + step( 2.0 * h, mod( p.y, 4.0 * h ) ), 2.0 ) - 1.0;
  p.y= mod( p.y, 2.0 * h )- h;

  o-= p;
  p.z-= (k == 10.0 ? 0.0 : 44.0) + 2.0 * smoothstep( -0.3, 0.3, cos( o.x * 0.03 + cos( o.y * 0.03 ) + j * 4.0 ) * cos( o.y * 0.01 + cos( o.x * 0.02 ) ) );
  float z= length( p )- 1.5;
  s( p.xy, 0.7, g/3.0);
  return max( z, p.x );
}

float B(vec3 p)
{

  return length( p+vec3(sin( j* 3.0) * 22.0,j * 11.0,-22.0))- 22.0;
}

float C(vec3 p)
{
  vec3 o= p;
  p.x= mod( p.x + step( 2.0 * h, mod( p.y, 4.0 * h ) ), 2.0 ) - 1.0;
  p.y= mod( p.y, 2.0 * h )- h;

  return max( abs( p.z + 1.0 ) - 0.2, h - length( p.xy ) );
}

float D(vec3 p)
{
  return length( p-vec3(22.0,22.0,-14.0))- expand * 33.0 - 12.0;
}

float f(vec3 p)
{
  float z= min( min( A(p), B(p) ), C(p) );
  return max(length(p) - 77.0, min( z, max( 0.5 - z, D(p) ) ) );
}

void main()
{
        float CurTime= mod( time, 60.0 );
        j= CurTime / 12.0;

  vec3 q = vec3((gl_FragCoord.xy / resolution.xy - 0.5), 1.0);

  vec3 p;
        k= 0.0;
  if( j < 1.0 )
  {
                expand= 0.0;
                k= 10.0;
    p= vec3( 33.0, 33.0, -11.0 + j * 5.0);
    q.yz= r( q.yz, 0.8 - j );
    q.xz= r( q.xz, 0.5 + j );
  }
  else if( j < 2.0 )
  {
                j-= 1.0;
                expand= j*j;
    p= vec3(-11.0, -11.0, -11.0);
    q.yz= r( q.yz, -j * 0.7  );
    q.xz= r( q.xz, -j );
  }
  else if( j < 3.0 )
  {
                j-= 2.0;
                expand= j*j;
    p= vec3(33.0, 11.0, 33.0);
    q.yz= r( q.yz, j * 0.4  );
    q.xz= r( q.xz, 1.2 + j * 0.6);
  }
  else
  {
                j= ( j - 3.0 ) * 0.5;
                expand= j*j * 2.0;
    p= vec3( mix( 22.0 - 88.0 * expand, -44.0 * j, j), 22.0, 6.0 );
    q.yz= r( q.yz, j * 0.2 );
    q.xz= r( q.xz, 3.4 + sqrt(j) * 1.4 );
  }

  q = normalize(q);

  vec3 b= vec3( .0,.0,.0 );
  float a=1.0;

  float t=w( q*666.0 )*0.5,y,z,d;
        float m= 0.0;

  for(int mm= 0; mm < 2; ++mm)
  {
                for( int tt= 0; tt < 256; ++tt )
                {
                        d = f(p+q*t);
                        t+=max( 0.01, d+0.01);
                        if( !(t<66.0 && d>t*.003) )
                        {
                               break;
                        }
                }

    if( t > 66.0 )
    {
      break;
    }

                m+= 1.0;

    p+= q*t;

    vec2 e = vec2(0.04, 0.0);
    vec3 n= vec3( f(p + e.xyy) - f(p - e.xyy), f(p + e.yxy) - f(p - e.yxy), f(p + e.yyx) - f(p - e.yyx) );
    n= normalize(n);

    z= A(p);

    vec3 c = vec3(0.8,.0,.0 );
    d= .15;

    if( z > D(p) )
    {
      z= D(p);
      c = vec3(1.0,0.0,0.0 );
      d= .15;
    }
    if( z > B(p) )
    {
      z= B(p);
      c = vec3(0.05,.1,.2 );
      d= .7;
      e.y= 0.3;
    }
    if( z > C(p) )
    {
      z= C(p);
      c = vec3(0.0,0.6,0.8 ) * (0.9 - 0.15 / clamp(dot( n, q ), -1.0, -0.05));
      d= .2;
      e.y= 2.0;
    }

    n+= (w( p * e.y ) + w( p * e.y * 2.0 ) + w( p * e.y * 4.0 )) * e.x;
    n= normalize(n);
    q= reflect( q, n );

    z= 1.0;
    for (float yy=6.0;yy>0.;yy--)
    {
      z-=(yy*.5-f(p+n*yy*.5))/exp2(yy);
    }
    c*= z;

    n.yz= r( n.yz, 0.6 );

    c*= .4 + .3 * ( 1.0 - abs( n.y - .9 ) );


    b+= a*c;
    a*= d;
    t= 0.3;
  }

  q.yz= r( q.yz, 0.6 );
        p=vec3(0.7 + q.y * 0.2);
  if( m < 1.0 )
  {
    p*= vec3( 0.95, 1.1, 1.2);
  }

  if( q.y > 0.0 )
  {
    s(q.xz, 0.4, g/8.0);
    q.x= abs( q.x ) - .2;
    p+= pow( smoothstep(.2, .0, mix( abs(q.z),length(q.xz), step(0.0, q.x) ) ), 22.0 );
  }

  gl_FragColor.xyz = b + a*p;
}
