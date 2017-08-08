"use strict";

var mouse_paint = function()
{
    var self = this
    var maxNumTriangles = 200;
    var maxNumVertices  = 3 * maxNumTriangles;
    var segments = [];
    var index = 0;

    var t1, t2, t3, t4;

    var cIndex = 0;

    var colors = [
        vec4( 0.0, 0.0, 0.0, 1.0 ),  // black
        vec4( 1.0, 0.0, 0.0, 1.0 ),  // red
        vec4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
        vec4( 0.0, 1.0, 0.0, 1.0 ),  // green
        vec4( 0.0, 0.0, 1.0, 1.0 ),  // blue
        vec4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
        vec4( 0.0, 1.0, 1.0, 1.0 )   // cyan
    ];

    var canvas = document.getElementById( "gl-canvas" );

    var gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    gl.viewport( 0, 0, canvas.width, canvas.height );
    gl.clearColor( 0.0, 0.0, 0.0, 1.0 );

    //
    //  Load shaders and initialize attribute buffers
    //
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );


    var vBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, 8*maxNumVertices, gl.STATIC_DRAW);

    var vPosition = gl.getAttribLocation( program, "vPosition");
    gl.vertexAttribPointer(vPosition, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(vPosition);

    var cBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, cBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, 16*maxNumVertices, gl.STATIC_DRAW );

    var vColor = gl.getAttribLocation( program, "vColor");
    gl.vertexAttribPointer(vColor, 4, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(vColor);

    var m = document.getElementById("mymenu");

    m.addEventListener("click", function() {
        cIndex = m.selectedIndex;
    });

    var first = true;
    canvas.addEventListener("mousedown", function(event)
    {
        gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer);

        var t = vec2(2*event.clientX/canvas.width-1,
            2*(canvas.height-event.clientY)/canvas.height-1);
        gl.bufferSubData(gl.ARRAY_BUFFER, sizeof['vec2']* index, t);
        index++;
    } );

    canvas.addEventListener("mousemove", function(event)
    {
        gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
        var t = vec2(2*event.clientX/canvas.width-1,
            2*(canvas.height-event.clientY)/canvas.height-1);
        gl.bufferSubData(gl.ARRAY_BUFFER, sizeof['vec2']* index, t);
        index++;

    });

    canvas.addEventListener("mouseup", function(event)
    {
        segments.push(index);
        index = 0;
    });

    this.render = function() {

        gl.clear( gl.COLOR_BUFFER_BIT );

        segments.forEach(function(index)
        {
            for (var i = 0; i < index; i++)
                gl.drawArrays(gl.LINE_STRIP, i, 1);
        });

        window.requestAnimFrame(self.render);
    }

    this.render();
};


window.onload = function init()
{
    new mouse_paint();
}


