uniform vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

uniform ColorBlock {
    vec4 diffuse;
    vec4 ambient;
};

in vec2 texCoord;

void main() {
    gl_FragColor = color;
}