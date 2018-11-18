#include "UI/mainwindow.h"

// Constructor.
MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent)
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

    QWidget * mainWidget = new QWidget(this);
    hboxLayout->addWidget(widget);
    hboxLayout->addWidget(oglContainer);
    mainWidget->setLayout(hboxLayout);

    setCentralWidget(mainWidget);
}

/**
 * @brief initializeLoadFilesPanel Initialize the panel with the UI
 *      components for loading the mesh files.
 */
void MainWindow::initializeLoadFilesPanel()
{
    off = new QRadioButton(".off");
    triVert = new QRadioButton(".tri .vert");
    triVert->setChecked(true);
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

    renderButton = new QPushButton(QString("Renderize"));
    gridLayout->addWidget(renderButton, 3, 0, 1, 3);

    loadFilesPanel = new QGroupBox();
    loadFilesPanel->setLayout(gridLayout);
    loadFilesPanel->setTitle(QString("Load files"));

    connect(
        group,
        static_cast<void (QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
        this, &MainWindow::updateFilesPanel);

    connect(
        openFile1, &QPushButton::clicked,
        this, [=](){ this->loadFile(openFile1); });

    connect(
        openFile2, &QPushButton::clicked,
        this, [=](){ this->loadFile(openFile2); });
}

/**
 * @brief initializePropertiesPanel Initialize the panel with the UI
 *      components with the properties for calculating the interest points.
 */
void MainWindow::initializePropertiesPanel()
{
    propertiesPanel = new QGroupBox();
    harrisParam = new QLineEdit();
    rings = new QLineEdit();
    selectionMode = new QComboBox(this);
    selectionMode->addItem(QString("Fraction"));
    parameterSelection = new QLineEdit();

    QFormLayout * layout = new QFormLayout();
    layout->addRow(new QLabel("Harris Param K"), harrisParam);
    layout->addRow(new QLabel("Rings"), rings);
    layout->addRow(new QLabel("Selection mode"), selectionMode);
    layout->addRow(new QLabel("Parameter selection"), parameterSelection);

    calculateInterestPoints = new QPushButton(QString("Calculate interest points"));
    layout->addRow(calculateInterestPoints);

    propertiesPanel->setLayout(layout);
}

/**
 * @brief updateFilesPanel updates loadFilesPanel according to the kind
 *      mesh files to load.
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
    }
    else if (button == triVert)
    {
        labelFile1->setText(QString("Tri"));
        path1->clear();
        path2->clear();
        labelFile2->show();
        openFile2->show();
        path2->show();
    }
}

/**
 * @brief loadFile opens a QFileDialog for choosing a file.
 * @param origin the button origin of the event.
 */
void MainWindow::loadFile(QAbstractButton * origin)
{
    bool isOff = (off->isChecked());
    QString title;
    QString filter;
    QLineEdit * lineEdit = 0;

    if (origin == openFile1)
    {
        title = QString((isOff)? "Choose an OFF file" : "Choose a .tri file");
        filter = QString((isOff)? "OFF (*.off)" : "TRI (*.tri)");
        lineEdit = path1;
    }
    else if (origin == openFile2)
    {
        title = QString("Choose a .vert file");
        filter = QString("VERT (*.vert)");
        lineEdit = path2;
    }

    QString fileName = QFileDialog::getOpenFileName(this, title, ".", filter);
    lineEdit->setText(fileName);
}

/**
 * @brief initializeOglPanel Initialize the panel with the OpenGL widget.
 */
void MainWindow::initializeOglPanel()
{
    oglContainer = new QGroupBox();
    oglContainer->setMinimumSize(QSize(500, 500));
    oglContainer->setTitle(QString("Render"));
}
