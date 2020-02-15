"""
This project contains code to explore and learn about OpenGL technologies.
"""
import sys
import math
from OpenGL.GL import glBegin, glEnd, glColor, glVertexPointerf, glDrawArrays, glFlush, glClearColor, glViewport, glMatrixMode, \
                      glLoadIdentity, glClearDepth, glClear, glVertex, glEnableClientState, GL_PROJECTION, GL_VERTEX_ARRAY, \
                      GL_LINE_STRIP, GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT
from OpenGL.GLU import gluPerspective
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtOpenGL import QGLWidget


class SpiralWidget(QGLWidget):
    def __init__(self, parent):  
        super().__init__(parent)
        self.setMinimumSize(500, 500)

    def paintGL(self):
        """
        Drawing routing
        """
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()

        #Draw spiral in 'immediate mode'
        #WARNING: You should not be doing the spiral calculation inside the loop
        #even if you are using glBegin/glEnd, sin/cos are fairly expensive functions
        #For now left here to make code simpler
        radius = 1.0
        x = radius * math.sin(0)
        y = radius * math.cos(0)
        glColor(0.0, 1.0, 0.0)
        
        glBegin (GL_LINE_STRIP)
        for deg in range(1000):
            glVertex(x,y,0.0)
            rad = math.radians(deg)
            radius -= 0.001
            x = radius * math.sin(rad)
            y = radius * math.cos(rad)
        glEnd()


        glEnableClientState(GL_VERTEX_ARRAY)
        
        #TODO: Use list comprehension
        spiral_array = []

        #Second spiral using "array immediate mode" (i.e vertex arrays)
        radius = 0.8
        x = radius * math.sin(0)
        y = radius * math.cos(0)

        glColor(1.0,0.0, 0.0)
        for deg in range(820):
            spiral_array.append([x,y])
            rad = math.radians(deg)
            radius -= 0.001
            x = radius * math.sin(rad)
            y = radius * math.cos(rad)

        glVertexPointerf(spiral_array)
        glDrawArrays(GL_LINE_STRIP, 0, len(spiral_array))
        glFlush()

    def resizeGL(self, w, h):
        '''
        Resize the GL window
        '''

        glViewport(0, 0, w, h)
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluPerspective(40.0, 1.0, 1.0, 30.0)

    def initializeGL(self):
        '''
        Initialize GL
        '''

        #set viewing projection
        glClearColor(0.0, 0.0, 0.0, 1.0)
        glClearDepth(1.0)


        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()
        gluPerspective(40.0, 1.0, 1.0, 30.0)

class SpiralWidgetDemo(QMainWindow):
    '''
    Example class for using spiralwidget
    '''
    def __init__(self):
        super().__init__()
        widget = SpiralWidget(self)
        self.setCentralWidget(widget)


def main():
    app = QApplication(['Spiral Widget Demo'])
    window = SpiralWidgetDemo()
    window.show()
    sys.exit(app.exec_())

if __name__=='__main__':
    main()