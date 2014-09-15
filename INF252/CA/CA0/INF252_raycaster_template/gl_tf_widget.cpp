#include "gl_tf_widget.h"

#include "Matrix4.h"
#include "TransferFunction.h"
#include "Vector3.h"
#include <math.h>
#include <iostream>
#include <QtGui>
#include <QtOpenGL>


// ************************************************************************
// *** Basic methods ******************************************************
// Default constructor
GLTFWidget::GLTFWidget(QWidget *parent) : QGLWidget(parent),
    mp_transferFunction(nullptr)
    // TODO (CA2): initialize default values here
{

} /* constructor */

// Destructor
GLTFWidget::~GLTFWidget(){
    // TODO (CA2): deallocate everything here
} /* destructor */


// ************************************************************************
// *** Public methods *****************************************************
// Set the transfer function to edit
void GLTFWidget::setTransferFunction(TransferFunction* tf) {
    mp_transferFunction = tf;
}

// Updates the rendered scene
void GLTFWidget::updateContent() {
    if(mp_transferFunction)
        updateGL();
}


// ************************************************************************
// *** OpenGL handlers ****************************************************
// Initialize the OpenGL context
void GLTFWidget::initializeGL() {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_POINT_SMOOTH);
}

// Render a scene in the OpenGL context
void GLTFWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO (CA2): draw the transfer function here
}

// Called when the window is resized
void GLTFWidget::resizeGL(int width, int height) {
    m_wndWidth = width;
    m_wndHeight =  height;

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    Matrix4d prj = Matrix4d::createOrthoPrj(- 1., 1., -1., 1., -10., 10.);
    glLoadMatrixd(prj.get());

    // Set the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, m_wndWidth, m_wndHeight);
}

// Called when a mouse button is pressed
void GLTFWidget::mousePressEvent(QMouseEvent *event) {
    std::cout << "GLTFWidget::mousePressEvent()" << std::endl;
    // TODO (CA2)
    this->updateContent();
}

// Called when the mouse moves
void GLTFWidget::mouseMoveEvent(QMouseEvent *event) {
    std::cout << "GLTFWidget::mouseMoveEvent()" << std::endl;
    // TODO (CA2)
    this->updateContent();
}

// Called when a mouse button is released
void GLTFWidget::mouseReleaseEvent(QMouseEvent *event) {
    std::cout << "GLTFWidget::mouseReleaseEvent()" << std::endl;
    // TODO (CA2)
    this->updateContent();
}

// Called on double click
void GLTFWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    std::cout << "GLTFWidget::mouseDoubleClickEvent()" << std::endl;
    // TODO (CA2)
    this->updateContent();
}

// Called when the mouse wheel moves
void GLTFWidget::wheelEvent(QWheelEvent *event) {
    std::cout << "GLTFWidget::wheelEvent()" << std::endl;
    // TODO (CA2)
    this->updateContent();
}

