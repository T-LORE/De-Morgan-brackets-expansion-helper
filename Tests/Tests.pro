QT += testlib
QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        test_createlogicaltree.cpp \
        test_deletedoublenegation.cpp \
        test_demorgantransform.cpp \
        test_treetostring.cpp \


#include(..\DeMorganBracketsExpansion\DeMorganBracketsExpansion.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    test_createlogicaltree.h \
    test_deletedoublenegation.h \
    test_demorgantransform.h \
    test_treetostring.h \

