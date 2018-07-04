in vec4 color;

uniform ColorBlock {
    vec4 diffuse;
    vec4 ambient;
}

void main() {
    gl_FragColor = color;
}