#include "UI/mainwindow.h"
#include "Communicator/exception.h"
#include "Render/openglwidget.h"

// Constructor.
MainWindow::MainWindow(Communicator * communicator, QWidget * parent) : QMainWindow(parent)
{
    QHBoxLayout * hboxLayout = new QHBoxLayout();

    initializeLoadFilesPanel();
    initializePropertiesPanel();
    initializeOglPanel();

    buttonsPanel = new QGridLayout();
    buttonsPanel->addWidget(loadFilesPanel);
    buttonsPanel->addWidget(propertiesPanel);

    QWidget* widget = new QWidget(this);
    widget->setLayout(buttonsPanel);
    widget->setMaximumWidth(300);

    QWidget * mainWidget = new QWidget(this);
    hboxLayout->addWidget(widget);
    hboxLayout->addWidget(oglContainer);
    mainWidget->setLayout(hboxLayout);

    setCentralWidget(mainWidget);

    file1 = new QString();
    file2 = new QString();

    this->communicator = communicator;
}

/**
 * @brief MainWindow::initializeLoadFilesPanel Initialize the panel with the UI
 *  components for loading the mesh files.
 */
void MainWindow::initializeLoadFilesPanel()
{
    off = new QRadioButton(".off");
    triVert = new QRadioButton(".tri .vert");
    triVert->setChecked(true);

    meshType = MeshType::TRIVERT;

    QButtonGroup * group = new QButtonGroup();
    group->addButton(off, 0);
    group->addButton(triVert, 1);

    labelFile1 = new QLabel("Tri");
    labelFile2 = new QLabel("Vert");
    openFile1 = new QPushButton("...");
    openFile2 = new QPushButton("...");

    path1 = new QLineEdit();
    path1->setReadOnly(true);

    path2 = new QLineEdit();
    path2->setReadOnly(true);

    QGridLayout * gridLayout = new QGridLayout();
    gridLayout->addWidget(off, 0,0);
    gridLayout->addWidget(triVert, 0, 1);
    gridLayout->addWidget(labelFile1, 1, 0);
    gridLayout->addWidget(path1, 1, 1);
    gridLayout->addWidget(openFile1, 1, 2);
    gridLayout->addWidget(labelFile2, 2, 0);
    gridLayout->addWidget(path2, 2, 1);
    gridLayout->addWidget(openFile2, 2, 2);

    loadMeshButton = new QPushButton(QString("Load Mesh"));
    gridLayout->addWidget(loadMeshButton, 3, 0, 1, 3);

    loadFilesPanel = new QGroupBox();
    loadFilesPanel->setLayout(gridLayout);
    loadFilesPanel->setTitle(QString("Load files"));

    connect(
        group,
        static_cast<void (QButtonGroup::*)(QAbstractButton *)>(
            &QButtonGroup::buttonClicked),
        this, &MainWindow::updateFilesPanel);

    connect(
        openFile1, &QPushButton::clicked,
        this, [=](){ this->loadFile(openFile1); });

    connect(
        openFile2, &QPushButton::clicked,
        this, [=](){ this->loadFile(openFile2); });

    connect(loadMeshButton, &QPushButton::clicked,this, &MainWindow::loadMesh);
}

/**
 * @brief MainWindow::initializePropertiesPanel Initialize the panel with the UI
 *  components with the properties for calculating the interest points.
 */
