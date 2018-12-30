#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QComboBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>

#include "Communicator/communicator.h"
#include "Render/openglwidget.h"

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
private:
    QString * file1;
    QString * file2;
    QGroupBox * loadFilesPanel;
    QGroupBox * propertiesPanel;
    QGroupBox * oglContainer;
    QGridLayout * buttonsPanel;

    QRadioButton * off;
    QRadioButton * triVert;
    QPushButton * openFile1;
    QPushButton * openFile2;
    QLabel * labelFile1;
    QLabel * labelFile2;
    QLineEdit * path1;
    QLineEdit * path2;
    QLineEdit * harrisParam;
    QLineEdit * rings;
    QComboBox * selectionMode;
    QLineEdit * percentageOfPoints;

    QPushButton * loadMeshButton;
    QPushButton * calculateInterestPoints;

    Communicator * communicator;
    OpenGLWidget * render;
    MeshType meshType;

    /**
     * @brief initializeLoadFilesPanel Initialize the panel with the UI
     *      components for loading the mesh files.
     */
    void initializeLoadFilesPanel();

    /**
     * @brief initializePropertiesPanel Initialize the panel with the UI
     *      components with the properties for calculating the interest points.
     */
    void initializePropertiesPanel();

    /**
     * @brief initializeOglPanel Initialize the panel with the OpenGL widget.
     */
    void initializeOglPanel();

private slots:

    /**
     * @brief updateFilesPanel updates loadFilesPanel according to the kind
     *      mesh files to load.
     * @param button a pointer to the QRadioButton choosed.
     */
    void updateFilesPanel(QAbstractButton * button);

    /**
     * @brief loadFile opens a QFileDialog for choosing a file.
     * @param origin the button origin of the event.
     */
    void loadFile(QAbstractButton * origin);

    /**
     * @brief loadMesh loads the mesh into the Communicator, ready for process,
     *  and render the mesh in to the OpenGL widget.
     */
    void loadMesh();

    /**
     * @brief loadInterestPoints read the parameters defined by the user and
     *  send a request to the communicator to calculate the interest points
     *  of the loaded mesh.
     */
    void loadInterestPoints();

    /**
     * @brief validateInput Validate the input parameters prior the interest
     *  points calculation.
     * @param rings the number of ring to consider during the interest
     *  points calculation.
     * @param k the harris param.
     * @param percentage the percentage of interest points to select.
     * @param isOk flag that indicates wheter the input fields has been filled
     *  with numbers.
     */
    void validateInput(int rings, double k, double percentage, bool isOk);
public:

    // Constructor.
    explicit MainWindow(Communicator * communicator, QWidget * parent = 0);
};

#endif // MAINWINDOW_H
