#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T09:23:45
#
#-------------------------------------------------

QT       += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kpa_new
TEMPLATE = app

DESTDIR      =  ./bin
VPATH       +=  ./gui ./include ./src ./resources ./translate
INCLUDEPATH +=  ./include
MOC_DIR     +=  ./build/moc
OBJECTS_DIR +=  ./build/objects
UI_DIR      +=  ./build/ui
RCC_DIR     +=  ./build/res

win32{
LIBS += -lpthread #C:\Qt\Qt5.8.0\5.8\mingw53_32\plugins\platforms\qwindows.dll
}
unix{
LIBS += -lpthread -ldl
}

SOURCES += main.cpp\
        mainwindow.cpp \
        ava_terminal.cpp \
        event.cpp \
        kpa_com.cpp\
        eventmap.cpp \
        md_param.cpp \
        log.cpp \
        stream_kanal.cpp \
        md_object.cpp \
        event_bus.cpp \
        helper_converter.cpp \
        kpa_rocket.cpp \
        kashtan.cpp \
        tyngyska.cpp \
        ava_cxpoh.cpp \
        file_cxpoh.cpp \
        mymd5.cpp \
        comport.cpp \
        messagesave.cpp \
        sqlite3.c \
        datamanager.cpp \
        ava_sql_helper.cpp \
        ava_sqlite.cpp \
        sql_window.cpp \
        mixik.cpp


HEADERS  += \
        mainwindow.h \
        ava_terminal.h \
        Delegate.h \
        event.h \
        kpa_com.h\
        eventmap.h \
        md_param.h \
        log.h \
        stream_kanal.h \
        helper_converter.h \
        md_object.h \
        event_bus.h \
        kpa_rocket.h \
        kashtan.h \
        tyngyska.h \
        ava_cxpoh.h \
        test/test_helper_convert.h \
        comport.h \
        headerkpa.h \
        messagesave.h \
        sqlite3.h \
        datamanager.h \
        ava_sql_helper.h \
        ava_sqlite.h \
        sql_window.h \
        com_randomizer.h \
        error.h \
        mixik.h


FORMS    += \
         mainwindow.ui \
         comport.ui \
         messagesave.ui \
         sql_window.ui

RESOURCES += res.qrc

TRANSLATIONS = translate/QtLanguage_en.ts\
               translate/QtLanguage_ru.ts

CODECFORSRC = UTF-8