void MainWindow::initializePropertiesPanel()
{
    propertiesPanel = new QGroupBox();
    harrisParam = new QLineEdit();
    rings = new QLineEdit();
    selectionMode = new QComboBox(this);
    selectionMode->addItem(QString("Fraction"));
    selectionMode->addItem(QString("Clustering"));
    percentageOfPoints = new QLineEdit();

    QFormLayout * layout = new QFormLayout();
    layout->addRow(new QLabel("Harris Param K"), harrisParam);
    layout->addRow(new QLabel("Rings"), rings);
    layout->addRow(new QLabel("Percentage of points"), percentageOfPoints);
    layout->addRow(new QLabel("Selection mode"), selectionMode);

    // Setting default values.

    harrisParam->setText(QString("0.2"));
    rings->setText(QString("3"));
    percentageOfPoints->setText("0.5");

    QDoubleValidator * validator
        = new QDoubleValidator(0, 100, 3, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    harrisParam->setValidator(validator);
    rings->setValidator( new QIntValidator(0, 200, this) );
    QDoubleValidator * validatorPercentage =
        new QDoubleValidator(0, 100, 3, this);
    validatorPercentage->setNotation(QDoubleValidator::StandardNotation);
    validatorPercentage->setDecimals(3);
    percentageOfPoints->setValidator(validatorPercentage);

    calculateInterestPoints =
        new QPushButton(QString("Calculate interest points"));
    layout->addRow(calculateInterestPoints);

    propertiesPanel->setLayout(layout);

    connect(
        calculateInterestPoints,
        &QPushButton::clicked,
        this,
        &MainWindow::loadInterestPoints);
}

/**
 * @brief MainWindow::updateFilesPanel updates loadFilesPanel according to
 *  the kind mesh files to load.
 * @param button a pointer to the QRadioButton choosed.
 */
void MainWindow::updateFilesPanel(QAbstractButton * button)
{
    if (button == off)
    {
        labelFile1->setText(QString("Off"));
        path1->clear();
        labelFile2->hide();
        openFile2->hide();
        path2->hide();
        meshType = MeshType::OFF;
    }
    else if (button == triVert)
    {
        labelFile1->setText(QString("Tri"));
        path1->clear();
        path2->clear();
        labelFile2->show();
        openFile2->show();
        path2->show();
        meshType = MeshType::TRIVERT;
    }
}

/**
 * @brief MainWindow::loadFile opens a QFileDialog for choosing a file.
 * @param origin the button origin of the event.
 */
void MainWindow::loadFile(QAbstractButton * origin)
{
    bool isOff = (off->isChecked());
    QString title;
    QString filter;
    QLineEdit * lineEdit = 0;
    QString ** filePath;

    if (origin == openFile1)
    {
        title = QString((isOff)? "Choose an OFF file" : "Choose a .tri file");
        filter = QString((isOff)? "OFF (*.off)" : "TRI (*.tri)");
        lineEdit = path1;
        filePath = &file1;

    }
    else if (origin == openFile2)
    {
        title = QString("Choose a .vert file");
        filter = QString("VERT (*.vert)");
        lineEdit = path2;
        filePath = &file2;
    }

    QString fileName = QFileDialog::getOpenFileName(this, title, ".", filter);

    if (! fileName.isEmpty())
    {
        *filePath = new QString(fileName);
        lineEdit->setText(fileName);
    }
}

/**
 * @brief MainWindow::initializeOglPanel Initialize the panel with the OpenGL
 *  widget.
 */
void MainWindow::initializeOglPanel()
{
    render = new OpenGLWidget;
    oglContainer = new QGroupBox();
    oglContainer->setMinimumSize(QSize(500, 500));
    oglContainer->setTitle(QString("Render"));
    QGridLayout * gridLayout = new QGridLayout(oglContainer);
    gridLayout->addWidget(render);
    oglContainer->setLayout(gridLayout);
}

/**
 * @brief MainWindow::loadMesh loads the mesh into the Communicator, ready for
 *  process, and render the mesh in to the OpenGL widget.
 */
void MainWindow::loadMesh()
{
    bool errorState = file1->isEmpty() || file1->isNull();

    if (meshType == MeshType::TRIVERT)
    {
        errorState = errorState || file2->isEmpty() || file2->isNull();
    }

    if (errorState)
    {
        QString message = "Please choose the files to build the mesh";
        QMessageBox::warning(this, QString("Warning"), message);
        return;
    }
    try
    {
        communicator->loadMesh(meshType, *file1, *file2);
    }
    catch (Exception & e)
    {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    catch (exception & e)
    {
        QMessageBox::critical(this, "Critical Error", e.what());
        return;
    }
    render->drawMesh(communicator->getMesh());
}

/**
 * @brief MainWindow::loadInterestPoints read the parameters defined by the
 *  user and send a request to the communicator to calculate the interest points
 *  of the loaded mesh.
 */
void MainWindow::loadInterestPoints()
{
    bool conversionOk = false;
    vector<Vertex *> * intPoints;
    try
    {
        int numRings = rings->text().toInt(&conversionOk);
        double k = harrisParam->text().toDouble(&conversionOk);
        double percentageOfPoints =
            this->percentageOfPoints->text().toDouble(&conversionOk);

        validateInput(numRings, k, percentageOfPoints, conversionOk);
        QString selectionMode = this->selectionMode->currentText();

        intPoints =
            communicator->retrieveInterestPoints(
                numRings, k, percentageOfPoints, selectionMode);
        render->reallocateBufferWithInteresPoints(intPoints);
    }
    catch (Exception & e)
    {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    catch (exception & e)
    {
        QMessageBox::critical(this, "Critical Error", e.what());
        return;
    }
}

/**
 * @brief MainWindow::validateInput Validate the input parameters prior the
 *  interest points calculation.
 * @param rings the number of ring to consider during the interest
 *  points calculation.
 * @param k the harris param.
 * @param percentage the percentage of interest points to select
 * @param isOk flag that indicates wheter the input fields has been filled
 *  with numbers.
 */
void MainWindow::validateInput(
    int rings, double k, double percentage, bool isOk)
{
    if (!isOk)
    {
        throw Exception(
            ExceptionType::VALIDATION_ERROR,
            "At least one of the input parameters is empty.");
    }
    else if (rings <= 1 || rings > 100)
    {
        throw Exception(
            ExceptionType::VALIDATION_ERROR,
            "The number of rings should be between 2 and 100");
    }
    else if (percentage <= 0 || percentage > 100)
    {
        throw Exception(
            ExceptionType::VALIDATION_ERROR,
            "The percentage of interest points to select should be greater than 0 and lower or equals to 100");
    }
    else if (k <= 0 || k > 0.4)
    {
        throw Exception(
            ExceptionType::VALIDATION_ERROR,
            "The harris parameter should be a decimal number greater than 0 and lower or equals than 0.4");
    }
}
