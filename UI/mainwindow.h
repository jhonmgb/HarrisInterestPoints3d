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
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
private:
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
    QLineEdit * parameterSelection;

    QPushButton * renderButton;
    QPushButton * calculateInterestPoints;

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

public:

    // Constructor.
    explicit MainWindow(QWidget * parent = 0);
};

#endif // MAINWINDOW_H
