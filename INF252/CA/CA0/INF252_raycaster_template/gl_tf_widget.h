#ifndef GL_TF_WIDGET_H
#define GL_TF_WIDGET_H


#include <QGLWidget>

class TransferFunction;

/// OpenGL widget for displaying a transfer function
class GLTFWidget : public QGLWidget {
    Q_OBJECT

    // ************************************************************************
    // *** Basic methods ******************************************************
public:
    /// Default constructor
    GLTFWidget(QWidget *parent = nullptr);

    /// Destructor
    ~GLTFWidget();

    // ************************************************************************
    // *** Public methods *****************************************************
public:
    /// Set the transfer function to edit
    void setTransferFunction(TransferFunction* tf);

    /// Updates the rendered scene
    void updateContent();


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

    /// Called on double click
    void mouseDoubleClickEvent(QMouseEvent *event);

    /// Called when the mouse wheel moves
    void wheelEvent(QWheelEvent *event);


    // ************************************************************************
    // *** Class members ******************************************************
private:
    TransferFunction *mp_transferFunction;    ///< the controlled transfer function

    int m_wndWidth;           ///< the width of the OpenGL context
    int m_wndHeight;          ///< the height of the OpenGL context

    // TODO (CA2): add anything else you need here



    // ************************************************************************
    // *** Overloaded methods *************************************************
public:
    QSize sizeHint() const {
        return QSize(400, 200);
    }

    QSize minimumSizeHint() const {
        return QSize(50, 50);
    }

}; /* class GLTFWidget */

#endif /* GL_TF_WIDGET_H */
