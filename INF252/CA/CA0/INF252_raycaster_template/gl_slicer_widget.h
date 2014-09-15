#ifndef GL_SLICER_WIDGET_H
#define GL_SLICER_WIDGET_H

#include "Matrix4.h"
#include <QGLWidget>

class Volume;
class TransferFunction;


/// OpenGL widget for displaying Slice-based rendering
class GLSlicerWidget : public QGLWidget {
    Q_OBJECT

    // ************************************************************************
    // *** Basic methods ******************************************************
public:
    /// Default constructor
    GLSlicerWidget(QWidget *parent = nullptr);

    /// Destructor
    ~GLSlicerWidget();


    // ************************************************************************
    // *** Public methods *****************************************************
public:
    /// Set the volume to be visualized
    void setVolume(Volume *v);

    /// Set the transfer function to be used (optional)
    void setTransferFunction(TransferFunction* tf);

    /// Updates the rendered scene
    void updateContent();

    // TODO (CA1): add a method to change the selected slice
    void setSlice(int slice);

    // TODO (CA1): add a method to change the selected axis
    void setAxis(int axis);

    // ************************************************************************
    // *** OpenGL handlers ****************************************************
protected:
    /// Initialize the OpenGL context
    void initializeGL();

    /// Render a scene in the OpenGL context
    void paintGL();

    /// Called when the window is resized
    void resizeGL(int width, int height);

    /// Called when a mouse button is pressed
    void mousePressEvent(QMouseEvent *event);

    /// Called when the mouse moves
    void mouseMoveEvent(QMouseEvent *event);

    /// Called when a mouse button is released
    void mouseReleaseEvent(QMouseEvent *event);

    /// Called when the mouse wheel moves
    void wheelEvent(QWheelEvent *event);
    

    // ************************************************************************
    // *** Private methods ****************************************************
private:
    /** Extract an axis-aligned slice from the dataset and store it in the
     *  texture buffer. */
    void updateTexture();


    // ************************************************************************
    // *** Class members ******************************************************
private:
    const Volume *mp_volume; ///< pointer to the volume to be visualized
    const TransferFunction *mp_transferFunction; ///< pointer to the transfer function to be used to display the volume

    int m_wndWidth;           ///< the width of the OpenGL context
    int m_wndHeight;          ///< the height of the OpenGL context

    GLuint m_textureId;       ///< the texture used to show the current slice
    float* m_texBuf;        ///< the actual texture
    int m_texWidth;         ///< width of the texture
    int m_texHeight;        ///< height of the texture

    // TODO (CA1): add a class member to keep track of the the selected axis
    int m_axis; ///0,1,2 is x,y,z
    // TODO (CA1): add anything else you need here
    int m_currSlice;


    // ************************************************************************
    // *** Overloaded methods *************************************************
public:
    QSize sizeHint() const {
        return QSize(600, 600);
    }

    QSize minimumSizeHint() const {
        return QSize(200, 200);
    }


}; /* GLSlicerWidget */

#endif /* GL_SLICER_WIDGET_H */
