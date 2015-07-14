"use strict"

/* global window */
/* global document */
/* global WebGLUtils */
/* global initShaders */
/* global flatten */
/* global mix */
/* global vec4 */
/* global WebGLDebugUtils */

var Twisted = function()
{
    var gl;
    var points = [];
    var numOfSubdivisions = 10;
    var canvas = document.getElementById("gl-canvas");
    var twistAngle = 0.0;
    var self = this;
    document.getElementById("slide").onchange =
        function() { twistAngle = event.srcElement.value; self.render();};
    
    document.getElementById("subdiv").onchange = 
        function() { 
            numOfSubdivisions = parseInt(event.srcElement.value); 
            self.render(); };
    
    gl = WebGLUtils.setupWebGL(canvas);
//    var ctx = WebGLDebugUtils.makeDebugContext(canvas.getContext("webgl"));
    
    if ( !gl ) 
    {
        alert("WebGL isn't available");
    }
        
    var vert = [[-0.5,-0.5], [0,0.5], [0.5,-0.5]];
    var center = vert.reduce(function(prev, curr, ind, vert)  {
        return [prev[0] + curr[0], prev[1] + curr[1]];
        }, [0,0]);

    
    center = [center[0] / vert.length, center[1] / vert.length];
    console.log(center);

    //Configure WebGL
    gl.viewport(0,0, canvas.width, canvas.height);
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    
    //Load shaders and initialize attribute buffers
    var program = initShaders(gl, "vertex-shader", "fragment-shader");
    gl.useProgram(program);
    var bufferId = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, bufferId);
    
    //Associate out shader variables with our data buffer
    var vPosition = gl.getAttribLocation(program, "vPosition");
    gl.vertexAttribPointer(vPosition, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray( vPosition);
    
    gl.uniform2fv(gl.getUniformLocation(program, "center"), center);
    
    
    gl.uniform4fv(gl.getUniformLocation(program, "color"), 
                                       vec4(1.0, 0.0, 0.0, 1.0));
    this.render = function()
    {
        points = [];
        divideTriangle(vert[0], vert[1], vert[2], numOfSubdivisions);

        gl.bufferData(gl.ARRAY_BUFFER, flatten(points), gl.STATIC_DRAW);
        gl.uniform1f(gl.getUniformLocation(program, "angle"), twistAngle);
        gl.clear(gl.COLOR_BUFFER_BIT);
        gl.drawArrays(gl.TRIANGLES, 0, points.length);
    };
    
    this.render();
    
    function divideTriangle( a, b, c, count )
    {
        // check for end of recursion
        if ( count === 0 ) {
            points.push( a, b, c );
        }
        else {
            //bisect the sides
            var ab = mix( a, b, 0.5 );
            var ac = mix( a, c, 0.5 );
            var bc = mix( b, c, 0.5 );

            // four new triangles
            divideTriangle( a, ab, ac, count - 1);
            divideTriangle( c, ac, bc, count - 1);
            divideTriangle( b, bc, ab, count - 1);
            divideTriangle(ab, ac, bc, count - 1);
        }
    }
};

window.onload = function init()
{
    new Twisted();
};

