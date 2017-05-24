TEMPLATE = app

QT += qml quick
CONFIG += c++11

INCLUDEPATH += include

HEADERS += \
    include/enum_types.h \
    include/game_space.h \
    include/logic.h \
    include/map_maker.h \
    include/easy_bot.h \
    include/clever_bot.h \
    include/base_bot.h

SOURCES += \
    src/game_space.cpp \
    src/logic.cpp \
    src/main.cpp \
    src/map_maker.cpp \
    src/easy_bot.cpp \
    src/clever_bot.cpp \
    src/base_bot.cpp

RESOURCES += \
    rc/qml.qrc \
    rc/img.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

