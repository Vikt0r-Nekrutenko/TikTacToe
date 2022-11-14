TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    model/headers/gamemodel.hpp \
    model/headers/gameresultmodel.hpp \
    model/headers/gamesavemodel.hpp \
    model/headers/node.hpp \
    views/headers/closeview.hpp \
    views/headers/endview.hpp \
    views/headers/gameview.hpp \
    views/headers/menuview.hpp \
    views/headers/pausemenuview.hpp \
    views/headers/playerselectview.hpp \
    views/headers/storyview.hpp


SOURCES += \
        main.cpp \
    model/sources/gamemodel.cpp \
    model/sources/gameresultmodel.cpp \
    model/sources/gamesavemodel.cpp \
    model/sources/node.cpp \
    views/sources/closeview.cpp \
    views/sources/endview.cpp \
    views/sources/gameview.cpp \
    views/sources/menuview.cpp \
    views/sources/pausemenuview.cpp \
    views/sources/playerselectview.cpp \
    views/sources/storyview.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../stf/release/ -lstf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../stf/release/ -lstf

INCLUDEPATH += $$PWD/../stf \
               $$PWD/../stf/sdb \
               $$PWD/../stf/smv \
               $$PWD/model/headers \
               $$PWD/views/headers \

DEPENDPATH += $$PWD/../stf \
              $$PWD/../stf/sdb \
              $$PWD/../stf/smv \
              $$PWD/model/headers \
              $$PWD/views/headers \

DISTFILES += \
    sprs/*.spr
