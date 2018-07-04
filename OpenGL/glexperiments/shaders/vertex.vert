#version 330 core

//layout(location = 1) uniform Matrices {
//    mat4 pvm;
//};
//
// the signature
//subroutine vec4 colorRedBlue();

// option 1
//subroutine(colorRedBlue) vec4 redColor() {

//    return vec4(1.0, 0.0, 0.0, 1.0);
//}

// option 2
//subroutine(colorRedBlue) vec4 blueColor() {

//    return vec4(0.0, 0.0, 1.0, 1.0);
//}

//subroutine uniform colorRedBlue myRedBlueSelection;

in vec4 position;

out vec4 color;

void main() {
    //color = myRedBlueSelection();
    //gl_Position = pvm * position;
    gl_Position = position;
}