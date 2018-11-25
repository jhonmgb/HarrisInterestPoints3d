#include "filemanager.h"

/**
 * @brief FileManager Constructor for FileManager
 */
FileManager::FileManager()
{
}

/**
 * @brief readOFF Read an OFF file
 * @param offFile Pointer to QFile for the OFF file selected from the GUI
 * @return A pointer to an object of the Mesh class containing read faces and vertexes
 */
Mesh * FileManager::readOFF(QFile * offFile)
{
    //Get string names of the files
    QString offFileName = offFile->fileName();
    string offFileNameString = offFileName.toStdString();
    string line;
    string fileFormat = offFileNameString.substr(offFileNameString.length() - 3, 3);

    int numPoints(0);
    int numFaces(0);
    int numElementsPerFace(0);

    if(fileFormat == "off")
    {
        //First, get number of vertexes and number of faces
        unsigned int delimiterPos_1(0), delimiterPos_2(0), delimiterPos_3(0);
        ifstream myfile (offFileNameString);
        if (myfile.is_open())
        {
          getline(myfile,line); //Get first line
          if(line=="OFF") //If first line is OFF, then it is an off file
          {
              getline(myfile, line); //Second line contains    NumberOfPoints  NumberOfFaces  NumberOfEdges

              //This part was modified from https://bytes.com/topic/c/answers/133131-reading-file-off-format:
              delimiterPos_1 = line.find(" ", 0); //Find first blank space
              numPoints = atoi(line.substr(0,delimiterPos_1).c_str()); //Convert first number to integer
              delimiterPos_2 = line.find(" ", delimiterPos_1+1); //Find second blank space
              numFaces = atoi(line.substr(delimiterPos_1+1,delimiterPos_2-(delimiterPos_1+1)).c_str());
           }else
           {
              return NULL;
           }

          //Now read values of points and faces and put them in a mesh
          Mesh * surface = new Mesh();

          //Now read points
          double x(0), y(0), z(0);
          for(int iPoint = 0; iPoint < numPoints; iPoint++)
          {
              getline(myfile, line);
              delimiterPos_1 = line.find(" ", 0);
              x = atof(line.substr(0,delimiterPos_1).c_str());
              delimiterPos_2 = line.find(" ", delimiterPos_1+1);
              y = atof(line.substr(delimiterPos_1+1,delimiterPos_2 - (delimiterPos_1 + 1)).c_str());
              z = atof(line.substr(delimiterPos_2+1).c_str());

              Vertex  * pointVertex = new Vertex;
              pointVertex->setCoordinates(double(x),double(y),double(z));
              pointVertex->setIndex(iPoint);
              surface->addNewVertex(pointVertex);

          }

          //Read faces of the surface
          int f0(0), f1(0), f2(0);
          for(int iFace=0; iFace < numFaces; iFace++)
          {
              getline(myfile, line);
              delimiterPos_1 = line.find(" ", 0);
              numElementsPerFace = atoi(line.substr(0,delimiterPos_1).c_str());
              if(numElementsPerFace != 3) //If faces are not triangular
              {
                    return NULL;
              }

              delimiterPos_2 = line.find(" ", delimiterPos_1+1);
              f0 = atoi(line.substr(delimiterPos_1+1, delimiterPos_2 - (delimiterPos_1 + 1)).c_str());
              delimiterPos_3 = line.find(" ", delimiterPos_2+1);
              f1 = atoi(line.substr(delimiterPos_2+1, delimiterPos_3 - (delimiterPos_2 + 1)).c_str());
              f2 = atoi(line.substr(delimiterPos_3+1).c_str());

              surface->getVertex(f0)->addNewFace(iFace);
              surface->getVertex(f1)->addNewFace(iFace);
              surface->getVertex(f2)->addNewFace(iFace);

              Face  * faceVertex = new Face;
              faceVertex->setPointsInFace(f0, f1, f2);
              faceVertex->setFaceIndex(iFace);
              surface->addNewFace(faceVertex);
          }
            myfile.close(); //Close file at the end

            return surface;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
    return 0;
}

/**
 * @brief readTriVert Read Tri and Vert files
 * @param triFile Poitner to QFile specifying the TRI file selected from the GUI
 * @param vertFile Pointer to QFile specifying the VERT file selected from the GUI
 * @return A pointer to an object of the Mesh class containing faces and vertexes
 */
Mesh * FileManager::readTriVert(QFile * triFile, QFile * vertFile)
{
    //Get string names of the files
    QString triFileName = triFile->fileName();
    string triFileNameString = triFileName.toStdString();
    QString vertFileName = vertFile->fileName();
    string vertFileNameString = vertFileName.toStdString();

    //First, read vert file
    string line;
    string fileFormatVert = vertFileNameString.substr(vertFileNameString.length() - 4, 4);

    int numPoints(0), numLines(0), numFaces(0);

    //First I have to get the number of points and number of faces to create the mesh
    if(fileFormatVert == "vert")
    {
        //First of all, get number of points by going through all lines
        // Modified from https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file
        ifstream myFile(vertFileNameString);
        if (myFile.is_open())
        {
            while (std::getline(myFile, line)) ++numLines;
            numPoints = numLines;
            myFile.close();
        }else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }

    string fileFormatTri = triFileNameString.substr(triFileNameString.length() - 3, 3);
    numLines = 0;

    if(fileFormatTri == "tri")
    {
        //First of all, get number of points by going through all lines
        // Modified from https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file
        ifstream myFile(triFileNameString);
        if (myFile.is_open())
        {
            while (std::getline(myFile, line)) ++numLines;
            numFaces = numLines;
            myFile.close();
        }else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
    Mesh * surface = new Mesh();
    //Now read the points and faces and put them in the mesh
    //If this point is reached, both files were read correctly before, so no need for checking format again
    unsigned int delimiterPos_1(0), delimiterPos_2(0);
    double x(0), y(0), z(0);

    ifstream myVertFile (vertFileNameString);
    if (myVertFile.is_open())
    {
        for(int iPoint=0; iPoint < numPoints; iPoint++)
        {
            getline(myVertFile, line);
            delimiterPos_1 = line.find(" ", 0);
            x = atof(line.substr(0,delimiterPos_1).c_str());
            delimiterPos_2 = line.find(" ", delimiterPos_1+1);
            y = atof(line.substr(delimiterPos_1+1,delimiterPos_2 - (delimiterPos_1 + 1)).c_str());
            z = atof(line.substr(delimiterPos_2+1).c_str());

            Vertex  * pointVertex = new Vertex;
            pointVertex->setCoordinates(x,y,z);
            pointVertex->setIndex(iPoint);
            surface->addNewVertex(pointVertex);
        }
        myVertFile.close();
    }
    else
    {
        return NULL;
    }


    int f0(0), f1(0), f2(0);
    delimiterPos_1 = 0;
    delimiterPos_2 = 0;

    ifstream myTriFile (triFileNameString);
    if (myTriFile.is_open())
    {
        for(int iFace=0; iFace < numFaces; iFace++)
        {
            getline(myTriFile, line);
            delimiterPos_1 = line.find(" ", 0);
            f0 = atoi(line.substr(0,delimiterPos_1).c_str()) -1;
            delimiterPos_2 = line.find(" ", delimiterPos_1+1);
            f1 = atoi(line.substr(delimiterPos_1+1,delimiterPos_2 - (delimiterPos_1 + 1)).c_str()) - 1;
            f2 = atoi(line.substr(delimiterPos_2+1).c_str()) - 1;

            surface->getVertex(f0)->addNewFace(iFace);
            surface->getVertex(f1)->addNewFace(iFace);
            surface->getVertex(f2)->addNewFace(iFace);

            Face  * faceVertex = new Face;
            faceVertex->setPointsInFace(f0, f1, f2);
            faceVertex->setFaceIndex(iFace);
            surface->addNewFace(faceVertex);
        }
        myTriFile.close();
    }
    else
    {
        return NULL;
    }
    return surface;
}
