 #include "gl_slicer_widget.h"

#include "TransferFunction.h"
#include "Vector3.h"
#include "Volume.h"
#include <iostream>
#include <QtGui>
#include <QtOpenGL>



// ************************************************************************
// *** Basic methods ******************************************************
/// Default constructor
GLSlicerWidget::GLSlicerWidget(QWidget *parent) : QGLWidget(parent),
    mp_volume(nullptr),
    mp_transferFunction(nullptr),
    m_textureId(0),
    m_texBuf(nullptr),
    m_texWidth(0),
    m_texHeight(0),
    m_axis(0),
    m_currSlice(0)
    // TODO (CA1): initialize default values here
{

} /* constructor */

/// Destructor
GLSlicerWidget::~GLSlicerWidget() {
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &m_textureId);
    delete [] m_texBuf;
    // TODO (CA1): deallocate anything else here
} /* destructor */


// ************************************************************************
// *** Public methods *****************************************************
/// Set the volume to be visualized
void GLSlicerWidget::setVolume(Volume *v) {
    assert(v);
    mp_volume = v;
    // TODO (CA1): initialize everything you need according to the new Volume


}

/// Set the transfer function to be used (Optional)
void GLSlicerWidget::setTransferFunction(TransferFunction* tf) {
    mp_transferFunction = tf;
}

/// Updates the rendered scene
void GLSlicerWidget::updateContent() {
    if(mp_volume) {
        updateTexture();  // Update the texture buffer
        updateGL();  // Update the display (cautomatically call paintGL())
    }
}

void GLSlicerWidget::setSlice(int slice) {
    m_currSlice = slice;
}

void GLSlicerWidget::setAxis(int axis) {
    m_axis = axis;

}

// ************************************************************************
// *** OpenGL handlers ****************************************************
/// Initialize the OpenGL context
void GLSlicerWidget::initializeGL() {
    glClearColor(0, 0, 0, 1);   // Background color
    glEnable(GL_DEPTH_TEST);    // Enable depth test
    glEnable(GL_TEXTURE_2D);    // Enable 2D textures

    // Initialize the texture object
    glGenTextures(1,&m_textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_NEAREST); // TODO (CA1): Try GL_LINEAR
    glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_NEAREST); // TODO (CA1): Try GL_LINEAR
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Set a default texture
    m_texWidth = 3;
    m_texHeight = 2;
    m_texBuf = new float[m_texWidth * m_texHeight];
    m_texBuf[ 0] = 1.0f; m_texBuf[ 1] = 0.6f; m_texBuf[ 2] = 0.2f;
    m_texBuf[ 3] = 0.8f; m_texBuf[ 4] = 0.4f; m_texBuf[ 5] = 0.0f;
}

/// Render a scene in the OpenGL context
void GLSlicerWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the texture (change GL_LUMINANCE to GL_RGB for colors)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_texWidth, m_texHeight, 0,
        GL_LUMINANCE, GL_FLOAT, m_texBuf);

    // Draw a textured quad that covers the entire screen
    glBegin(GL_QUADS);
    glColor3f(1.0f,1.0f,1.0f);
    glTexCoord2f(0,0); glVertex2f(-1,-1);
    glTexCoord2f(1,0); glVertex2f(1,-1);
    glTexCoord2f(1,1); glVertex2f(1,1);
    glTexCoord2f(0,1); glVertex2f(-1,1);
    glEnd();
} /* paintGL() */


/// Called when the window is resized
void GLSlicerWidget::resizeGL(int width, int height) {
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

/// Called when a mouse button is pressed
void GLSlicerWidget::mousePressEvent(QMouseEvent *event) {
    std::cout << "GLSlicerWidget::mousePressEvent()" << std::endl;
    // TODO (CA1)
    this->updateContent();
}

/// Called when the mouse moves
void GLSlicerWidget::mouseMoveEvent(QMouseEvent *event) {
    std::cout << "GLSlicerWidget::mouseMoveEvent()" << std::endl;
    // TODO (CA1)
    this->updateContent();
}

/// Called when a mouse button is released
void GLSlicerWidget::mouseReleaseEvent(QMouseEvent *event) {
    std::cout << "GLSlicerWidget::mouseReleaseEvent()" << std::endl;
    // TODO (CA1)
    this->updateContent();
}

/// Called when the mouse wheel moves
void GLSlicerWidget::wheelEvent(QWheelEvent *event) {
    std::cout << "GLSlicerWidget::wheelEvent();" << std::endl;
    // TODO (CA1) (optional)
    this->updateContent();
}


// ************************************************************************
// *** Private methods ****************************************************
/** Extract an axis-aligned slice from the dataset and store it in the
 *  texture buffer. */
void GLSlicerWidget::updateTexture() {
    assert(mp_volume);
    assert(mp_transferFunction);

    // TODO (CA1): compute slice rendering here

    if(m_axis == 0) { //xy slice
        fillTexBuf(mp_volume->getWidth(), mp_volume->getHeight());
    }else if(m_axis == 1) { //yz slice
        fillTexBuf(mp_volume->getHeight(), mp_volume->getDepth());
    }else if(m_axis == 2) { //xz slice
        fillTexBuf(mp_volume->getWidth(), mp_volume->getDepth());
    }

} /* updateTexture() */

void GLSlicerWidget::fillTexBuf(int W, int H) {

    if(m_texBuf) delete [] m_texBuf;
    m_texHeight = H;
    m_texWidth = W;
    m_texBuf = new float[W*H];

    //std::cout << "W " << W << "\tH " << H << "\tD " << D << std::endl;

    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            //std::cout << "i " << i << "\t j " << j << std::endl;
            if(m_axis == 0) {
                m_texBuf[(j*W)+i] = mp_volume->getVoxel(i,j,m_currSlice);
            }else if(m_axis == 1) {
                m_texBuf[(j*W)+i] = mp_volume->getVoxel(m_currSlice,i,j);
            }else {
                m_texBuf[(j*W)+i] = mp_volume->getVoxel(i,m_currSlice,j);
            }

            //m_texBuf[j*W+i] = mp_volume->getData()[m_currSlice*H*W+j*W+i];
        }
    }
}
