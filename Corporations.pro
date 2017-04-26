TEMPLATE = app

QT += qml quick network
CONFIG += c++11

INCLUDEPATH += include

HEADERS += \
    include/client.h \
    include/enum_types.h \
    include/game_space.h \
    include/logic.h \
    include/map_maker.h \
    include/server.h

SOURCES += \
    src/client.cpp \
    src/game_space.cpp \
    src/logic.cpp \
    src/main.cpp \
    src/map_maker.cpp \
    src/server.cpp

RESOURCES += \
    rc/qml.qrc \
    rc/img.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

