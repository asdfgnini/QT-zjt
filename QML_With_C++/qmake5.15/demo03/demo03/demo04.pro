QT += quick quickcontrols2 qml gui

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

RESOURCES += qml.qrc

include(TaoQuick.pri)
# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = C:\Users\Administrator\Desktop\Qt\QT-zjt\QML_With_C++\qmake5.15\demo03\demo03

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
