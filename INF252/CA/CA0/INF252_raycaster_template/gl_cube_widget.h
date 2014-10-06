#ifndef GL_WIDGET_CUBE_H
#define GL_WIDGET_CUBE_H

#include "Matrix4.h"
#include <QGLWidget>


class GLCubeWidget : public QGLWidget {
	Q_OBJECT

    // ************************************************************************
    // *** Basic methods ******************************************************
public:
    /// Default constructor
    GLCubeWidget(QWidget *parent=0);

    /// Destructor
    ~GLCubeWidget();


    // ***********************************************************************
    // *** OpenGL handlers ***************************************************
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


    // ***********************************************************************
    // *** Class members *****************************************************
private:
    int m_wndWidth;     ///< the width of the OpenGL context
    int m_wndHeight;    ///< the height of the OpenGL context

    int m_prevMouseY;   ///< Y-position of the mouse at the last callback
    int m_prevMouseX;

    double m_prevScale;

    // TODO (CA0): define here any other class variable you may need

    Matrix4d m_matRotX; ///< Matrix for the rotation around the Y axis
    Matrix4d m_matRotY;
    Matrix4d m_matTrY;  ///< Matrix for the translation along the Y axis
    Matrix4d m_matTryX;

    Matrix4d m_matScale;

    // TODO (CA0): define here any other matrix you may need



    // ***********************************************************************
    // *** Private methods ***************************************************
private:
    /// Draw a cube on the screen
    void drawCube();


    // ***********************************************************************
    // *** Overloaded methods ************************************************
public:
    QSize sizeHint() const { return QSize(600, 600); }
    QSize minimumSizeHint() const { return QSize(200, 200); }

}; /* class GLWidgetCube */

#endif /* GL_WIDGET_CUBE_H */


