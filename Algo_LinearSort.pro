TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        linearsortclass.cpp \
        main.cpp \
        mergesortclass.cpp \
        stl_sort_wrapper.cpp \
        test_generator.cpp

HEADERS += \
    itask.h \
    linearsortclass.h \
    mergesortclass.h \
    stl_sort_wrapper.h \
    test_generator.h \
    tester.h

LIBS += -lstdc++fs
