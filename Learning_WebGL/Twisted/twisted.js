"use strict"

/* global window */
/* global document */
/* global WebGLUtils */
/* global Float32Array */
/* global initShaders */
/* global flatten */

var Twisted = function()
{
    var gl;
    //var points;

    var canvas = document.getElementById("gl-canvas");
    
    gl = WebGLUtils.setupWebGL(canvas);
    if ( !gl ) 
    {
        alert("WebGL isn't available");
    }
    
    var vert = [[-1,-1], [0,1], [1,-1]];
    var flattenedArr = flatten(vert);
    var center = vert.reduce(function(prev, curr, ind, vert)
                            {
        return [prev[0] + curr[0], prev[1] + curr[1]];
    }, 
                            [0,0]);
    
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
    gl.bufferData(gl.ARRAY_BUFFER, flattenedArr, gl.STATIC_DRAW);
    
    //Associate out shader variables with our data buffer
    var vPosition = gl.getAttribLocation(program, "vPosition");
    gl.vertexAttribPointer(vPosition, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray( vPosition);
    
    gl.uniform2fv(gl.getUniformLocation(program, "center"), center);
    gl.uniform1f(gl.getUniformLocation(program, "angle"), 45);
    
    this.render = function()
    {
        gl.clear(gl.COLOR_BUFFER_BIT);
        gl.drawArrays(gl.TRIANGLES, 0, 3);
    };
    
    this.render();
};

window.onload = function init()
{
    new Twisted();
};

