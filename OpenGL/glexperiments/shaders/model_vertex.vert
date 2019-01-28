layout(std140) uniform Matrices {
    mat4 pvm;
    mat3 normal;
};

in vec3 position;
in vec3 normal;
in vec2 texCoord;

void main() {
    //color = myRedBlueSelection();
    gl_Position = pvm * position;
}