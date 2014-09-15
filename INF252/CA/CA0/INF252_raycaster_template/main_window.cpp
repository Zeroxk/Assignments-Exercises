#include "main_window.h"

#include "gl_cube_widget.h"
#include "gl_dvr_widget.h"
#include "gl_slicer_widget.h"
#include "gl_tf_widget.h"
#include <math.h>
#include <iostream>
#include <QAction>
#include <QApplication>
#include <QDialogButtonBox>
#include <QFileDialog>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QTextEdit>
#include <QDoubleSpinBox>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QSlider>
#include <QPushButton>
#include <QSpacerItem>
#include <QComboBox>
#include <QCheckBox>


// ****************************************************************************
// *** Basic Methods **********************************************************
// ****************************************************************************
// Default constructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Set the window size
    this->resize(800,600);
    this->setWindowTitle(tr("INF252 Assignments"));

    setupUi();
} /* constructor */


// Destructor
MainWindow::~MainWindow() {

} /* destructor */


// init()
void MainWindow::init() {

    m_glSlicerWidget->setVolume(&m_volume);
    // TODO (CA1): initialize any other parameter for the Slicer
    m_glSlicerWidget->setAxis(0);
    // TODO (CA1): set current and max values on m_slider_slice
    m_slider_slice->setMinimum(0);
    m_slider_slice->setMaximum(m_volume.getDepth()-1);

    this->resetDvrTab();
    m_glDvrWidget->setVolume(&m_volume);
    // TODO (CA2): initialize any other parameter for DVR

    updateContent();
} /* init() */


// ****************************************************************************
// *** Qt Slots ***************************************************************
// ****************************************************************************
// Load a dataset
void MainWindow::loadVolume() {
    std::cout << "loadVolume()" << std::endl;
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open Dataset"), "",
                tr("DataSet (*.dat);;All Files (*)"));
    if (!fileName.isEmpty()) {
        m_volume.loadVolumeDat(fileName.toStdString());
        this->init();
    }
}
// Open a dialog to edit a transfer function
void MainWindow::openTFEditor() {
    std::cout << "openTFEditor()" << std::endl;
    m_tfEditorDlg->setVisible(true);
}
// Update the content of the OpenGL widgets
void MainWindow::updateContent() {
    std::cout << "updateContent()" << std::endl;
    m_glSlicerWidget->updateContent();
    m_glDvrWidget->updateContent();
    m_glTFWidget->updateContent();
}

// --- Slicer Tab ---------------------------
// Change the current slicing axis
void MainWindow::changeSlicerAxis(int axis) {
    std::cout << "changeSlicerAxis(" << axis << ")"
              << std::endl;
    // TODO (CA1): set the new axis on the slicer widget
    m_glSlicerWidget->setAxis(axis);
    // TODO (CA1): reset m_slider_slice
    m_glSlicerWidget->setSlice(0);
    m_slider_slice->setValue(0);
    // TODO (CA1): set the maximum value for m_slider_slice
    int max = 0;
    switch(axis) {
    case 0: max = m_volume.getDepth(); break;
    case 1: max = m_volume.getWidth(); break;
    case 2: max = m_volume.getHeight(); break;
    }
    m_slider_slice->setMaximum(max-1);


    m_glSlicerWidget->updateContent();
}
// Change the currently displayed slice
void MainWindow::changeSlicerSlice(int slice) {
    std::cout << "changeSlicerSlice(" << slice << ")"
              << std::endl;
    // TODO (CA1): set the selected slice on the slicer widget
    m_glSlicerWidget->setSlice(slice);

    m_glSlicerWidget->updateContent();
}

