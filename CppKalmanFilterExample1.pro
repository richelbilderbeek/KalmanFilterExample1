TEMPLATE = app
CONFIG += console
CONFIG -= qt

win32 {
  INCLUDEPATH += E:/boost_1_50_0

  LIBS += \
    -LE:/boost_1_50_0/stage/lib  \
    #-lboost_system-mgw47-mt-d-1_50 \     #NEXT for GCC 4.7
    #-lboost_filesystem-mgw47-mt-d-1_50 \ #NEXT for GCC 4.7
    #-lboost_regex-mgw47-mt-d-1_50 \      #NEXT for GCC 4.7
    -lboost_system-mgw44-mt-1_50 \        #PREV for GCC 4.4
    -lboost_filesystem-mgw44-mt-1_50 \    #PREV for GCC 4.4
    -lboost_regex-mgw44-mt-1_50          #PREV for GCC 4.4

}

SOURCES += main.cpp

