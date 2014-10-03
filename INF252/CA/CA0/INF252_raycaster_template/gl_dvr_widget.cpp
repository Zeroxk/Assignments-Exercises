#include "gl_dvr_widget.h"

#include "Matrix4.h"
#include "TransferFunction.h"
#include "Vector3.h"
#include "Volume.h"
#include <iostream>
#include <QtGui>
#include <QtOpenGL>



// ****************************************************************************
// *** Public methods *********************************************************
// Default constructor
GLDvrWidget::GLDvrWidget(QWidget *parent) : QGLWidget(parent),
    mp_volume(nullptr),
    mp_transferFunction(nullptr),
    m_textureId(0),
    m_texBuf(nullptr),
    m_texWidth(0),
    m_texHeight(0)
    // TODO (CA2): initialize default values here
{

} /* constructor */

// Destructor
GLDvrWidget::~GLDvrWidget() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &m_textureId);
    delete [] m_texBuf;
    // TODO (CA2): deallocate anything else here
} /* destructor */


// ************************************************************************
// *** Public methods *****************************************************
// Set the volume to be visualized
void GLDvrWidget::setVolume(Volume* v) {
    assert(v);
    mp_volume = v;
    // TODO (CA2): initialize everything you need according to the new Volume
}

// Set the transfer function to be used
void GLDvrWidget::setTransferFunction(TransferFunction* tf) {
    mp_transferFunction = tf;
}

// Updates the rendered scene
void GLDvrWidget::updateContent() {
    if(mp_volume) {
        updateTexture();  // Update the texture buffer
        updateGL();  // Update the display (cautomatically call paintGL())
    }
}


// ****************************************************************************
// *** OpenGL handlers ********************************************************
// Initialize the OpenGL context
void GLDvrWidget::initializeGL() {
    glClearColor(0, 0, 0, 1);   // Background color
    glEnable(GL_DEPTH_TEST);    // Enable depth test
    glEnable(GL_TEXTURE_2D);    // Enable 2D textures

    // Initialize the texture object
    glGenTextures(1,&m_textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Try GL_LINEAR
    glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Try GL_LINEAR
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Create a fake default texture
    m_texWidth = m_texHeight = 2;
    m_texBuf = new float[3 * m_texWidth * m_texHeight];
    m_texBuf[ 0] = 1.0f; m_texBuf[ 1] = 0.0f; m_texBuf[ 2] = 0.0f;
    m_texBuf[ 3] = 0.0f; m_texBuf[ 4] = 1.0f; m_texBuf[ 5] = 0.0f;
    m_texBuf[ 6] = 0.0f; m_texBuf[ 7] = 0.0f; m_texBuf[ 8] = 1.0f;
    m_texBuf[ 9] = 0.5f; m_texBuf[10] = 0.5f; m_texBuf[11] = 0.5f;
} /* initializeGL() */


// Render a scene in the OpenGL context
void GLDvrWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_texWidth, m_texHeight, 0,
        GL_RGB, GL_FLOAT, m_texBuf);

    // Draw a textured quad that covers the entire screen
    glBegin(GL_QUADS);
    glColor3f(1.0f,1.0f,1.0f);
    glTexCoord2f(0,0); glVertex2f(-1,-1);
    glTexCoord2f(1,0); glVertex2f(1,-1);
    glTexCoord2f(1,1); glVertex2f(1,1);
    glTexCoord2f(0,1); glVertex2f(-1,1);
    glEnd();
} /* paintGL() */


// Called when the window is resized
void GLDvrWidget::resizeGL(int width, int height) {
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
}

// Called when a mouse button is pressed
void GLDvrWidget::mousePressEvent(QMouseEvent *event) {
    std::cout << "GLDvrWidget::mousePressEvent()" << std::endl;
    // TODO (CA2)
    int y = event->y();
    m_prevMouseY = y;

    this->updateContent();
}

// Called when the mouse moves
void GLDvrWidget::mouseMoveEvent(QMouseEvent *event) {
    std::cout << "GLDvrWidget::mouseMoveEvent()" << std::endl;
    // TODO (CA2)
    this->updateContent();
}

// Called when a mouse button is released
void GLDvrWidget::mouseReleaseEvent(QMouseEvent *event) {
    std::cout << "GLDvrWidget::mouseReleaseEvent()" << std::endl;
    // TODO (CA2)
    this->updateContent();
}

// Called when the mouse wheel moves
void GLDvrWidget::wheelEvent(QWheelEvent *event) {
    std::cout << "GLDvrWidget::wheelEvent();" << std::endl;
    // TODO (CA2)
    this->updateContent();
}

// ****************************************************************************
// *** Private methods ********************************************************
/** Store the Direct Volume Rendering of the dataset and store it in the
 *  texture buffer. */
void GLDvrWidget::updateTexture() {
    assert(mp_volume);
    assert(mp_transferFunction);

    // TODO (CA2): perform Direct Volume Rendering here



} /* updateTexture() */
