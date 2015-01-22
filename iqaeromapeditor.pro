#-------------------------------------------------
#
# Project created by QtCreator 2014-04-21T20:35:14
#
#-------------------------------------------------

QT       += core gui opengl

LIBS     += -L/home/pashok/local/lib/ -lGeographic

INCLUDEPATH += /home/pashok/local/include/

CONFIG   += C++11

#LIBS += -LC:\Qt\5.3\mingw482_32\bin -lGeographic9

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iqaeromapeditor
TEMPLATE = app


SOURCES += main.cpp\
        iqamemainwindow.cpp \
    iqameatdmenueditdialog.cpp \
    iqamelayer.cpp \
    iqamemapmodel.cpp \
    iqameapplication.cpp \
    iqlayerview.cpp \
    iqamegeopoint.cpp \
    iqamegeopointsmodel.cpp \
    iqamegeohelper.cpp \
    iqamegeopointstabledelegate.cpp \
    iqamegeopointstableview.cpp \
    iqamepointstablewidget.cpp \
    iqamemapmodeltreeview.cpp \
    iqameline.cpp \
    iqamesubline.cpp \
    iqamelinesegment.cpp \
    iqamestraightlinesegment.cpp \
    iqameshapesmodel.cpp \
    iqamegraphiceditwidget.cpp \
    iqameshapesattributes.cpp \
    iqameshapeobject.cpp \
    iqametext.cpp \
    iqamegeopointssortfiltermodel.cpp \
    iqamelogdialog.cpp \
    iqamenamedshapeobject.cpp \
    iqamesublinegraphicsitem.cpp \
    iqamelinegraphicsitem.cpp \
    iqamelayergraphicsitem.cpp \
    iqametextgraphicsitem.cpp

HEADERS  += iqamemainwindow.h \
    iqameatdmenueditdialog.h \
    iqamelayer.h \
    iqamemapmodel.h \
    iqameapplication.h \
    iqlayerview.h \
    iqamegeopoint.h \
    iqamegeopointsmodel.h \
    iqamegeohelper.h \
    iqamegeopointstabledelegate.h \
    iqamegeopointstableview.h \
    iqamepointstablewidget.h \
    iqamemapmodeltreeview.h \
    iqameline.h \
    iqamesubline.h \
    iqamelinesegment.h \
    iqamestraightlinesegment.h \
    iqameshapesmodel.h \
    iqamegraphiceditwidget.h \
    iqameshapesattributes.h \
    iqameshapeobject.h \
    iqametext.h \
    iqamegeopointssortfiltermodel.h \
    iqamelogdialog.h \
    iqamenamedshapeobject.h \
    iqamesublinegraphicsitem.h \
    iqamelinegraphicsitem.h \
    iqamelayergraphicsitem.h \
    iqametextgraphicsitem.h

FORMS    += iqamemainwindow.ui \
    iqameatdmenueditdialog.ui \
    iqamepointstablewidget.ui \
    iqamegraphiceditwidget.ui \
    iqamelogdialog.ui

RESOURCES += \
    icons.qrc
