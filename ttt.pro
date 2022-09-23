TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
        gamemodel.hpp \
        gameview.hpp \
        closeview.hpp \
        endview.hpp \
        menuview.hpp \
        pausemenuview.hpp \
        storyview.hpp

SOURCES += \
        gamemodel.cpp \
        gameview.cpp \
        closeview.cpp \
        endview.cpp \
        menuview.cpp \
        pausemenuview.cpp \
        storyview.cpp \
        main.cpp \

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../stf/release/ -lstf
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../stf/debug/ -lstf

INCLUDEPATH += $$PWD/../stf \
               $$PWD/../stf/sdb \
               $$PWD/../stf/smv \
DEPENDPATH += $$PWD/../stf \
              $$PWD/../stf/sdb \
              $$PWD/../stf/smv \
