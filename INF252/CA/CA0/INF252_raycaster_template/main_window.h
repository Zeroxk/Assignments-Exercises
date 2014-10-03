#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "TransferFunction.h"
#include "Volume.h"
#include <QMainWindow>

class GLCubeWidget;
class GLSlicerWidget;
class GLDvrWidget;
class GLTFWidget;
class QComboBox;
class QDialog;
class QDoubleSpinBox;
class QSlider;


/// Main window of the application
class MainWindow : public QMainWindow {
    Q_OBJECT

    // ************************************************************************
    // *** Public methods *****************************************************
public:
    /// Default constructor
    MainWindow(QWidget *parent = nullptr);

    /// Destructor
    ~MainWindow();


    /// Reinitialize everything when a new volume is loaded
    void init();


    // ************************************************************************
    // *** Slots **************************************************************
public slots:
    // --- General ------------------------------
    /// Load a dataset
    void loadVolume();

    /// Open a dialog to edit a transfer function
    void openTFEditor();

    /// Update the content of the OpenGL widgets
    void updateContent();


    // --- Slicer Tab ---------------------------
    /// Change the current slicing axis
    void changeSlicerAxis(int axis);

    /// Change the currently displayed slice
    void changeSlicerSlice(int slice);

    void changeContrast(int exp);


    // --- DVR Tab ------------------------------
    /// Called when the dynamic resolution dropdown menu changes
    void changeDvrDynamicResolution(int id);

    /// Called when the gradient interpolation mode dropdown menu changes
    void changeDvrGradientInterpolationMode(int id);

    /// Called when the gradient computation mode dropdown menu changes
    void changeDvrGradientMode(int id);

    /// Called when the interpolation mode dropdown menu changes
    void changeDvrInterpolationMode(int id);

    /// Called when the projection mode dropdown menu is changed
    void changeDvrProjectionMode(int id);

    /// Called when the ray casting step size is changed
    void changeDvrRayCastingStep(double value);

    /// Called when the compositing type is changed
    void changeDvrRenderingMode(int id);

    /// Called when the shading type is changed
    void changeDvrShadingType(int id);

    /// Called when the (static) resolution dropdown menu changes
    void changeDvrStaticResolution(int id);

    /// Called when the type of transfer function is changed
    void changeDvrTransferFunctionType(int id);


    // --- TransferFunction editor --------------
    /// Reset the transfer functions
    void resetTF();

    /// Load a trasnfer function
    void loadTF();

    /// Store a transfer function
    void saveTF();

    /// Enable/Disable the logarithmic transfer function
    void logTF(bool enable);



    // ************************************************************************
    // *** Class members ******************************************************
private:
    // Data
    Volume m_volume;
    TransferFunction m_transferFunction;

    // OpenGL widgets
    GLCubeWidget *m_glCubeWidget;
    GLSlicerWidget *m_glSlicerWidget;
    GLDvrWidget *m_glDvrWidget;
    GLTFWidget *m_glTFWidget;

    // Dialog for editing the transfer function
    QDialog* m_tfEditorDlg;

    // Slicer GUI elements
    QSlider *m_slider_slice;
    QSlider *m_slider_contrast;
    QComboBox *m_combo_sliceAxis;

    // DVR GUI elements
    QComboBox *m_combo_dvrDynamicRes;
    QComboBox *m_combo_dvrGradientInterpolationMode;
    QComboBox *m_combo_dvrGradientMode;
    QComboBox *m_combo_dvrInterpolationMode;
    QComboBox *m_combo_dvrProjection;
    QComboBox *m_combo_dvrRenderingMode;
    QComboBox *m_combo_dvrShading;
    QComboBox *m_combo_dvrStaticRes;
    QComboBox *m_combo_dvrTfMode;
    QDoubleSpinBox *m_spinBox_dvrStepSize;



    // ************************************************************************
    // *** Private methods ****************************************************
private:
    void setupUi();
    QMenuBar* createMenus(QWidget *parent = nullptr);
    QWidget* createCubeTab(QWidget *parent = nullptr);
    QWidget* createSlicerTab(QWidget *parent = nullptr);
    QWidget* createDvrTab(QWidget *parent = nullptr);
    QDialog* createTFDialog(QWidget *parent = nullptr);

    void resetDvrTab();

}; /* class MainWindow */

#endif // MAINWINDOW_H


