#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "BasicStructures/mesh.h"
#include "mesh.h"
#include <QFile>

class FileManager
{
public:
    /**
     * @brief FileManager Constructor for FileManager
     */
    FileManager();

    /**
     * @brief readOFF Read an OFF file
     * @param offFile Pointer to QFile for the OFF file selected from the GUI
     * @return A pointer to an object of the Mesh class containing read faces and vertexes
     */
    Mesh * readOFF(QFile * offFile);

    /**
     * @brief readTriVert Read Tri and Vert files
     * @param triFile Poitner to QFile specifying the TRI file selected from the GUI
     * @param vertFile Pointer to QFile specifying the VERT file selected from the GUI
     * @return A pointer to an object of the Mesh class containing faces and vertexes
     */
    Mesh * readTriVert(QFile * triFile, QFile * vertFile);
};

#endif // FILEMANAGER_H
