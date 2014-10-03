#ifndef GL_DVR_WIDGET_H
#define GL_DVR_WIDGET_H

#include <QGLWidget>

class TransferFunction;
class Volume;

/// OpenGL widget for displaying Direct Volume Rendering
class GLDvrWidget : public QGLWidget {
	Q_OBJECT

    // ************************************************************************
    // *** Basic methods ******************************************************
public:
    /// Default constructor
    GLDvrWidget(QWidget *parent = nullptr);

    /// Destructor
    ~GLDvrWidget();


    // ************************************************************************
    // *** Public methods *****************************************************
public:
    /// Set the volume to be visualized
    void setVolume(Volume* v);

    /// Set the transfer function to be used
    void setTransferFunction(TransferFunction* tf);

    /// Updates the rendered scene
    void updateContent();

    // TODO (CA2&3): add any other method you need here


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
    /** Store the Direct Volume Rendering of the dataset and store it in the
     *  texture buffer. */
    void updateTexture();


    // ************************************************************************
    // *** Class members ******************************************************
private:
    /// pointer to the volume to be visualized
    Volume *mp_volume;
    /// pointer to the transfer function to be used to display the volume
    TransferFunction *mp_transferFunction;

    int m_wndWidth;           ///< the width of the OpenGL context
    int m_wndHeight;          ///< the height of the OpenGL context

    GLuint m_textureId;       ///< the texture used to show the current slice
    float* m_texBuf;          ///< the actual texture
    int m_texWidth;           ///< width of the texture
    int m_texHeight;          ///< height of the texture

    // TODO (CA2&3): add anything else you need here

    int m_prevMouseY;
    int m_prevMouseX;


    // ************************************************************************
    // *** Overloaded methods *************************************************
public:
    QSize sizeHint() const {
        return QSize(600, 600);
    }

    QSize minimumSizeHint() const {
        return QSize(200, 200);
    }


}; /* class GLDvrWidget */

#endif /* GL_DVR_WIDGET_H */
