#include "gl_cube_widget.h"

#include "Volume.h"
#include "Vector3.h"
#include "Matrix4.h"
#include <math.h>
#include <iostream>
#include <QtOpenGL>

// ****************************************************************************
// *** Basic methods **********************************************************
/// Default constructor
GLCubeWidget::GLCubeWidget(QWidget *parent) : QGLWidget(parent) {
    // Initialize class members
    m_matRotX.identity();
    m_matTrY.identity();
    m_matScale.identity();
    m_prevScale = 1.0;

    // TODO (CA0): add any other necessary initialization here
} /* constructor */


/// Destructor
GLCubeWidget::~GLCubeWidget() {

}


// ***************************************************************************
// *** OpenGL handlers *******************************************************
// Initialize the OpenGL context
void GLCubeWidget::initializeGL() {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
} /* initializeGL() */


// Render a scene in the OpenGL context
void GLCubeWidget::paintGL() {
    // Clear the background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Select the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // The overall tranformation matrix
    Matrix4d mat;

    // TODO (CA0): change this part in order to compute the proper transformation
    mat = m_matRotX * m_matRotY * m_matScale;   // Try this!
    //mat = m_matTrY * m_matRotX;     // Try this!

    // Set the transformation matrix
    glLoadMatrixd(mat.get());

    // Draw the cube
    drawCube();
} /* paintGL() */


// Called when the window is resized
void GLCubeWidget::resizeGL(int width, int height) {
    m_wndWidth = width;
    m_wndHeight =  height;

    glViewport(0, 0, m_wndWidth, m_wndHeight);

    // Set the projection matrix in order to handle the aspect ratio
    glMatrixMode(GL_PROJECTION);
    Matrix4d prj;
    if(width > height)
        prj = Matrix4d::createOrthoPrj(
                -static_cast<double>(width) / (1e-12 + height),
                static_cast<double>(width) / (1e-12 + height),
                - 1., 1., -10., 10.);
    else
        prj = Matrix4d::createOrthoPrj(
                - 1., 1.,
                -static_cast<double>(height) / (1e-12 + width),
                static_cast<double>(height) / (1e-12 + width),
                 -10., 10.);

    glLoadMatrixd(prj.get());
} /* resizeGL() */


// Called when a mouse button is pressed
void GLCubeWidget::mousePressEvent(QMouseEvent *event) {
    std::cout << "GLCubeWidget::mousePressEvent()" << std::endl;
    // TODO (CA0)
    // Get current mouse position from the event object using
    // event->x()
    // event->y()
    int y = event->y();
    int x = event->x();

    // Store the current mouse position in a class variable
    m_prevMouseY = y;
    m_prevMouseX = x;

    updateGL(); // Update the scene (automatically calls paintGL())
} /* mousePressEvent() */


// Called when the mouse moves
void GLCubeWidget::mouseMoveEvent(QMouseEvent *event) {
    std::cout << "GLCubeWidget::mouseMoveEvent()" << std::endl;

    // TODO (CA0)
    // Get current mouse position from the event object using
    //   event->x()
    //   event->y()
    int y = event->y();
    int x = event->x();

    // Compute the mouse displacement with respect to the stored position
    int dy = y - m_prevMouseY;
    int dx = x - m_prevMouseX;

    // Check which button is pressed
    if(event->buttons() & Qt::LeftButton) {
        // Compute the rotation matrix
        Matrix4d rotX;
        rotX.identity();
        rotX.rotate(0.5 * dy, Vector3d(1., 0., 0.));

        // Update the stored transformation with the one just computed
        m_matRotX *= rotX;

        //TODO (CA0): do the same for rotation around the y axis

        Matrix4d rotY;
        rotY.identity();
        rotY.rotate(0.5 * dx, Vector3d(0., 1., 0.));

        // Update the stored transformation with the one just computed
        m_matRotY *= rotY;
    }
    else if(event->buttons() & Qt::RightButton) {
        // Compute the rotation matrix
        Matrix4d trY;
        trY.identity();
        trY.translate(- 0.02 * dy * Vector3d(0., 1., 0.));

        // Update the stored transformation with the one just computed
        m_matTrY *= trY;

        //TODO (CA0): do the same for the translation along the x axis
    }
    // TODO (CA0): scaling when the middle mouse button is pressed (optional)


    // TODO: Overwrite the old mouse position with the current one
    m_prevMouseY = y;
    m_prevMouseX = x;

    updateGL(); // Update the scene (automatically calls paintGL())
} /* mouseMoveEvent() */


// Called when a mouse button is released
void GLCubeWidget::mouseReleaseEvent(QMouseEvent *event) {
    std::cout << "GLCubeWidget::mouseReleaseEvent()" << std::endl;
    // TODO (CA0)
    // Usually there is nothing to do here

    updateGL(); // Update the scene (automatically calls paintGL())
} /* mouseReleaseEvent() */


// Called when the mouse wheel moves
void GLCubeWidget::wheelEvent(QWheelEvent *event) {
    std::cout << "GLCubeWidget::wheelEvent();" << std::endl;
    // TODO (CA0) (Optional)
    // Get the wheel rotation amount with
    //   event->delta();
    // Compute a scaling matrix according to the rotation amount
    // Update the stored transformation with the one just computed

    double deg = (double)event->delta()/8.0;
    double steps = deg/15.0;

    double sc = m_prevScale + ((5*steps)/100.0);

    Matrix4d scale;
    scale.scale(Vector3d(sc,sc,sc));

    m_matScale = scale;
    m_prevScale = sc;

    updateGL(); // Update the scene (automatically calls paintGL())
} /* wheelEvent() */



// ***************************************************************************
// *** Private methods *******************************************************
// Draw a cube on the screen
void GLCubeWidget::drawCube() {
    double volx = 0.5;
    double voly = 0.5;
    double volz = 0.5;

    glBegin(GL_QUADS);
    // First face
    glColor3d(0.0,0.0,1.);
    glVertex3d(-volx, -voly, volz);
    glVertex3d(volx, -voly, volz);
    glVertex3d(volx, voly, volz);
    glVertex3d(-volx, voly, volz);
    // Second face
    glColor3d(1.0,0.0,0.0);
    glVertex3d(volx, -voly, volz);
    glVertex3d(volx, -voly, -volz);
    glVertex3d(volx, voly, -volz);
    glVertex3d(volx, voly, volz);
    // Third face
    glColor3d(1.0,1.0,0.0);
    glVertex3d(volx, -voly, -volz);
    glVertex3d(-volx, -voly, -volz);
    glVertex3d(-volx, voly, -volz);
    glVertex3d(volx, voly, -volz);
    // Fourth face
    glColor3d(0.0,1.0,1.0);
    glVertex3d(-volx, -voly, -volz);
    glVertex3d(-volx, -voly, volz);
    glVertex3d(-volx, voly, volz);
    glVertex3d(-volx, voly, -volz);
    // top face
    glColor3d(0.0,1.0,0.0);
    glVertex3d(-volx, voly, volz);
    glVertex3d(volx, voly, volz);
    glVertex3d(volx, voly, -volz);
    glVertex3d(-volx, voly, -volz);
    // bottom face
    glColor3d(1.0,0.0,1.0);
    glVertex3d(-volx, -voly, -volz);
    glVertex3d(volx, -voly, -volz);
    glVertex3d(volx, -voly, volz);
    glVertex3d(-volx, -voly, volz);
    glEnd();
} /* drawCube() */
