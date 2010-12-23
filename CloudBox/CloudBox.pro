# Add more folders to ship with the application, here
folder_01.source = qml/CloudBox
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01


INCLUDEPATH += ../3rdparty/kqoauth/include/
INCLUDEPATH += ../3rdparty/kqoauth/src/

QT += network script
CONFIG += kqoauth

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# Avoid auto screen rotation
#DEFINES += ORIENTATIONLOCK

# Needs to be defined for Symbian
DEFINES += NETWORKACCESS

symbian:TARGET.UID3 = 0xE7E0B2E9

# Define QMLJSDEBUGGER to allow debugging of QML in debug builds
# (This might significantly increase build time)
# DEFINES += QMLJSDEBUGGER

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the 
# MOBILITY variable. 
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    json.cpp \
    dropboxnetwork.cpp


HEADERS += \
    helper.h \
    json.h \
    dropboxnetwork.h \
    assets.h

LIBS += -Wl,-rpath,./

LIBS += -lkqoauth
LIBS += -L./

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

RESOURCES += \
    resources.qrc
