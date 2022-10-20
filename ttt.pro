TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
        gamemodel.hpp \
        gameresultmodel.hpp \
        gamesavemodel.hpp \
        gameview.hpp \
        closeview.hpp \
        endview.hpp \
        menuview.hpp \
        modeselectview.hpp \
        node.hpp \
        pausemenuview.hpp \
        playerselectview.hpp \
        storyview.hpp

SOURCES += \
        gamemodel.cpp \
    gameresultmodel.cpp \
    gamesavemodel.cpp \
        gameview.cpp \
        closeview.cpp \
        endview.cpp \
        menuview.cpp \
    modeselectview.cpp \
    node.cpp \
        pausemenuview.cpp \
    playerselectview.cpp \
        storyview.cpp \
        main.cpp \

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../stf/release/ -lstf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../stf/release/ -lstf

INCLUDEPATH += $$PWD/../stf \
               $$PWD/../stf/sdb \
               $$PWD/../stf/smv \
DEPENDPATH += $$PWD/../stf \
              $$PWD/../stf/sdb \
              $$PWD/../stf/smv \