// --- DVR Tab ------------------------------
// Called when the (static) resolution dropdown menu changes
void MainWindow::changeDvrStaticResolution(int id) {
    std::cout << "changeDvrResolution(" << id << ")"
              << std::endl;
    // TODO (CA3)
    m_glDvrWidget->updateContent();
}
// Called when the dynamic resolution dropdown menu changes
void MainWindow::changeDvrDynamicResolution(int id) {
    std::cout << "changeDvrDynamicResolution(" << id << ")"
              << std::endl;
    // TODO (CA3)
    m_glDvrWidget->updateContent();
}
// Called when the interpolation mode dropdown menu changes
void MainWindow::changeDvrInterpolationMode(int id) {
    std::cout << "changeInterpolationMode(" << id << ")"
              << std::endl;
    // TODO (CA3)
    m_glDvrWidget->updateContent();
}
// Called when the gradient interpolation mode dropdown menu changes
void MainWindow::changeDvrGradientInterpolationMode(int id) {
    std::cout << "changeGradientInterpolationMode(" << id << ")"
              << std::endl;
    // TODO (CA3)
    m_glDvrWidget->updateContent();
}
// Called when the gradient computation mode dropdown menu changes
void MainWindow::changeDvrGradientMode(int id) {
    std::cout << "changeGradientMode(" << id << ")"
              << std::endl;
    // TODO (CA3)
    m_glDvrWidget->updateContent();
}
// Called when the projection mode dropdown menu is changed
void MainWindow::changeDvrProjectionMode(int id) {
    std::cout << "changeProjectionMode(" << id << ")"
              << std::endl;
    // TODO (CA3)
    m_glDvrWidget->updateContent();
}
// Called when the compositing type is changed
void MainWindow::changeDvrRenderingMode(int id) {
    std::cout << "changeRenderingMode(" << id << ")"
              << std::endl;
    // TODO (CA3)
    m_glDvrWidget->updateContent();
}
// Called when the shading type is changed
void MainWindow::changeDvrShadingType(int id) {
    std::cout << "changeShadingType(" << id << ")"
              << std::endl;
    // TODO (CA3)
    m_glDvrWidget->updateContent();
}
// Called when the ray casting step size is changed
void MainWindow::changeDvrRayCastingStep(double value) {
    std::cout << "changeRayCastingStep(" << value << ")"
              << std::endl;
    // TODO (CA3)
    m_glDvrWidget->updateContent();
}
// Called when the type of transfer function is changed
void MainWindow::changeDvrTransferFunctionType(int id) {
    std::cout << "changeTransferFunctionType(" << id << ")"
              << std::endl;
    // TODO (CA3)
    m_glDvrWidget->updateContent();
}

// --- TransferFunction editor --------------
// Reset the transfer functions
void MainWindow::resetTF() {
    m_transferFunction.reset();
}
// Load a trasnfer function
void MainWindow::loadTF() {
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open Transfer Function"), "",
                tr("Transfer Function (*.tff);;All Files (*)"));
    if (!fileName.isEmpty()) {
        m_transferFunction.load(fileName.toStdString());
    }
}
// Store a transfer function
void MainWindow::saveTF() {
    QString fileName = QFileDialog::getSaveFileName(
                this, tr("Save transfer function"), "",
                tr("Transfer Function (*.tff);;All Files (*)"));
    if (!fileName.isEmpty()) {
        m_transferFunction.save(fileName.toStdString());
    }
}
// Enable/Disable the logarithmic transfer function
void MainWindow::logTF(bool enable) {
    std::cout << "logTF(" << enable << ")"
              << std::endl;
    // TODO (CA2&3) (optional)
}



// ****************************************************************************
// *** Methods to setup and handle the graphical user interface ***************
// ****************************************************************************
/// Setup the graphical user interface
void MainWindow::setupUi() {
    // Create the tab pane
    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->setTabPosition(QTabWidget::West);
    tabWidget->setTabShape(QTabWidget::Triangular);
    setCentralWidget(tabWidget);

    // Create the menus
    this->setMenuBar(createMenus(tabWidget));

    // Create the tabs
    tabWidget->addTab(createCubeTab(), tr("&Cube"));
    tabWidget->addTab(createSlicerTab(), tr("&Slicer"));
    tabWidget->addTab(createDvrTab(), tr("&DVR"));
    resetDvrTab();

    // Set the transfer function
    m_tfEditorDlg = createTFDialog();
    m_glSlicerWidget->setTransferFunction(&m_transferFunction);
    m_glDvrWidget->setTransferFunction(&m_transferFunction);

    // Every time the transfer function is changed, the content is updated
    connect(&m_transferFunction, SIGNAL(tfChanged()),
            this, SLOT(updateContent()));
} /* setupUi() */


