
CONFIG += c++11
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    UI/mainwindow.cpp \
    BasicStructures/face.cpp \
    BasicStructures/mesh.cpp \
    BasicStructures/vertex.cpp \
    Communicator/communicator.cpp \
    Communicator/exception.cpp \
    FileManager/filemanager.cpp \
    Render/openglwidget.cpp \
    Engine/engine.cpp \
    Render/renderutil.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    UI/mainwindow.h \
    BasicStructures/face.h \
    BasicStructures/mesh.h \
    BasicStructures/vertex.h \
    Communicator/communicator.h \
    Communicator/exception.h \
    FileManager/filemanager.h \
    Render/openglwidget.h \
    Engine/engine.h \
    Render/renderutil.h

DISTFILES +=

RESOURCES += \
    shaders.qrc \
