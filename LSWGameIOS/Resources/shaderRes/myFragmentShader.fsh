varying vec4 v_fragmentColor;

uniform vec4 u_color;

void main()
{
    gl_FragColor = v_fragmentColor * u_color;
}