/// Create the menus for the main window
QMenuBar* MainWindow::createMenus(QWidget *parent) {
    QMenuBar *menuBar = new QMenuBar(parent);

    QMenu* menuFile = new QMenu(tr("&File"), menuBar);
    menuBar->addAction(menuFile->menuAction());

    QAction* actionLoadDataset = new QAction(tr("&Load dataset"),menuFile);
    actionLoadDataset->setStatusTip(tr("Open Dataset"));
    connect(actionLoadDataset, SIGNAL(triggered()), this, SLOT(loadVolume()));
    menuFile->addAction(actionLoadDataset);

    return menuBar;
} /* createMenus() */


/// Add widgets to the cube tab
QWidget* MainWindow::createCubeTab(QWidget *parent) {
    // --- Create the cube tab ---
    QWidget* tabCube = new QWidget(parent);
    QHBoxLayout* layoutCube = new QHBoxLayout(tabCube);
    m_glCubeWidget = new GLCubeWidget(tabCube);
    layoutCube->addWidget(m_glCubeWidget);

    return tabCube;
}

/// Add widgets to the slicer tab
QWidget* MainWindow::createSlicerTab(QWidget *parent) {
    // --- Create the slicer tab ---
    QWidget* tabSlicer = new QWidget(parent);

    // Layout
    QHBoxLayout* layoutSlicer = new QHBoxLayout(tabSlicer);
    layoutSlicer->setObjectName(QString::fromUtf8("layoutSlicer"));

    // Split the tab in two using a splitter
    QSplitter* splitterSlicer = new QSplitter(tabSlicer);
    splitterSlicer->setObjectName(QString::fromUtf8("splitterSlicer"));
    splitterSlicer->setOrientation(Qt::Horizontal);
    layoutSlicer->addWidget(splitterSlicer); // Add the splitter to the tab


    // --- Setup a control panel on the left side of the slicer tab ---
    QWidget* widgetSlicerControl = new QWidget(splitterSlicer);
    widgetSlicerControl->setObjectName(QString::fromUtf8("widgetSlicerControl"));
    widgetSlicerControl->setMaximumWidth(200);
    splitterSlicer->addWidget(widgetSlicerControl);

    // layout
    QVBoxLayout* layoutSlicerControl = new QVBoxLayout(widgetSlicerControl);
    layoutSlicerControl->setObjectName(QString::fromUtf8("layoutSlicerControl"));

    // first label
    QLabel* label1_Slicer = new QLabel(widgetSlicerControl);
    label1_Slicer->setText(QApplication::translate("MainWindowClass", "Slicing through axis", 0, QApplication::UnicodeUTF8));
    layoutSlicerControl->addWidget(label1_Slicer);

    // the combobox
    m_combo_sliceAxis = new QComboBox(widgetSlicerControl);
    m_combo_sliceAxis->addItem(tr("x"));
    m_combo_sliceAxis->addItem(tr("y"));
    m_combo_sliceAxis->addItem(tr("z"));
    layoutSlicerControl->addWidget(m_combo_sliceAxis);

    // the vspacer
    QSpacerItem* spacer1_Slicer = new QSpacerItem(20, 480, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layoutSlicerControl->addItem(spacer1_Slicer);

    // the slider
    m_slider_slice = new QSlider(widgetSlicerControl);
    m_slider_slice->setObjectName(QString::fromUtf8("hSlider_Slicer"));
    m_slider_slice->setOrientation(Qt::Horizontal);
    m_slider_slice->setRange(0,0);
    layoutSlicerControl->addWidget(m_slider_slice);

    // the pushbutton
    QPushButton *push_slicerTf = new QPushButton(widgetSlicerControl);
    push_slicerTf->setObjectName(QString::fromUtf8("push_slicerTf"));
    push_slicerTf->setText(QApplication::translate("MainWindowClass", "TransferFunction Editor", 0, QApplication::UnicodeUTF8));
    layoutSlicerControl->addWidget(push_slicerTf);

    // --- Setup an OpenGL widget on the right side of the slicer tab ---
    m_glSlicerWidget = new GLSlicerWidget(splitterSlicer);
    splitterSlicer->addWidget(m_glSlicerWidget);

    // --- Establish all the connections from this tab ---
    connect(push_slicerTf, SIGNAL(clicked()),this, SLOT(openTFEditor()));
    connect(m_slider_slice, SIGNAL(valueChanged(int)), this, SLOT(changeSlicerSlice(int)));
    connect(m_combo_sliceAxis, SIGNAL(activated(int)), this, SLOT(changeSlicerAxis(int)));

    return tabSlicer;
} /* createSlicerTab() */


/// Add widgets to the dvr tab
QWidget* MainWindow::createDvrTab(QWidget *parent) {
    // --- Create the dvr tab ---
    QWidget *tabVolumeRendering = new QWidget(parent);
    tabVolumeRendering->setObjectName(QString::fromUtf8("tabVolumeRendering"));

    // Layout
    QHBoxLayout *layoutDvr = new QHBoxLayout(tabVolumeRendering);
    layoutDvr->setObjectName(QString::fromUtf8("layoutDvr"));

    // Split the tab in two using a splitter
    QSplitter* splitterDvr = new QSplitter(tabVolumeRendering);
    splitterDvr->setObjectName(QString::fromUtf8("splitterDvr"));
    splitterDvr->setOrientation(Qt::Horizontal);
    layoutDvr->addWidget(splitterDvr);

    // --- Setup a control panel on the left side of the dvr tab ---
    QWidget* widgetDvrControl = new QWidget(splitterDvr);
    widgetDvrControl->setObjectName(QString::fromUtf8("widgetDvrControl"));
    widgetDvrControl->setMaximumWidth(200);
    splitterDvr->addWidget(widgetDvrControl);

    // layout
    QVBoxLayout* layoutDvrControl = new QVBoxLayout(widgetDvrControl);
    layoutDvrControl->setObjectName(QString::fromUtf8("layoutDvrControl"));

    // all the other widgets
    QLabel *label1_Dvr = new QLabel(widgetDvrControl);
    label1_Dvr->setObjectName(QString::fromUtf8("label1_Dvr"));
    label1_Dvr->setText(QApplication::translate("MainWindowClass", "Interpolation method", 0, QApplication::UnicodeUTF8));
    layoutDvrControl->addWidget(label1_Dvr);

    m_combo_dvrInterpolationMode = new QComboBox(widgetDvrControl);
    m_combo_dvrInterpolationMode->setObjectName(QString::fromUtf8("combo_dvrInterpolationMethod"));
    m_combo_dvrInterpolationMode->addItem(tr("Data - Nearest"));
    m_combo_dvrInterpolationMode->addItem(tr("Data - Trilinear"));
    layoutDvrControl->addWidget(m_combo_dvrInterpolationMode);

    m_combo_dvrGradientInterpolationMode = new QComboBox(widgetDvrControl);
    m_combo_dvrGradientInterpolationMode->setObjectName(QString::fromUtf8("combo_dvrGradientInterpolationMethod"));
    m_combo_dvrGradientInterpolationMode->addItem(tr("Gradient - Nearest"));
    m_combo_dvrGradientInterpolationMode->addItem(tr("Gradient - Trilinear"));
    layoutDvrControl->addWidget(m_combo_dvrGradientInterpolationMode);

    QLabel *label2_Dvr = new QLabel(widgetDvrControl);
    label2_Dvr->setObjectName(QString::fromUtf8("label2_Dvr"));
    label2_Dvr->setText(QApplication::translate("MainWindowClass", "Gradient Computation Method", 0, QApplication::UnicodeUTF8));
    layoutDvrControl->addWidget(label2_Dvr);

    m_combo_dvrGradientMode = new QComboBox(widgetDvrControl);
    m_combo_dvrGradientMode->setObjectName(QString::fromUtf8("combo_dvrGradientMethod"));
    m_combo_dvrGradientMode->addItem(tr("Central Diff."));
    m_combo_dvrGradientMode->addItem(tr("Forward Diff."));
    m_combo_dvrGradientMode->addItem(tr("Backward Diff."));
    layoutDvrControl->addWidget(m_combo_dvrGradientMode);

    QLabel* label3_Dvr = new QLabel(widgetDvrControl);
    label3_Dvr->setObjectName(QString::fromUtf8("label3_Dvr"));
    label3_Dvr->setText(QApplication::translate("MainWindowClass", "Viewing projection", 0, QApplication::UnicodeUTF8));
    layoutDvrControl->addWidget(label3_Dvr);

    m_combo_dvrProjection = new QComboBox(widgetDvrControl);
    m_combo_dvrProjection->setObjectName(QString::fromUtf8("combo_dvrProjection"));
    m_combo_dvrProjection->addItem(tr("Parallel"));
    m_combo_dvrProjection->addItem(tr("Perspective"));
    layoutDvrControl->addWidget(m_combo_dvrProjection);

    QLabel* label4_Dvr = new QLabel(widgetDvrControl);
    label4_Dvr->setObjectName(QString::fromUtf8("label4_Dvr"));
    label4_Dvr->setText(QApplication::translate("MainWindowClass", "Shading", 0, QApplication::UnicodeUTF8));
    layoutDvrControl->addWidget(label4_Dvr);

    m_combo_dvrShading = new QComboBox(widgetDvrControl);
    m_combo_dvrShading->setObjectName(QString::fromUtf8("combo_dvrShading"));
    m_combo_dvrShading->addItem(tr("None"));
    m_combo_dvrShading->addItem(tr("Phong"));
    layoutDvrControl->addWidget(m_combo_dvrShading);

    QLabel* label5_Dvr = new QLabel(widgetDvrControl);
    label5_Dvr->setObjectName(QString::fromUtf8("label5_Dvr"));
    label5_Dvr->setText(QApplication::translate("MainWindowClass", "Rendering method", 0, QApplication::UnicodeUTF8));
    layoutDvrControl->addWidget(label5_Dvr);

    m_combo_dvrRenderingMode = new QComboBox(widgetDvrControl);
    m_combo_dvrRenderingMode->setObjectName(QString::fromUtf8("combo_dvrRenderingMethod"));
    m_combo_dvrRenderingMode->addItem(tr("DVR"));
    m_combo_dvrRenderingMode->addItem(tr("Maximum Intensity"));
    m_combo_dvrRenderingMode->addItem(tr("BB Entry Point"));
    m_combo_dvrRenderingMode->addItem(tr("First Hit"));
    m_combo_dvrRenderingMode->addItem(tr("Average"));
    layoutDvrControl->addWidget(m_combo_dvrRenderingMode);

    QLabel* label7_Dvr = new QLabel(widgetDvrControl);
    label7_Dvr->setObjectName(QString::fromUtf8("label7_Dvr"));
    label7_Dvr->setText(QApplication::translate("MainWindowClass", "Rendering resolution", 0, QApplication::UnicodeUTF8));
    layoutDvrControl->addWidget(label7_Dvr);

    m_combo_dvrStaticRes = new QComboBox(widgetDvrControl);
    m_combo_dvrStaticRes->setObjectName(QString::fromUtf8("combo_dvrRes"));
    m_combo_dvrStaticRes->addItem(tr("64x64"));
    m_combo_dvrStaticRes->addItem(tr("128x128"));
    m_combo_dvrStaticRes->addItem(tr("256x256"));
    m_combo_dvrStaticRes->addItem(tr("512x512"));
    m_combo_dvrStaticRes->addItem(tr("1024x1024"));
    layoutDvrControl->addWidget(m_combo_dvrStaticRes);

    QLabel* label8_Dvr = new QLabel(widgetDvrControl);
    label8_Dvr->setObjectName(QString::fromUtf8("label8_Dvr"));
    label8_Dvr->setText(QApplication::translate("MainWindowClass", "Moving resolution", 0, QApplication::UnicodeUTF8));
    layoutDvrControl->addWidget(label8_Dvr);

    m_combo_dvrDynamicRes = new QComboBox(widgetDvrControl);
    m_combo_dvrDynamicRes->setObjectName(QString::fromUtf8("combo_dvrResRotating"));
    m_combo_dvrDynamicRes->addItem(tr("16x16"));
    m_combo_dvrDynamicRes->addItem(tr("32x32"));
    m_combo_dvrDynamicRes->addItem(tr("64x64"));
    m_combo_dvrDynamicRes->addItem(tr("128x128"));
    m_combo_dvrDynamicRes->addItem(tr("256x256"));
    m_combo_dvrDynamicRes->addItem(tr("512x512"));
    layoutDvrControl->addWidget(m_combo_dvrDynamicRes);

    QLabel* label9_Dvr = new QLabel(widgetDvrControl);
    label9_Dvr->setObjectName(QString::fromUtf8("label9_Dvr"));
    label9_Dvr->setText(QApplication::translate("MainWindowClass", "Transfer Function", 0, QApplication::UnicodeUTF8));
    layoutDvrControl->addWidget(label9_Dvr);

    m_combo_dvrTfMode = new QComboBox(widgetDvrControl);
    m_combo_dvrTfMode->setObjectName(QString::fromUtf8("combo_dvrTfMode"));
    m_combo_dvrTfMode->addItem(tr("1D Transfer Function"));
    m_combo_dvrTfMode->addItem(tr("Gradient-Based k=1 p=1"));
    m_combo_dvrTfMode->addItem(tr("Gradient-Based k=0.1 p=1"));
    m_combo_dvrTfMode->addItem(tr("Gradient-Based k=1 p=10"));
    m_combo_dvrTfMode->addItem(tr("Gradient-Based k=0.1 p=10"));
    layoutDvrControl->addWidget(m_combo_dvrTfMode);

    QLabel* label6_Dvr = new QLabel(widgetDvrControl);
    label6_Dvr->setObjectName(QString::fromUtf8("label6_Dvr"));
    label6_Dvr->setText(QApplication::translate("MainWindowClass", "Step size", 0, QApplication::UnicodeUTF8));
    layoutDvrControl->addWidget(label6_Dvr);

    m_spinBox_dvrStepSize = new QDoubleSpinBox(widgetDvrControl);
    m_spinBox_dvrStepSize->setObjectName(QString::fromUtf8("spinBox_dvrStepSize"));
    m_spinBox_dvrStepSize->setRange(0.25,5.0);
    m_spinBox_dvrStepSize->setSingleStep(0.05);
    layoutDvrControl->addWidget(m_spinBox_dvrStepSize);

    QSpacerItem* spacer2_Dvr = new QSpacerItem(20, 110, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layoutDvrControl->addItem(spacer2_Dvr);

    QPushButton* push_dvrTf = new QPushButton(widgetDvrControl);
    push_dvrTf->setObjectName(QString::fromUtf8("push_dvrTf"));
    push_dvrTf->setText(QApplication::translate("MainWindowClass", "TransferFunction editor", 0, QApplication::UnicodeUTF8));
    layoutDvrControl->addWidget(push_dvrTf);

    // --- Setup an OpenGL widget on the right side of the slicer tab ---
    m_glDvrWidget = new GLDvrWidget(splitterDvr);
    splitterDvr->addWidget(m_glDvrWidget);

    // --- Establish all the connections from this tab ---
    connect(m_combo_dvrDynamicRes, SIGNAL(activated(int)), this, SLOT(changeDvrDynamicResolution(int)));
    connect(m_combo_dvrGradientInterpolationMode, SIGNAL(activated(int)), this, SLOT(changeDvrGradientInterpolationMode(int)));
    connect(m_combo_dvrGradientMode, SIGNAL(activated(int)), this, SLOT(changeDvrGradientMode(int)));
    connect(m_combo_dvrInterpolationMode, SIGNAL(activated(int)), this, SLOT(changeDvrInterpolationMode(int)));
    connect(m_combo_dvrProjection, SIGNAL(activated(int)), this, SLOT(changeDvrProjectionMode(int)));
    connect(m_combo_dvrRenderingMode, SIGNAL(activated(int)), this, SLOT(changeDvrRenderingMode(int)));
    connect(m_combo_dvrShading, SIGNAL(activated(int)), this, SLOT(changeDvrShadingType(int)));
    connect(m_combo_dvrStaticRes, SIGNAL(activated(int)), this, SLOT(changeDvrStaticResolution(int)));
    connect(m_combo_dvrTfMode, SIGNAL(activated(int)), this, SLOT(changeDvrTransferFunctionType(int)));
    connect(m_spinBox_dvrStepSize, SIGNAL(valueChanged(double)), this, SLOT(changeDvrRayCastingStep(double)));
    connect(push_dvrTf, SIGNAL(clicked()),this, SLOT(openTFEditor()));

    return tabVolumeRendering;
} /* createDvrTab() */

// Create the transfer function dialog
QDialog* MainWindow::createTFDialog(QWidget *parent) {
    QDialog* tfDialog = new QDialog(parent);
    tfDialog->setWindowTitle(tr("Transfer Function editor"));

    QVBoxLayout* layout = new QVBoxLayout(tfDialog);
    tfDialog->setLayout(layout);

    QCheckBox* ckLogarithmic = new QCheckBox(tr("&Logaritmic Scale"));
    layout->addWidget(ckLogarithmic);

    QDialogButtonBox* btsBox = new QDialogButtonBox(Qt::Horizontal, tfDialog);
    QPushButton* btOpen = new QPushButton(tr("&Open"), btsBox);
    QPushButton* btSave = new QPushButton(tr("&Save"), btsBox);
    QPushButton* btReset = new QPushButton(tr("&Reset"), btsBox);
    btsBox->addButton(btOpen, QDialogButtonBox::AcceptRole);
    btsBox->addButton(btSave, QDialogButtonBox::ActionRole);
    btsBox->addButton(btReset,QDialogButtonBox::ActionRole);
    layout->addWidget(btsBox);

    // Create the OpenGL editor widget
    m_glTFWidget = new GLTFWidget(tfDialog);
    layout->addWidget(m_glTFWidget);

    tfDialog->resize(450, 220);
    tfDialog->setVisible(false);

    // --- Establish all the connections from this dialog ---
    connect(ckLogarithmic, SIGNAL(toggled(bool)), this, SLOT(logTF(bool)));
    connect(btReset, SIGNAL(clicked()),this, SLOT(resetTF()));
    connect(btOpen, SIGNAL(clicked()),this, SLOT(loadTF()));
    connect(btSave, SIGNAL(clicked()),this, SLOT(saveTF()));

    return tfDialog;
} /* createTFDialog() */


// Reset the dvr options to the default settings
void MainWindow::resetDvrTab() {
    m_combo_dvrStaticRes->setCurrentIndex(0);
    m_combo_dvrDynamicRes->setCurrentIndex(0);
    m_combo_dvrInterpolationMode->setCurrentIndex(0);
    m_combo_dvrGradientMode->setCurrentIndex(0);
    m_combo_dvrGradientInterpolationMode->setCurrentIndex(0);
    m_combo_dvrProjection->setCurrentIndex(0);
    m_combo_dvrShading->setCurrentIndex(0);
    m_combo_dvrRenderingMode->setCurrentIndex(0);
    m_combo_dvrTfMode->setCurrentIndex(0);
    m_spinBox_dvrStepSize->setValue(0.7);
}
